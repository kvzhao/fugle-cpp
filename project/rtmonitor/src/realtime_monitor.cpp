#include "CLI/CLI.hpp"
#include "fugle.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <spdlog/spdlog.h>
#include <string>
#include <tabulate/table.hpp>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fugle_realtime;
using namespace tabulate;

struct Args {
    vector<string> symbols;
};

void clearConsoleLines(int lines) {
    for (int i = 0; i < lines; ++i) {
        std::cout << "\033[K\033[1A";
    }
}

int main(int argc, char **argv) {
    CLI::App app{"Fugle API Testbed: for terminal development"};

    Args args;
    app.add_option("-s,--symbol-list", args.symbols, "watch list");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    FugleIntraday intraday;
    unordered_map<string, TickerResponse> stockInfo;
    unordered_map<string, TradeData> prevTradeData;
    for (const auto &symbol : args.symbols) {
        spdlog::info("symbol: {}", symbol);
        stockInfo[symbol] = intraday.Ticker({.symbol = symbol});
        prevTradeData[symbol] =
            TradeData{.ask = 0, .bid = 0, .price = 0, .volume = 0};
    }

    Table table;
    table.add_row({"Stock", "Price", "Change (%)", "+Vol"});
    table.format().multi_byte_characters(true);
    for (uint32_t i = 0; i < args.symbols.size(); ++i) {
        const auto &symbol = args.symbols[i];
        string stockName = stockInfo[symbol].name + "(" + symbol + ")";
        table.add_row(
            {stockName, floatToString(stockInfo[symbol].previousClose),
             floatToString(0), to_string(prevTradeData[symbol].volume)});
    }

    while (true) {
        for (uint32_t i = 0; i < args.symbols.size(); ++i) {
            uint32_t rowIndex = i + 1;
            const auto &symbol = args.symbols[i];
            const auto &info = stockInfo.at(symbol);

            auto trades = intraday.Trades({.symbol = symbol});
            auto curTrade = trades.data.back();
            auto prevTrade = prevTradeData[symbol];

            float price = curTrade.price;
            float changePercentage =
                (price - info.previousClose) / info.previousClose * 100.0;
            uint32_t vol = curTrade.volume - prevTrade.volume;

            table[rowIndex][1].set_text(floatToString(price));
            table[rowIndex][2].set_text(floatToString(changePercentage));
            table[rowIndex][3].set_text(to_string(vol));

            bool isPriceInc = price - prevTrade.price > 0;
            bool isPriceChangeUp = changePercentage > 0;
            bool isPriceFlat = price - prevTrade.price == 0;
            bool isPriceChangeFlat = changePercentage == 0;

            // or near
            bool isPriceUpLimit = price == info.limitUpPrice;
            bool isPriceDownLimit = price == info.limitDownPrice;

            tabulate::Color priceColor =
                isPriceInc ? tabulate::Color::red : tabulate::Color::green;
            tabulate::Color changeColor =
                isPriceChangeUp ? tabulate::Color::red : tabulate::Color::green;
            if (isPriceFlat)
                priceColor = tabulate::Color::none;
            if (isPriceChangeFlat)
                changeColor = tabulate::Color::none;

            table[rowIndex][1].format().font_color(priceColor);
            table[rowIndex][2].format().font_color(changeColor);

            if (isPriceUpLimit)
                table[rowIndex][1].format().background_color(
                    tabulate::Color::red);
            if (isPriceDownLimit)
                table[rowIndex][1].format().background_color(
                    tabulate::Color::green);

            prevTradeData[symbol] = curTrade;
        }

        cout << table << std::endl;

        // clear the terminal
        std::cout << "\033[2J\033[1;1H";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
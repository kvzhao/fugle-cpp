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

int main(int argc, char **argv) {
    CLI::App app{"Fugle API : Real-time stock price monitor"};

    Args args;
    app.add_option("-s,--symbol-list", args.symbols, "watch list");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    FugleIntraday intraday;
    FugleHistorical historical;
    FugleSnapshot snapshot;

    unordered_map<string, TickerResponse> stockInfo;
    unordered_map<string, TradeData> prevTradeData;
    unordered_map<string, vector<CandleData>> candleDay;
    // unordered_map<string, vector<CandleData>> candleWeek;

    // TODO: Show INDEX by default

    // Fetch stock info
    for (const auto &symbol : args.symbols) {
        spdlog::info("symbol: {}", symbol);
        stockInfo[symbol] = intraday.Ticker({.symbol = symbol});
        prevTradeData[symbol] =
            TradeData{.ask = 0, .bid = 0, .price = 0, .volume = 0};

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        // TODO: time frame, sort with time
        historical
            .Candles({.symbol = symbol, .timeframe = CandleTimeFrame::K_DAY})
            .data;
    }

    // TODO: Use predefined vector for colume
    // TODO: Pressure & Support

    Table table;
    table.add_row(
        {"Stock", "Price", "Change (%)", "+Vol", "AvgPrice", "Val (E)"});
    table.format().multi_byte_characters(true);
    for (uint32_t i = 0; i < args.symbols.size(); ++i) {
        const auto &symbol = args.symbols[i];
        string stockName = stockInfo[symbol].name + "(" + symbol + ")";
        table.add_row({stockName,
                       floatToString(stockInfo[symbol].previousClose),
                       floatToString(stockInfo[symbol].previousClose),
                       to_string(prevTradeData[symbol].volume),
                       floatToString(0), floatToString(0)});
        table[i + 1][1].format().font_style({FontStyle::bold});
    }

    while (true) {
        for (uint32_t i = 0; i < args.symbols.size(); ++i) {
            uint32_t rowIndex = i + 1;
            const auto &symbol = args.symbols[i];
            const auto &info = stockInfo.at(symbol);

            auto trades = intraday.Trades({.symbol = symbol});
            auto quote = intraday.Quote({.symbol = symbol});

            auto curTrade = trades.data.front();
            auto prevTrade = prevTradeData[symbol];

            float price = curTrade.price;
            float changePercentage =
                (price - info.previousClose) / info.previousClose * 100.0;
            uint32_t vol = curTrade.volume - prevTrade.volume;
            float avgPrice = quote.avgPrice;
            float val = quote.total.tradeValue / 1e8;

            // TODO: Add technical analysis
            table[rowIndex][1].set_text(floatToString(price));
            table[rowIndex][2].set_text(floatToString(changePercentage));
            table[rowIndex][3].set_text(to_string(vol));
            table[rowIndex][4].set_text(floatToString(avgPrice));
            table[rowIndex][5].set_text(floatToString(val));

            bool isPriceInc = price - prevTrade.price > 0;
            bool isPriceFlat = price - prevTrade.price == 0;

            bool isPriceChangeUp = changePercentage > 0;
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
            else if (isPriceDownLimit)
                table[rowIndex][1].format().background_color(
                    tabulate::Color::green);
            else
                table[rowIndex][1].format().background_color(
                    tabulate::Color::none);

            prevTradeData[symbol] = curTrade;
        }

        cout << table << std::endl;

        // clear the terminal
        std::cout << "\033[2J\033[1;1H";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
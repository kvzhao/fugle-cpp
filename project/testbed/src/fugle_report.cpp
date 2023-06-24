
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

#include "fugle_report.hpp"
#include "progressbar.hpp"

using namespace std;
using namespace fugle_realtime;
using namespace fugle_app;

vector<string>
FugleReport::TradingValueRankingReport(const vector<MarketType> &markets,
                                       uint32_t numStock) {
    FugleSnapshot snapshot;

    // TODO: safety check of numStock

    priority_queue<ActiveTradeData, vector<ActiveTradeData>, CompareTradeValue>
        tradeQueue;

    string date;
    vector<string> marketStr;
    for (const auto &market : markets) {
        if (market != MarketType::OTC && market != MarketType::TSE)
            continue;
        auto actives =
            snapshot.Actives({.market = market, .trade = TradeType::VALUE});
        for (uint32_t i = 0; i < numStock; ++i) {
            const auto &data = actives.data[i];
            tradeQueue.push(data);
        }
        date = actives.date;
        marketStr.emplace_back(sMarketType.at(market));
    }

    while (tradeQueue.size() > numStock) {
        tradeQueue.pop();
    }

    vector<ActiveTradeData> sortedTradeData;
    while (!tradeQueue.empty()) {
        auto data = tradeQueue.top();
        sortedTradeData.push_back(data);
        tradeQueue.pop();
    }
    reverse(sortedTradeData.begin(), sortedTradeData.end());

    // Ranking of Transaction Values

    cout << date << " Market : " << joinWith(marketStr, ", ") << endl;
    tabulate::Table table;
    table.add_row({"Rank", "Symbol", "Value", "Volume", "Change", "Change (%)",
                   "Name", "20% UP"});
    table.format().multi_byte_characters(true);

    vector<string> sortedStockSymbols;
    progressbar bar(numStock);
    for (uint32_t i = 0; i < numStock; ++i) {
        bar.update();

        const auto &data = sortedTradeData[i];

        uint32_t rowIndex = i + 1;

        auto valueStr = floatToString(data.tradeValue / 1e8);
        float changePercent =
            data.change / (data.closePrice - data.change) * 100.0;

        bool isHitPriceLimit = std::abs(changePercent) > 9.5;

        bool is20Up = FugleReport::Is20PercentUpLastWeek(data.symbol);
        string is20UpStr = is20Up ? "Yes" : "";

        if (is20Up) {
            // TODO: is it first breakthrough?
        }

        table.add_row({to_string(rowIndex), data.symbol, valueStr,
                       to_string(data.tradeVolume), floatToString(data.change),
                       floatToString(changePercent), data.name, is20UpStr});

        tabulate::Color color =
            data.change > 0 ? tabulate::Color::red : tabulate::Color::green;

        if (isHitPriceLimit) {
            table[rowIndex][4].format().background_color(color);
            table[rowIndex][5].format().background_color(color);
        } else {
            table[rowIndex][4].format().font_color(color);
            table[rowIndex][5].format().font_color(color);
        }
        sortedStockSymbols.emplace_back(data.symbol);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    cout << table << endl;

    return sortedStockSymbols;
}

bool FugleReport::Is20PercentUpLastWeek(const string &symbol) {
    const float topPerformancePercentage = 20.0f;
    auto dateToday = getToday();
    auto dateLastWeek = subtractDays(dateToday, 14);

    FugleHistorical historical;
    auto weekCandles = historical.Candles({.symbol = symbol,
                                           .timeframe = CandleTimeFrame::K_WEEK,
                                           .from = dateLastWeek,
                                           .to = dateToday});

    vector<string> sortedDates;
    unordered_map<string, CandleData> candlesticks;
    for (const auto &data : weekCandles.data) {
        sortedDates.emplace_back(data.date);
        candlesticks[data.date] = data;
    }
    sort(sortedDates.begin(), sortedDates.end());

    for (size_t i = 1; i < sortedDates.size(); ++i) {
        auto lastDate = sortedDates[i - 1];
        auto currentDate = sortedDates[i];
        auto last = candlesticks[lastDate];
        auto current = candlesticks[currentDate];
        float changePercent = (current.close - last.close) / last.close * 100.0;

        if (changePercent >= topPerformancePercentage) {
            spdlog::debug("{} {} to {}, last close {}, current close {} => {}%",
                          symbol, lastDate, currentDate, last.close,
                          current.close, floatToString(changePercent));
            return true;
        }
    }

    return false;
}
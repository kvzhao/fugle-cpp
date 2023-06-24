
#include "fugle_report.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <tabulate/table.hpp>
#include <vector>

using namespace std;
using namespace fugle_realtime;
using namespace fugle_app;

void FugleDailyReport::TradingValueRankingReport(
    const vector<MarketType> &markets, uint32_t numStock) {
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
    table.add_row(
        {"Rank", "Symbol", "Value", "Volume", "Change", "Change (%)", "Name"});
    table.format().multi_byte_characters(true);

    for (uint32_t i = 0; i < numStock; ++i) {
        const auto &data = sortedTradeData[i];

        uint32_t rowIndex = i + 1;

        auto valueStr = floatToString(data.tradeValue / 1e8);
        float changePercent =
            data.change / (data.closePrice - data.change) * 100.0;

        bool isHitPriceLimit = std::abs(changePercent) > 9.5;

        table.add_row({
            to_string(rowIndex),
            data.symbol,
            valueStr,
            to_string(data.tradeVolume),
            floatToString(data.change),
            floatToString(changePercent),
            data.name,
        });

        tabulate::Color color =
            data.change > 0 ? tabulate::Color::red : tabulate::Color::green;

        if (isHitPriceLimit) {
            table[rowIndex][4].format().background_color(color);
            table[rowIndex][5].format().background_color(color);
        } else {
            table[rowIndex][4].format().font_color(color);
            table[rowIndex][5].format().font_color(color);
        }
    }

    cout << table << endl;
}
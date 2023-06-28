
#pragma once

#include "fugle.hpp"
#include <string>
#include <vector>

using namespace std;
using namespace fugle_realtime;

namespace fugle_app {

struct CompareTradeValue {
    bool operator()(const ActiveTradeData &trade1,
                    const ActiveTradeData &trade2) {
        return trade1.tradeValue > trade2.tradeValue;
    }
};

struct CompareTradeVolume {
    bool operator()(const ActiveTradeData &trade1,
                    const ActiveTradeData &trade2) {
        return trade1.tradeVolume > trade2.tradeVolume;
    }
};

struct TAWeekyReport {
    bool is20Percent = false;
    float changePercent = 0.0;
    float volRation = 1.0;
};

class FugleWeeklyReport {
  public:
    static vector<string>
    TradingValueRankingReport(const vector<MarketType> &markets,
                              uint32_t numStock = 100);
    // todo: trading volume
    static vector<string>
    DailyTradingValueRankingReport(const vector<MarketType> &markets,
                                   uint32_t numStock = 100);

    static bool Is20PercentUpLastWeek(const string &symbol);

    static TAWeekyReport TechnicalAnalysisWeekly(const string &symbol);
};

} // namespace fugle_app
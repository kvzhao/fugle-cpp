
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

class FugleDailyReport {
  public:
    static void TradingValueRankingReport(const vector<MarketType> &markets,
                                          uint32_t numStock = 100);
    // todo: trading volume
};

} // namespace fugle_app
#pragma once

#include "fugle_client_base.hpp"
#include "fugle_historical_data.hpp"
#include <nlohmann/json.hpp>

namespace fugle_realtime {

class FugleHistorical : public FugleHttpClientBase {
  public:
    FugleHistorical();

    HistoricalChandlesResponse
    Candles(const HistoricalChandlesParameter &param);

    StatsResponse Stats(const StatsParameter &param);

  private:
};

} // namespace fugle_realtime
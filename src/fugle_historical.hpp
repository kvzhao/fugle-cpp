#pragma once

#include "fugle_client_base.hpp"
#include "fugle_historical_data.hpp"
#include <nlohmann/json.hpp>

namespace fugle_realtime {

class FugleHistorical : public FugleHttpClientBase {
public:
  FugleHistorical(const string &key);

  HistoricalChandlesResponse Candles(const HistoricalChandlesParameter &param);

private:
};

} // namespace fugle_realtime
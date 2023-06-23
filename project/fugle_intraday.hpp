#pragma once

#include "fugle_client_base.hpp"
#include "fugle_intraday_data.hpp"
#include <nlohmann/json.hpp>

namespace fugle_realtime {

class FugleIntraday : public FugleHttpClientBase {
public:
  FugleIntraday(const string &key);

  TickersResponse Tickers(const TickersParameter &param);

  VolumeResponse Volumes(const VolumeParameter &param);

  QuoteResponse Quote(const QuoteParameter &param);

  TradesResponse Trades(const TradesParameter &param);

  ChandlesResponse Candles(const ChandlesParameter &param);

private:
};

} // namespace fugle_realtime
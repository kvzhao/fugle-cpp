
#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace fugle_realtime {

static const std::vector<std::string> kFugleAPIList = {
    "/intraday/tickers",          "/intraday/ticker/{symbol}",
    "/intraday/quote/{symbol}",   "/intraday/candles/{symbol}",
    "/intraday/trades/{symbol}",  "/intraday/volumes/{symbol}",
    "/snapshot/quotes/{market}",  "/snapshot/movers/{market}",
    "/snapshot/actives/{market}", "/historical/candles/{symbol}",
    "/historical/stats/{symbol}"};

inline int ShowAPIs() {
  for (const auto &s : kFugleAPIList) {
    spdlog::info(s);
  }
  return 0;
}
}
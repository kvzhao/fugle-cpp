#pragma once

#include "fugle_common_data.hpp"
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace nlohmann;

namespace fugle_realtime {
const static string kHistorical = "historical";
const static string kChandles = "candles";
const static string kFields = "fields";
const static string kFrom = "from";
const static string kTo = "to";

struct HistoricalChandlesParameter {
  string symbol;
  Date from;
  Date to;
  CandleTimeFrame timeframe = CandleTimeFrame::K_DAY;
  // TODO: Use CandleField
  string fields = "open,high,low,close,volume,turnover,change";
};

struct HistoricalChandlesResponse {
  string symbol;
  string type;
  string market;
  string exchange;
  vector<CandleData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j,
                      HistoricalChandlesResponse &data) {
  j.at("symbol").get_to(data.symbol);
  j.at("type").get_to(data.type);
  j.at("market").get_to(data.market);
  j.at("data").get_to(data.data);
}

} // namespace fugle_realtime
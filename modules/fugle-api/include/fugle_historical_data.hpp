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
const static string kStats = "stats";
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

struct StatsParameter {
    string symbol;
};

struct StatsResponse {
    string date;
    string type;
    string exchange;
    string market;
    string symbol;
    string name;
    float openPrice;
    float highPrice;
    float lowPrice;
    float closePrice;
    float change;
    float changePercent;
    uint32_t tradeVolume;
    uint64_t tradeValue;
    float previousClose;
    float week52High;
    float week52Low;
};

template <typename BasicJsonType>
void from_json(const BasicJsonType &j, StatsResponse &data) {
    j.at("date").get_to(data.date);
    j.at("type").get_to(data.type);
    j.at("exchange").get_to(data.exchange);
    j.at("market").get_to(data.market);
    j.at("symbol").get_to(data.symbol);
    j.at("name").get_to(data.name);
    j.at("openPrice").get_to(data.openPrice);
    j.at("highPrice").get_to(data.highPrice);
    j.at("lowPrice").get_to(data.lowPrice);
    j.at("closePrice").get_to(data.closePrice);
    j.at("change").get_to(data.change);
    j.at("changePercent").get_to(data.changePercent);
    j.at("tradeVolume").get_to(data.tradeVolume);
    j.at("tradeValue").get_to(data.tradeValue);
    j.at("previousClose").get_to(data.previousClose);
    j.at("week52High").get_to(data.week52High);
    j.at("week52Low").get_to(data.week52Low);
}

} // namespace fugle_realtime
#pragma once

#include "fugle_common_data.hpp"
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace nlohmann;

namespace fugle_realtime {
const static string kSnapshot = "snapshot";
const static string kActives = "actives";
const static string kQuotes = "quotes";
const static string kMovers = "movers";
const static string kTrade = "trade";
const static string kChange = "change";
const static string kDirection = "direction";

enum class TradeType : uint8_t { VOLUME, VALUE };
const static std::map<TradeType, std::string> sTradeType = {
    {TradeType::VOLUME, "volume"},
    {TradeType::VALUE, "value"},
};

struct ActivesParameter {
    MarketType market = MarketType::TSE;
    TradeType trade = TradeType::VALUE;
};

struct ActiveTradeData {
    string type;
    string symbol;
    string name;
    float openPrice = 0;
    float highPrice = 0;
    float lowPrice = 0;
    float closePrice = 0;
    float change = 0;
    float changePercent = 0;
    uint32_t tradeVolume;
    float tradeValue;
    uint64_t lastUpdated;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, ActiveTradeData &data) {
    j.at("type").get_to(data.type);
    j.at("symbol").get_to(data.symbol);
    j.at("name").get_to(data.name);
    if (j.count("openPrice")) {
        j.at("openPrice").get_to(data.openPrice);
    }
    if (j.count("highPrice")) {
        j.at("highPrice").get_to(data.highPrice);
    }
    if (j.count("lowPrice")) {
        j.at("lowPrice").get_to(data.lowPrice);
    }
    if (j.count("closePrice")) {
        j.at("closePrice").get_to(data.closePrice);
    }
    if (j.count("change")) {
        j.at("change").get_to(data.change);
    }
    if (j.count("tradeVolume")) {
        j.at("tradeVolume").get_to(data.tradeVolume);
    }
    if (j.count("tradeValue")) {
        j.at("tradeValue").get_to(data.tradeValue);
    }
    if (j.count("lastUpdated")) {
        j.at("lastUpdated").get_to(data.lastUpdated);
    }
}

struct ActivesResponse {
    string date;
    string time;
    string market;
    string trade;
    vector<ActiveTradeData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, ActivesResponse &data) {
    j.at("date").get_to(data.date);
    j.at("time").get_to(data.time);
    j.at("market").get_to(data.market);
    j.at("trade").get_to(data.trade);
    j.at("data").get_to(data.data);
}

enum class MoveDirectionType : uint8_t {
    UP,
    DOWN,
};
const static std::map<MoveDirectionType, std::string> sMoveDirectionType = {
    {MoveDirectionType::UP, "up"},
    {MoveDirectionType::DOWN, "down"},
};
struct MoversParameter {
    MarketType market = MarketType::TSE;
    TradeType trade = TradeType::VALUE;
    string change = "percent"; // percent or value
    MoveDirectionType direction = MoveDirectionType::UP;
    float gt = -1;
    float lt = -1;
    float gte = -1;
    float lte = -1;
    float eq = -1;
};

struct MoversResponse {
    string date;
    string time;
    string market;
    string change;
    vector<ActiveTradeData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, MoversResponse &data) {
    j.at("date").get_to(data.date);
    j.at("time").get_to(data.time);
    j.at("market").get_to(data.market);
    j.at("change").get_to(data.change);
    j.at("data").get_to(data.data);
}

struct QuotesParameter {
    MarketType market = MarketType::TSE;
};

struct QuotesResponse {
    string date;
    string time;
    string market;
    vector<ActiveTradeData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, QuotesResponse &data) {
    j.at("date").get_to(data.date);
    j.at("time").get_to(data.time);
    j.at("market").get_to(data.market);
    j.at("data").get_to(data.data);
}

} // namespace fugle_realtime
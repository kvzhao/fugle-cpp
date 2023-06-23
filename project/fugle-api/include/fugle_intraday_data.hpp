#pragma once

#include "fugle_common_data.hpp"
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace nlohmann;

namespace fugle_realtime {

const static string kIntrady = "intraday";
const static string kTickers = "tickers";
const static string kTicker = "ticker";
const static string kQuote = "quote";
const static string kCandles = "candles";
const static string kTrades = "trades";
const static string kVolumes = "volumes";

struct VolumeParameter {
    string symbol;
    string type;
};

struct VolumeData {
    float price;
    uint32_t volume;
    uint32_t volumeAtAsk;
    uint32_t volumeAtBid;
};

template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, VolumeData &data) {
    j.at("price").get_to(data.price);
    j.at("volume").get_to(data.volume);
    j.at("volumeAtAsk").get_to(data.volumeAtAsk);
    j.at("volumeAtBid").get_to(data.volumeAtBid);
}

struct VolumeResponse {
    string date;
    string exchange;
    string market;
    string symbol;
    string type;
    vector<VolumeData> data;
};

template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, VolumeResponse &data) {
    j.at("date").get_to(data.date);
    j.at("exchange").get_to(data.exchange);
    j.at("market").get_to(data.market);
    j.at("symbol").get_to(data.symbol);
    j.at("type").get_to(data.type);
    j.at("data").get_to(data.data);
}

struct QuoteParameter {
    string symbol;
    string type;
};

struct OrderData {
    float price;
    uint32_t size;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, OrderData &data) {
    j.at("price").get_to(data.price);
    j.at("size").get_to(data.size);
}

struct TradeData {
    float ask;
    float bid;
    float price;
    uint32_t size;
    uint32_t volume;
    uint32_t serial;
    uint64_t time;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, TradeData &data) {
    j.at("price").get_to(data.price);
    j.at("size").get_to(data.size);
    if (j.count("ask")) {
        j.at("ask").get_to(data.ask);
    }
    if (j.count("bid")) {
        j.at("bid").get_to(data.bid);
    }
    j.at("time").get_to(data.time);
    j.at("serial").get_to(data.serial);
    if (j.count("volume")) {
        j.at("volume").get_to(data.volume);
    }
}

struct TotalTradeData {
    uint64_t time;
    float tradeValue;
    uint32_t tradeVolume;
    uint32_t tradeVolumeAtAsk;
    uint32_t tradeVolumeAtBid;
    uint32_t transaction;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, TotalTradeData &data) {
    j.at("time").get_to(data.time);
    j.at("tradeValue").get_to(data.tradeValue);
    j.at("tradeVolume").get_to(data.tradeVolume);
    j.at("tradeVolumeAtAsk").get_to(data.tradeVolumeAtAsk);
    j.at("tradeVolumeAtBid").get_to(data.tradeVolumeAtBid);
    j.at("transaction").get_to(data.transaction);
}

struct QuoteResponse {
    string date;
    string exchange;
    string market;
    string symbol;
    string type;
    string name;

    float referencePrice;
    float previousClose;
    float openPrice;
    float highPrice;
    float lowPrice;
    float closePrice;
    float avgPrice;
    float change;
    float changePercent;
    float amplitude;
    float lastPrice;

    uint64_t openTime;
    uint64_t highTime;
    uint64_t lowTime;
    uint64_t closeTime;

    vector<OrderData> bids;
    vector<OrderData> asks;

    TradeData lastTrial;
    TradeData lastTrade;
    TotalTradeData total;

    uint32_t lastSize;
    uint32_t serial;
    uint64_t lastUpdated;
    bool isClose;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, QuoteResponse &data) {
    j.at("date").get_to(data.date);
    j.at("exchange").get_to(data.exchange);
    j.at("market").get_to(data.market);
    j.at("symbol").get_to(data.symbol);
    j.at("type").get_to(data.type);
    j.at("name").get_to(data.name);
    j.at("referencePrice").get_to(data.referencePrice);
    j.at("previousClose").get_to(data.previousClose);
    j.at("openPrice").get_to(data.openPrice);
    j.at("highPrice").get_to(data.highPrice);
    j.at("lowPrice").get_to(data.lowPrice);
    j.at("closePrice").get_to(data.closePrice);
    j.at("avgPrice").get_to(data.avgPrice);
    j.at("change").get_to(data.change);
    j.at("changePercent").get_to(data.changePercent);
    j.at("amplitude").get_to(data.amplitude);
    j.at("lastPrice").get_to(data.lastPrice);
    j.at("openTime").get_to(data.openTime);
    j.at("highTime").get_to(data.highTime);
    j.at("lowTime").get_to(data.lowTime);
    j.at("closeTime").get_to(data.closeTime);
    j.at("lastSize").get_to(data.lastSize);
    j.at("serial").get_to(data.serial);
    j.at("lastUpdated").get_to(data.lastUpdated);
    j.at("isClose").get_to(data.isClose);
    j.at("bids").get_to(data.bids);
    j.at("asks").get_to(data.asks);
    j.at("lastTrial").get_to(data.lastTrial);
    j.at("lastTrade").get_to(data.lastTrade);
    j.at("total").get_to(data.total);
}

struct TradesParameter {
    string symbol;
    string type;
    float offset = 0;
    float limit = 0;
};

struct TradesResponse {
    string date;
    string exchange;
    string market;
    string symbol;
    string type;
    vector<TradeData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, TradesResponse &data) {
    j.at("date").get_to(data.date);
    j.at("exchange").get_to(data.exchange);
    j.at("market").get_to(data.market);
    j.at("symbol").get_to(data.symbol);
    j.at("type").get_to(data.type);
    j.at("data").get_to(data.data);
}

struct ChandlesParameter {
    string symbol;
    string type;
    CandleTimeFrame timeFrame = CandleTimeFrame::K_1_MIN;
};

struct ChandlesResponse {
    string date;
    string exchange;
    string market;
    string symbol;
    string type;
    string timeframe;
    vector<CandleData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, ChandlesResponse &data) {
    j.at("date").get_to(data.date);
    j.at("exchange").get_to(data.exchange);
    j.at("market").get_to(data.market);
    j.at("symbol").get_to(data.symbol);
    j.at("type").get_to(data.type);
    j.at("data").get_to(data.data);
}

struct TickersParameter {
    TickerType type = TickerType::EQUITY;
    ExchangeType exchange = ExchangeType::TWSE;
    MarketType market = MarketType::TSE;
    // TODO
    string industry;
    bool isNormal = true;
    bool isAttention = true;
    bool isDisposition = true;
    bool isHalted = true;
};

struct TickerData {
    string symbol;
    string name;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, TickerData &data) {
    j.at("symbol").get_to(data.symbol);
    j.at("name").get_to(data.name);
};

struct TickersResponse {
    string date;
    string type;
    string exchange;
    string market;
    bool isNormal;
    bool isAttention;
    bool isDisposition;
    bool isHalted;
    vector<TickerData> data;
};
template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, TickersResponse &data) {
    j.at("date").get_to(data.date);
    j.at("exchange").get_to(data.exchange);
    j.at("market").get_to(data.market);
    j.at("type").get_to(data.type);
    j.at("data").get_to(data.data);

    if (j.count("isNormal")) {
        j.at("isNormal").get_to(data.isNormal);
    }
    if (j.count("isAttention")) {
        j.at("isAttention").get_to(data.isAttention);
    }
    if (j.count("isDisposition")) {
        j.at("isDisposition").get_to(data.isDisposition);
    }
    if (j.count("isHalted")) {
        j.at("isHalted").get_to(data.isHalted);
    }
};

} // namespace fugle_realtime
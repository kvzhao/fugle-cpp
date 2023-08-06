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
    if (j.count("isClose"))
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

struct TickerParameter {
    string symbol;
    string type;
};

struct TickerResponse {
    string date;
    string type;
    string exchange;
    string market;
    string symbol;
    string name;
    string industry;
    string securityType;
    float previousClose;
    float referencePrice;
    float limitUpPrice;
    float limitDownPrice;
    bool canDayTrade;
    bool canBuyDayTrade;
    bool canBelowFlatMarginShortSell;
    bool canBelowFlatSBLShortSell;
    bool isAttention;
    bool isDisposition;
    bool isUnusuallyRecommended;
    bool isSpecificAbnormally;
    uint32_t matchingInterval;
    string securityStatus;
    string tradingCurrency;
};

template <typename BasicJsonType>
void from_json(const BasicJsonType &j, TickerResponse &data) {
    if (j.count("date")) {
        j.at("date").get_to(data.date);
    }
    if (j.count("type")) {
        j.at("type").get_to(data.type);
    }
    if (j.count("exchange")) {
        j.at("exchange").get_to(data.exchange);
    }
    if (j.count("market")) {
        j.at("market").get_to(data.market);
    }
    if (j.count("symbol")) {
        j.at("symbol").get_to(data.symbol);
    }
    if (j.count("name")) {
        j.at("name").get_to(data.name);
    }
    if (j.count("industry")) {
        j.at("industry").get_to(data.industry);
    }
    if (j.count("securityType")) {
        j.at("securityType").get_to(data.securityType);
    }
    if (j.count("previousClose")) {
        j.at("previousClose").get_to(data.previousClose);
    }
    if (j.count("referencePrice")) {
        j.at("referencePrice").get_to(data.referencePrice);
    }
    if (j.count("limitUpPrice")) {
        j.at("limitUpPrice").get_to(data.limitUpPrice);
    }
    if (j.count("limitDownPrice")) {
        j.at("limitDownPrice").get_to(data.limitDownPrice);
    }
    if (j.count("canDayTrade")) {
        j.at("canDayTrade").get_to(data.canDayTrade);
    }
    if (j.count("canBuyDayTrade")) {
        j.at("canBuyDayTrade").get_to(data.canBuyDayTrade);
    }
    if (j.count("canBelowFlatMarginShortSell")) {
        j.at("canBelowFlatMarginShortSell")
            .get_to(data.canBelowFlatMarginShortSell);
    }
    if (j.count("canBelowFlatSBLShortSell")) {
        j.at("canBelowFlatSBLShortSell").get_to(data.canBelowFlatSBLShortSell);
    }
    if (j.count("isAttention")) {
        j.at("isAttention").get_to(data.isAttention);
    }
    if (j.count("isDisposition")) {
        j.at("isDisposition").get_to(data.isDisposition);
    }
    if (j.count("isUnusuallyRecommended")) {
        j.at("isUnusuallyRecommended").get_to(data.isUnusuallyRecommended);
    }
    if (j.count("isSpecificAbnormally")) {
        j.at("isSpecificAbnormally").get_to(data.isSpecificAbnormally);
    }
    if (j.count("matchingInterval")) {
        j.at("matchingInterval").get_to(data.matchingInterval);
    }
    if (j.count("securityStatus")) {
        j.at("securityStatus").get_to(data.securityStatus);
    }
    if (j.count("tradingCurrency")) {
        j.at("tradingCurrency").get_to(data.tradingCurrency);
    }
}

static map<string, string> tickerIndustryToSector = {{"01", "水泥工業"},
                                                     {"02", "食品工業"},
                                                     {"03", "塑膠工業"},
                                                     {"04", "紡織纖維"},
                                                     {"05", "電機機械"},
                                                     {"06", "電器電纜"},
                                                     {"08", "玻璃陶瓷"},
                                                     {"09", "造紙工業"},
                                                     {"10", "鋼鐵工業"},
                                                     {"11", "橡膠工業"},
                                                     {"12", "汽車工業"},
                                                     {"14", "建材營造"},
                                                     {"15", "航運業"},
                                                     {"16", "觀光事業"},
                                                     {"17", "金融保險"},
                                                     {"18", "貿易百貨"},
                                                     {"19", "綜合"},
                                                     {"20", "其他"},
                                                     {"21", "化學工業"},
                                                     {"22", "生技醫療業"},
                                                     {"23", "油電燃氣業"},
                                                     {"24", "半導體業"},
                                                     {"25", "電腦及週邊設備業"},
                                                     {"26", "光電業"},
                                                     {"27", "通信網路業"},
                                                     {"28", "電子零組件業"},
                                                     {"29", "電子通路業"},
                                                     {"30", "資訊服務業"},
                                                     {"31", "其他電子業"},
                                                     {"32", "文化創意業"},
                                                     {"33", "農業科技業"},
                                                     {"34", "電子商務"},
                                                     {"80", "管理股票"}};

static map<string, string> sectorToTickerIndustry = {{"水泥工業", "01"},
                                                     {"食品工業", "02"},
                                                     {"塑膠工業", "03"},
                                                     {"紡織纖維", "04"},
                                                     {"電機機械", "05"},
                                                     {"電器電纜", "06"},
                                                     {"玻璃陶瓷", "08"},
                                                     {"造紙工業", "09"},
                                                     {"鋼鐵工業", "10"},
                                                     {"橡膠工業", "11"},
                                                     {"汽車工業", "12"},
                                                     {"建材營造", "14"},
                                                     {"航運業", "15"},
                                                     {"觀光事業", "16"},
                                                     {"金融保險", "17"},
                                                     {"貿易百貨", "18"},
                                                     {"綜合", "19"},
                                                     {"其他", "20"},
                                                     {"化學工業", "21"},
                                                     {"生技醫療業", "22"},
                                                     {"油電燃氣業", "23"},
                                                     {"半導體業", "24"},
                                                     {"電腦及週邊設備業", "25"},
                                                     {"光電業", "26"},
                                                     {"通信網路業", "27"},
                                                     {"電子零組件業", "28"},
                                                     {"電子通路業", "29"},
                                                     {"資訊服務業", "30"},
                                                     {"其他電子業", "31"},
                                                     {"文化創意業", "32"},
                                                     {"農業科技業", "33"},
                                                     {"電子商務", "34"},
                                                     {"管理股票", "80"}};

} // namespace fugle_realtime
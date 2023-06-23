
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "fugle_client_base.hpp"
#include "fugle_common_data.hpp"
#include "fugle_intraday.hpp"
#include "fugle_intraday_data.hpp"
#include "str_utils.hpp"

using namespace std;
using namespace fugle_realtime;

FugleIntraday::FugleIntraday(const string &key)
    : FugleHttpClientBase(
          key, joinWithSlash({kDefaultFugleMarketDataAPI, kIntrady})) {}

VolumeResponse FugleIntraday::Volumes(const VolumeParameter &param) {
  string symbol = param.symbol;
  string resquest = joinWithSlash({kVolumes, symbol});

  string response = FugleHttpClientBase::SimpleGet(resquest);
  spdlog::debug("response : {}", response);

  auto jsonFormat = nlohmann::json::parse(response);

  VolumeResponse volResp;
  try {
    jsonFormat.get_to(volResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return volResp;
}

QuoteResponse FugleIntraday::Quote(const QuoteParameter &param) {
  string symbol = param.symbol;
  string resquest = joinWithSlash({kQuote, symbol});

  string response = FugleHttpClientBase::SimpleGet(resquest);
  spdlog::debug("response : {}", response);

  auto jsonFormat = nlohmann::json::parse(response);

  QuoteResponse quoteResp;
  try {
    jsonFormat.get_to(quoteResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return quoteResp;
}

TradesResponse FugleIntraday::Trades(const TradesParameter &param) {
  string symbol = param.symbol;

  // TODO: parameters
  if (param.limit != 0) {
  }

  if (param.offset != 0) {
  }

  string resquest = joinWithSlash({kTrades, symbol});

  string response = FugleHttpClientBase::SimpleGet(resquest);
  spdlog::debug("response : {}", response);

  auto jsonFormat = nlohmann::json::parse(response);

  TradesResponse tradesResp;
  try {
    jsonFormat.get_to(tradesResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return tradesResp;
}

ChandlesResponse FugleIntraday::Candles(const ChandlesParameter &param) {
  string symbol = param.symbol;
  string resquest = joinWithSlash({kCandles, symbol});

  std::map<std::string, std::string> queryParams;
  queryParams[kTimeFrame] = sChandleTimeFrame.at(param.timeFrame);
  resquest = buildUrlWithQueryParams(resquest, queryParams);
  spdlog::debug("resquest {}", resquest);

  string response = FugleHttpClientBase::SimpleGet(resquest);

  auto jsonFormat = nlohmann::json::parse(response);
  ChandlesResponse candleResp;
  try {
    jsonFormat.get_to(candleResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return candleResp;
}

TickersResponse FugleIntraday::Tickers(const TickersParameter &param) {

  string resquest = joinWithSlash({kTickers});

  std::map<std::string, std::string> queryParams;
  queryParams[kType] = sTickerType.at(param.type);
  queryParams[kExchange] = sExchangeType.at(param.exchange);
  queryParams[kMarket] = sMarketType.at(param.market);

  resquest = buildUrlWithQueryParams(resquest, queryParams);
  spdlog::debug("resquest {}", resquest);

  string response = FugleHttpClientBase::SimpleGet(resquest);

  auto jsonFormat = nlohmann::json::parse(response);
  TickersResponse tickersResp;
  try {
    jsonFormat.get_to(tickersResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return tickersResp;
}
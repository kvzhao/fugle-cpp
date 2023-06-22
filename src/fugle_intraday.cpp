
#include "fugle_intraday.hpp"
#include "fugle_client_base.hpp"
#include "fugle_intraday_data.hpp"
#include "str_utils.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

using namespace std;
using namespace fugle_realtime;

const static string kIntrady = "intraday";
const static string kTickers = "tickers";
const static string kTicker = "ticker";
const static string kQuote = "quote";
const static string kCandles = "candles";
const static string kTrades = "trades";
const static string kVolumes = "volumes";

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
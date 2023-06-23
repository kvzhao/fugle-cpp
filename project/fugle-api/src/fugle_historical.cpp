
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "fugle_client_base.hpp"
#include "fugle_common_data.hpp"
#include "fugle_historical.hpp"
#include "fugle_historical_data.hpp"
#include "str_utils.hpp"

using namespace std;
using namespace fugle_realtime;

FugleHistorical::FugleHistorical()
    : FugleHttpClientBase(
          joinWithSlash({kDefaultFugleMarketDataAPI, kHistorical})) {}

HistoricalChandlesResponse
FugleHistorical::Candles(const HistoricalChandlesParameter &param) {

  string symbol = param.symbol;
  string resquest = joinWithSlash({kChandles, symbol});

  std::map<std::string, std::string> queryParams;
  // TODO: Use CandleFeild
  queryParams[kFields] = param.fields;
  queryParams[kTimeFrame] = sChandleTimeFrame.at(param.timeframe);

  if (param.from.isValid()) {
    queryParams[kFrom] = formatDate(param.from);
  }

  if (param.to.isValid()) {
    queryParams[kTo] = formatDate(param.to);
  }

  resquest = buildUrlWithQueryParams(resquest, queryParams);
  spdlog::debug("resquest {}", resquest);

  string response = FugleHttpClientBase::SimpleGet(resquest);

  auto jsonFormat = nlohmann::json::parse(response);
  HistoricalChandlesResponse candlesResp;
  try {
    jsonFormat.get_to(candlesResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return candlesResp;
}
#include "str_utils.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

#include "fugle_client_base.hpp"
#include "fugle_common_data.hpp"
#include "fugle_snapshot.hpp"
#include "fugle_snapshot_data.hpp"

using namespace std;
using namespace fugle_realtime;

FugleSnapshot::FugleSnapshot(const string &key)
    : FugleHttpClientBase(
          key, joinWithSlash({kDefaultFugleMarketDataAPI, kSnapshot})) {}

ActivesResponse FugleSnapshot::Actives(const ActivesParameter &param) {

  string resquest = joinWithSlash({kActives, sMarketType.at(param.market)});

  std::map<std::string, std::string> queryParams;
  queryParams[kTrade] = sTradeType.at(param.trade);

  resquest = buildUrlWithQueryParams(resquest, queryParams);
  spdlog::debug("resquest {}", resquest);

  string response = FugleHttpClientBase::SimpleGet(resquest);

  auto jsonFormat = nlohmann::json::parse(response);
  ActivesResponse activeResp;
  try {
    jsonFormat.get_to(activeResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return activeResp;
}

MoversResponse FugleSnapshot::Movers(const MoversParameter &param) {

  string resquest = joinWithSlash({kMovers, sMarketType.at(param.market)});

  std::map<std::string, std::string> queryParams;
  queryParams[kChange] = param.change;
  queryParams[kDirection] = sMoveDirectionType.at(param.direction);
  if (param.gte != -1) {
    queryParams["gte"] = to_string(param.gte);
  }

  if (param.lte != -1) {
    queryParams["lte"] = to_string(param.lte);
  }

  if (param.gt != -1) {
    queryParams["gt"] = to_string(param.gt);
  }

  if (param.lt != -1) {
    queryParams["lt"] = to_string(param.lt);
  }

  if (param.eq != -1) {
    queryParams["eq"] = to_string(param.eq);
  }

  resquest = buildUrlWithQueryParams(resquest, queryParams);
  spdlog::debug("resquest {}", resquest);

  string response = FugleHttpClientBase::SimpleGet(resquest);

  auto jsonFormat = nlohmann::json::parse(response);
  MoversResponse moversResp;
  try {
    jsonFormat.get_to(moversResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return moversResp;
}

QuotesResponse FugleSnapshot::Quotes(const QuotesParameter &param) {
  string resquest = joinWithSlash({kQuotes, sMarketType.at(param.market)});
  spdlog::debug("resquest {}", resquest);

  string response = FugleHttpClientBase::SimpleGet(resquest);

  auto jsonFormat = nlohmann::json::parse(response);
  QuotesResponse quotesResp;
  try {
    jsonFormat.get_to(quotesResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return quotesResp;
}
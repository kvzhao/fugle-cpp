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
  ActivesResponse acticeResp;
  try {
    jsonFormat.get_to(acticeResp);
  } catch (const std::exception &ex) {
    spdlog::error(ex.what());
  }

  return acticeResp;
}
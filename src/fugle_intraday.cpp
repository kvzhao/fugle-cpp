
#include "fugle_intraday.hpp"
#include "fugle_client_base.hpp"
#include "fugle_intraday_data.hpp"
#include "str_utils.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

using namespace std;
using namespace fugle_realtime;

FugleIntraday::FugleIntraday(const string &key)
    : FugleHttpClientBase(key, kDefaultFugleMarketDataAPI + "/intraday") {}

VolumeResponse FugleIntraday::Volumes(const VolumeParameter &param) {
  const string method = "volumes";
  string symbol = param.symbol;
  string resquest = joinWithSlash({method, symbol});

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
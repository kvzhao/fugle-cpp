
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
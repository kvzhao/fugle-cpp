#pragma once

#include "fugle_client_base.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace nlohmann;

namespace fugle_realtime {

struct VolumeData {
  float price;
  uint32_t volume;
  uint32_t volumeAtAsk;
  uint32_t volumeAtBid;
};

template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, VolumeData &volData) {
  j.at("price").get_to(volData.price);
  j.at("volume").get_to(volData.volume);
  j.at("volumeAtAsk").get_to(volData.volumeAtAsk);
  j.at("volumeAtBid").get_to(volData.volumeAtBid);
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
inline void from_json(const BasicJsonType &j, VolumeResponse &volResp) {
  j.at("date").get_to(volResp.date);
  j.at("exchange").get_to(volResp.exchange);
  j.at("market").get_to(volResp.market);
  j.at("symbol").get_to(volResp.symbol);
  j.at("type").get_to(volResp.type);
  j.at("data").get_to(volResp.data);
}

struct VolumeParameter {
  string symbol;
  string type;
};

// todo json converter

} // namespace fugle_realtime
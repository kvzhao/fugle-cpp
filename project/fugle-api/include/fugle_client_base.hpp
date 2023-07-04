
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace web;
using namespace web::http;
using namespace web::http::client;

using namespace std;

const static string kXAPIKEY = "X-API-KEY";
const static string kDefaultFugleMarketDataAPI =
    "https://api.fugle.tw/marketdata/v1.0/stock";
namespace fugle_realtime {

class FugleHttpClientBase {
  public:
    FugleHttpClientBase();

    FugleHttpClientBase(const string &url);

    FugleHttpClientBase(const string &key, const string &url);

    string SimpleGet(const string &request);

    bool SetAPIKey(const string &key);

  private:
    bool IsInit() const { return _init; }

    // Move GET Internally
    pplx::task<string> Get(const string &endpoint);

  private:
    bool _init = false;
    string _apiKey;
    string _baseURL = kDefaultFugleMarketDataAPI;
    http_client _httpClient;
    http_headers _httpHeaders;
};
} // namespace fugle_realtime
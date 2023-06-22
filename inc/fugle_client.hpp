
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

#include <nlohmann/json.hpp>

using namespace web;
using namespace web::http;
using namespace web::http::client;

using namespace std;

const static string kXAPIKEY = "X-API-KEY";

namespace fugle_terminal {

// intraday, snapshot, historical

class FugleClient {
public:
  FugleClient(const string &key);

  FugleClient(const string &key, const string &url);

  string SimpleGet(const string &request);

private:
  // Move GET Internally
  pplx::task<std::string> Get(const std::string &endpoint);

private:
  string _apiKey;
  string _baseURL = "https://api.fugle.tw/marketdata/v1.0/stock";
  http_client _httpClient;
  http_headers _httpHeaders;
};
} // namespace fugle_terminal

#pragma once
#include <string>
#include <vector>

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

using namespace std;

const static string kXAPIKEY = "X-API-KEY";

namespace fugle_terminal {
class FugleClient {
public:
  FugleClient(const string &key);

  FugleClient(const string &key, const string &url);

  pplx::task<std::string> Get(const std::string &endpoint);

private:
  string _apiKey;
  string _baseURL = "https://api.fugle.tw/marketdata/v1.0/stock";
  http_client _httpClient;
  http_headers _httpHeaders;
};
} // namespace fugle_terminal
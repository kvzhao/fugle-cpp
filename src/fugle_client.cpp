
#include "fugle_client.hpp"

using namespace fugle_terminal;

FugleClient::FugleClient(const string &key)
    : _apiKey(key), _httpClient(U(_baseURL)) {
  _httpHeaders.add(kXAPIKEY, _apiKey);
}

FugleClient::FugleClient(const string &key, const string &url)
    : _apiKey(key), _baseURL(url), _httpClient(U(_baseURL)) {
  _httpHeaders.add(kXAPIKEY, _apiKey);
}

pplx::task<std::string> FugleClient::Get(const std::string &endpoint) {
  uri_builder builder(U(endpoint));

  http_request request(methods::GET);
  request.headers() = _httpHeaders;
  request.set_request_uri(builder.to_string());

  return _httpClient.request(request).then([](http_response response) {
    if (response.status_code() == status_codes::OK) {
      return response.extract_string();
    } else {
      throw std::runtime_error("GET request failed!");
    }
  });
}
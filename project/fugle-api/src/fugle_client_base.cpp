
#include "fugle_client_base.hpp"
#include "str_utils.hpp"
#include <spdlog/spdlog.h>

using namespace fugle_realtime;

std::string GetFugleAPIKey() {
  std::string key;
  if (const char *env_p = std::getenv("FUGLE_API_KEY")) {
    key = std::string{env_p};
  }
  spdlog::debug("Get fulge api key from env : {}", key);
  return key;
}

FugleHttpClientBase::FugleHttpClientBase() : _httpClient(U(_baseURL)) {
  SetAPIKey(GetFugleAPIKey());
  spdlog::debug("set default url {}, and use default key", _baseURL);
}

FugleHttpClientBase::FugleHttpClientBase(const string &url)
    : _baseURL(url), _httpClient(U(_baseURL)) {
  SetAPIKey(GetFugleAPIKey());
  spdlog::debug("set base url {}, and use default key", _baseURL);
}

FugleHttpClientBase::FugleHttpClientBase(const string &key, const string &url)
    : _baseURL(url), _httpClient(U(_baseURL)) {
  SetAPIKey(key);
  spdlog::debug("set url {}, and given api key", _baseURL);
}

bool FugleHttpClientBase::SetAPIKey(const string &key) {
  if (_httpHeaders.has(kXAPIKEY)) {
    _httpHeaders.remove(kXAPIKEY);
  }
  _apiKey = key;
  _httpHeaders.add(kXAPIKEY, _apiKey);
  _init = true;
  return true;
}

pplx::task<std::string> FugleHttpClientBase::Get(const std::string &endpoint) {
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

string FugleHttpClientBase::SimpleGet(const string &input) {
  if (!this->IsInit()) {
    throw std::runtime_error("client is not init.");
  }

  auto request = addSlashIfNeeded(input);
  spdlog::debug("request : {}", request);

  ostringstream oss;
  this->Get(request)
      .then([&oss](pplx::task<std::string> previousTask) {
        try {
          string responseString = previousTask.get();
          nlohmann::json json = nlohmann::json::parse(responseString);
          oss << json.dump(4) << std::endl;
        } catch (const std::exception &ex) {
          oss << ex.what() << std::endl;
        }
      })
      .wait();

  return oss.str();
}

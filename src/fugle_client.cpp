
#include "fugle_client.hpp"

using namespace fugle_realtime;

FugleHttpClientBase::FugleHttpClientBase(const string &key)
    : _apiKey(key), _httpClient(U(_baseURL)) {
  _httpHeaders.add(kXAPIKEY, _apiKey);
}

FugleHttpClientBase::FugleHttpClientBase(const string &key, const string &url)
    : _apiKey(key), _baseURL(url), _httpClient(U(_baseURL)) {
  _httpHeaders.add(kXAPIKEY, _apiKey);
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

string FugleHttpClientBase::SimpleGet(const string &request) {

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
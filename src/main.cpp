#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include <spdlog/spdlog.h>

#include "CLI/CLI.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;

int main(int argc, char **argv) {
  spdlog::info("Hello world!");

  CLI::App app{"Fugle Terminal"};

  std::string filePath = "../fugle_api_key.json";
  app.add_option("-f,--api-key-file", filePath, "Path to api key");

  CLI11_PARSE(app, argc, argv);

  std::ifstream apiKeyFile(filePath);
  if (!apiKeyFile.is_open()) {
    spdlog::error("Can not open the api key file");
    return 1;
  }

  json::value json_data;
  apiKeyFile >> json_data;
  std::string apiKey = json_data["key"].as_string();

  http_client client(
      U("https://api.fugle.tw/marketdata/v1.0/stock/intraday/ticker/2330"));

  http_request request(methods::GET);

  request.headers().add(U("X-API-KEY"), U(apiKey));

  auto response = client.request(request).get();

  utility::string_t response_content = response.extract_utf8string().get();

  std::cout << response_content << std::endl;

  return 0;
}
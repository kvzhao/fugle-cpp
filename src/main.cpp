#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include <spdlog/spdlog.h>

#include "CLI/CLI.hpp"

#include "fugle_api_list.hpp"
#include "fugle_client_base.hpp"

// For test
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;
using namespace fugle_realtime;

struct Args {
  string filePath = "api_key.txt";
  string endpoint = "/intraday/quote";
  string symbol = "2330";
  bool showApiList = false;
};

int ShowAPIs() {
  for (const auto &s : kFugleAPIList) {
    spdlog::info(s);
  }
  return 0;
}

int main(int argc, char **argv) {
  CLI::App app{"Fugle Terminal"};

  Args args;
  app.add_option("-f,--api-file", args.filePath, "Path to api key");
  app.add_option("-s,--stock-symbol", args.symbol, "symbol");
  app.add_option("-e,--endpoint", args.endpoint, "endpoint");
  app.add_flag("-l,--show-api-list", args.showApiList, "print Fugle APIs");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  if (args.showApiList) {
    spdlog::info("SQlite3 version {} {} ", SQLite::VERSION,
                 SQLite::getLibVersion());
    spdlog::info("SQliteCpp version {} ", SQLITECPP_VERSION);
    return ShowAPIs();
  }

  std ::ifstream apiKeyFile(args.filePath);
  if (!apiKeyFile.is_open()) {
    spdlog::error("Can not open the api key file");
    return 1;
  }
  string apiKey;
  getline(apiKeyFile, apiKey);

  FugleHttpClientBase fugleClient(apiKey);

  string request = args.endpoint + "/" + args.symbol;
  auto response = fugleClient.SimpleGet(request);
  spdlog::info("Response: {}", response);

  return 0;
}
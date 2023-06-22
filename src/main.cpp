#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include <spdlog/spdlog.h>

#include "CLI/CLI.hpp"

#include "fugle_api_list.hpp"
#include "fugle_client_base.hpp"
#include "fugle_intraday.hpp"
#include "fugle_intraday_data.hpp"

// For test
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;
using namespace fugle_realtime;

struct Args {
  string filePath = "api_key.txt";
  string endpoint = "/intraday/quote";
  string symbol = "2330";
  bool showApiList = false;
  bool debug = false;
};

int main(int argc, char **argv) {
  CLI::App app{"Fugle Terminal"};

  Args args;
  app.add_option("-f,--api-file", args.filePath, "Path to api key");
  app.add_option("-s,--stock-symbol", args.symbol, "symbol");
  app.add_option("-e,--endpoint", args.endpoint, "endpoint");
  app.add_flag("-l,--show-api-list", args.showApiList, "print Fugle APIs");
  app.add_flag("-d,--set-debug-mode", args.debug, "set debug log");

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

  if (args.debug) {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Set to debug log");
  }

  std ::ifstream apiKeyFile(args.filePath);
  if (!apiKeyFile.is_open()) {
    spdlog::error("Can not open the api key file");
    return 1;
  }

  string apiKey;
  getline(apiKeyFile, apiKey);

  FugleHttpClientBase fugleClient(apiKey);
  FugleIntraday intraday(apiKey);

  auto vol = intraday.Volumes({.symbol = args.symbol});

  spdlog::info("vol.symbol {}", vol.symbol);
  spdlog::info("vol.date {}", vol.date);
  for (const auto &data : vol.data) {
    spdlog::info("price = {} @ volume = {}, ask/bid = ({}, {})", data.price,
                 data.volume, data.volumeAtAsk, data.volumeAtBid);
  }

  // string request = args.endpoint + "/" + args.symbol;
  // auto response = fugleClient.SimpleGet(request);
  // spdlog::info("Response: {}", response);

  return 0;
}
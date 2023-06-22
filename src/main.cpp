#include "CLI/CLI.hpp"

#include "fugle.hpp"
#include "str_utils.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <spdlog/spdlog.h>

#include <tabulate/table.hpp>

#include <iostream>

using namespace std;
using namespace fugle_realtime;

struct Args {
  string filePath = "api_key.txt";
  string endpoint;
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
  FugleSnapshot snapshot(apiKey);

  if (args.endpoint.empty()) {

    auto actives = snapshot.Actives(
        {.market = MarketType::TSE, .trade = TradeType::VALUE});

    tabulate::Table table;
    table.add_row({"Rank", "Symbol", "Value", "Volume", "Change", "Name"});

    uint32_t topStocks = std::min(100, (int)actives.data.size());
    for (uint32_t i = 0; i < topStocks; ++i) {
      const auto &data = actives.data[i];
      auto valueStr = floatToString(data.tradeValue / 1e8);
      table.add_row({
          to_string(i + 1),
          data.symbol,
          valueStr,
          to_string(data.tradeVolume),
          floatToString(data.change),
          data.name,
      });
    }

    cout << table << endl;

    // for (const auto &data : tradeData) {
    //   table.add_row({data.name, std::to_string(data.change),
    //                  std::to_string(data.changePercent),
    //                  std::to_string(data.tradeValue)});
    // }

    // auto vol = intraday.Volumes({.symbol = args.symbol});
    // spdlog::info("vol.symbol {}", vol.symbol);
    // spdlog::info("vol.date {}", vol.date);
    // for (const auto &data : vol.data) {
    //   spdlog::info("price = {} @ volume = {}, ask/bid = ({}, {})",
    //   data.price,
    //                data.volume, data.volumeAtAsk, data.volumeAtBid);
    // }

    // auto quote = intraday.Quote({.symbol = args.symbol});
    // spdlog::info("quote.name {}", quote.name);
    // spdlog::info("quote.lastPrice {}", quote.lastPrice);
    // spdlog::info("quote.total.tradeValue {}", quote.total.tradeValue);
    // spdlog::info("quote.total.tradeVolume {}", quote.total.tradeVolume);
    // spdlog::info("quote.total.tradeVolumeAtAsk {}",
    //              quote.total.tradeVolumeAtAsk);
    // spdlog::info("quote.total.tradeVolumeAtBid {}",
    //              quote.total.tradeVolumeAtBid);

    // auto trades = intraday.Trades({.symbol = args.symbol});

    // for (const auto &data : trades.data) {
    //   spdlog::debug("trade p / v = {} / {} ", data.price, data.volume);
    // }

    // auto candles = intraday.Candles(
    //     {.symbol = args.symbol, .timeFrame = CandleTimeFrame::K_10_MIN});

    // for (const auto &data : candles.data) {
    //   spdlog::debug("candle {}, {}, {}, {} ", data.open, data.high, data.low,
    //                 data.close);
    // }

    // auto tickers = intraday.Tickers({.type = TickerType::EQUITY,
    //                                  .exchange = ExchangeType::TWSE,
    //                                  .market = MarketType::TSE});

    // for (const auto &ticker : tickers.data) {
    //   spdlog::debug("{} {}", ticker.symbol, ticker.name);
    // }
    // spdlog::info("# of tickers {}", tickers.data.size());

  } else {
    string request;

    if (!args.symbol.empty()) {
      request = joinWithSlash({args.endpoint, args.symbol});
    } else {
      request = args.endpoint;
    }
    auto response = fugleClient.SimpleGet(request);
    spdlog::info("Response: {}", response);
  }

  return 0;
}
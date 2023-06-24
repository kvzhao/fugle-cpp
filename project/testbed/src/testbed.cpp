#include <SQLiteCpp/SQLiteCpp.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "CLI/CLI.hpp"
#include "fugle.hpp"
#include "fugle_report.hpp"

using namespace std;
using namespace fugle_realtime;
using namespace fugle_app;
// using namespace tabulate;

struct Args {
    string symbol = "2330";
    bool debug = false;
    bool monitor = false;
};

int main(int argc, char **argv) {
    CLI::App app{"Fugle API Testbed: for terminal development"};

    Args args;
    app.add_option("-s,--stock-symbol", args.symbol, "symbol");
    app.add_flag("-d,--set-debug-mode", args.debug, "set debug log");
    app.add_flag("-m,--set-monitor-mode", args.monitor, "set monitor");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    if (args.debug) {
        spdlog::set_level(spdlog::level::debug);
        spdlog::debug("Set to debug log");
    }

    auto stocks = FugleReport::TradingValueRankingReport(
        {MarketType::TSE, MarketType::OTC});

    // FugleReport::TopPerformerLastWeek(stocks);

    // auto movers = snapshot.Movers({
    //     .market = MarketType::TSE,
    //     .direction = MoveDirectionType::UP,
    //     .gte = 5,
    // });

    // for (const auto &data : movers.data) {
    //     spdlog::info("{} = {} -> {}", data.name, data.openPrice,
    //                  data.closePrice);
    // }

    // auto quotes = snapshot.Quotes({
    //     .market = MarketType::TSE,
    // });

    // // For Drawing Candles
    // auto candles = historical.Candles({.symbol = args.symbol,
    //                                    .from = Date{2023, 5, 19},
    //                                    .to = Date{2023, 5, 26},
    //                                    .timeframe =
    //                                    CandleTimeFrame::K_DAY});

    // for (const auto &kbar : candles.data) {
    //     spdlog::debug("[{}] open {}, close {}, high {}, low {}, volume
    //     {}",
    //                   kbar.date, kbar.open, kbar.close, kbar.high,
    //                   kbar.close, kbar.volume);
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

    // auto intradyCandles = intraday.Candles(
    //     {.symbol = args.symbol, .timeFrame = CandleTimeFrame::K_10_MIN});

    // for (const auto &data : intradyCandles.data) {
    //   spdlog::debug("candle {}, {}, {}, {} ", data.open, data.high,
    //   data.low,
    //                 data.close);
    // }

    // auto tickers = intraday.Tickers({.type = TickerType::EQUITY,
    //                                  .exchange = ExchangeType::TWSE,
    //                                  .market = MarketType::TSE});

    // for (const auto &ticker : tickers.data) {
    //   spdlog::debug("{} {}", ticker.symbol, ticker.name);
    // }
    // spdlog::info("# of tickers {}", tickers.data.size());

    return 0;
}
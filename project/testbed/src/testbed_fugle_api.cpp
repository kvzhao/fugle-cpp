#include <SQLiteCpp/SQLiteCpp.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <tabulate/table.hpp>

#include "CLI/CLI.hpp"
#include "fugle.hpp"

using namespace std;
using namespace fugle_realtime;
using namespace tabulate;

struct Args {
    string symbol = "2330";
    bool debug = false;
};

int main(int argc, char **argv) {
    CLI::App app{"Fugle API Testbed: for terminal development"};

    Args args;
    app.add_option("-s,--stock-symbol", args.symbol, "symbol");
    app.add_flag("-d,--set-debug-mode", args.debug, "set debug log");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    if (args.debug) {
        spdlog::set_level(spdlog::level::debug);
        spdlog::debug("Set to debug log");
    }

    // NOTE: Consider combine
    FugleIntraday intraday;
    FugleSnapshot snapshot;
    FugleHistorical historical;

    auto actives = snapshot.Actives(
        {.market = MarketType::TSE, .trade = TradeType::VALUE});

    // TODO: Implement this as a specific function
    // Ranking of Transaction Values
    tabulate::Table table;
    table.add_row(
        {"Rank", "Symbol", "Value", "Volume", "Change", "Change (%)", "Name"});
    table.format().multi_byte_characters(true);

    uint32_t topStocks = std::min(100, (int)actives.data.size());
    for (uint32_t i = 0; i < topStocks; ++i) {
        uint32_t rowIndex = i + 1;
        const auto &data = actives.data[i];
        auto valueStr = floatToString(data.tradeValue / 1e8);
        float changePercent =
            data.change / (data.closePrice - data.change) * 100.0;
        table.add_row({
            to_string(rowIndex),
            data.symbol,
            valueStr,
            to_string(data.tradeVolume),
            floatToString(data.change),
            floatToString(changePercent),
            data.name,
        });
        if (data.change > 0) {
            table[rowIndex][4].format().font_color(Color::red);
            table[rowIndex][5].format().font_color(Color::red);
        } else {
            table[rowIndex][4].format().font_color(Color::green);
            table[rowIndex][5].format().font_color(Color::green);
        }
    }

    cout << table << endl;

    auto movers = snapshot.Movers({
        .market = MarketType::TSE,
        .direction = MoveDirectionType::UP,
        .gte = 5,
    });

    // for (const auto &data : movers.data) {
    //     spdlog::info("{} = {} -> {}", data.name, data.openPrice,
    //                  data.closePrice);
    // }

    auto quotes = snapshot.Quotes({
        .market = MarketType::TSE,
    });

    // For Drawing Candles
    auto candles = historical.Candles({.symbol = args.symbol,
                                       .from = Date{2023, 5, 19},
                                       .to = Date{2023, 5, 26},
                                       .timeframe = CandleTimeFrame::K_DAY});

    for (const auto &kbar : candles.data) {
        spdlog::debug("[{}] open {}, close {}, high {}, low {}, volume {}",
                      kbar.date, kbar.open, kbar.close, kbar.high, kbar.close,
                      kbar.volume);
    }

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
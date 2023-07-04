#include <SQLiteCpp/SQLiteCpp.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "CLI/CLI.hpp"
#include "fugle.hpp"
#include "fugle_report.hpp"
#include "test_db.hpp"

using namespace std;
using namespace fugle_realtime;
using namespace fugle_app;
// using namespace tabulate;

struct Args {
    string symbol = "2330";
    string command;
    string mode = "report";
    bool debug = false;
};

int main(int argc, char **argv) {
    CLI::App app{"Fugle API Testbed: for terminal development"};

    Args args;
    app.add_option("-s,--stock-symbol", args.symbol, "symbol");
    app.add_option("-m,--run-mode", args.mode, "Run mode");
    app.add_option("-c,--command", args.command, "/snapshot/movers");
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

    if (args.mode == "report") {
        auto stocks = FugleWeeklyReport::TradingValueRankingReport(
            {MarketType::TSE, MarketType::OTC}, 100);
        return 0;
    }

    if (args.mode == "value") {
        auto stocks = FugleWeeklyReport::DailyTradingValueRankingReport(
            {MarketType::TSE, MarketType::OTC}, 100);
        return 0;
    }

    if (args.mode == "get") {
        FugleHttpClientBase base;
        if (!args.command.empty()) {
            auto resp = base.SimpleGet(args.command);
            spdlog::info("Response {}", resp);
        } else
            spdlog::warn("no command provided for get");

        return 0;
    }

    if (args.mode == "db") {
        return StockDBTester::RunSQLiteSample();
    }

    spdlog::error("run mode {} not found", args.mode);

    return 0;
}
#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <string>

using namespace nlohmann;

namespace fugle_realtime {

const static std::string kExchange = "exchange";
const static std::string kType = "type";
const static std::string kMarket = "market";

inline std::string sBoolean(bool isTrue) { return isTrue ? "true" : "false"; }

enum class TickerType : uint8_t { EQUITY, INDEX, WARRANT, ODDLOT };
const static std::map<TickerType, std::string> sTickerType = {
    {TickerType::EQUITY, "EQUITY"},
    {TickerType::INDEX, "INDEX"},
    {TickerType::WARRANT, "WARRANT"},
    {TickerType::ODDLOT, "ODDLOT"}};

enum class ExchangeType : uint8_t { TWSE, TPEx };
const static std::map<ExchangeType, std::string> sExchangeType = {
    {ExchangeType::TWSE, "TWSE"}, {ExchangeType::TPEx, "TPEx"}};

// TSE: 上市. OTC: 上櫃, ESB:興櫃一般板, TIB:臺灣創新板, PSB:興櫃戰略新板
enum class MarketType : uint8_t { TSE, OTC, ESB, TIB, PSB };
const static std::map<MarketType, std::string> sMarketType = {
    {MarketType::TSE, "TSE"},
    {MarketType::OTC, "OTC"},
    {MarketType::ESB, "ESB"},
    {MarketType::TIB, "TIB"},
    {MarketType::PSB, "PSB"}};

} // namespace fugle_realtime
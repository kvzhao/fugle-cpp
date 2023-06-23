#pragma once

#include <chrono>
#include <iomanip>
#include <map>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using namespace nlohmann;

namespace fugle_realtime {

const static std::string kExchange = "exchange";
const static std::string kType = "type";
const static std::string kMarket = "market";
const static string kTimeFrame = "timeframe";

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

struct CandleData {
  string date;
  float open;
  float high;
  float low;
  float close;
  float average;
  uint32_t volume;
};

template <typename BasicJsonType>
inline void from_json(const BasicJsonType &j, CandleData &data) {
  j.at("date").get_to(data.date);
  if (j.count("open")) {
    j.at("open").get_to(data.open);
  }
  if (j.count("close")) {
    j.at("close").get_to(data.close);
  }
  if (j.count("high")) {
    j.at("high").get_to(data.high);
  }
  if (j.count("low")) {
    j.at("low").get_to(data.low);
  }
  if (j.count("volume")) {
    j.at("volume").get_to(data.volume);
  }
  if (j.count("average")) {
    j.at("average").get_to(data.average);
  }
}

// TODO: not so useful
enum class CandleFeild : uint8_t {
  OPEN,
  HIGH,
  LOW,
  CLOSE,
  VOLUME,
  TUNROVER,
  CHANGE
};

enum class CandleTimeFrame : uint8_t {
  K_1_MIN,
  K_5_MIN,
  K_10_MIN,
  K_15_MIN,
  K_30_MIN,
  K_60_MIN,
  K_DAY,
  K_WEEK,
  K_MONTH,
};

const static std::map<CandleTimeFrame, string> sChandleTimeFrame = {
    {CandleTimeFrame::K_1_MIN, "1"},   {CandleTimeFrame::K_5_MIN, "5"},
    {CandleTimeFrame::K_10_MIN, "10"}, {CandleTimeFrame::K_15_MIN, "15"},
    {CandleTimeFrame::K_30_MIN, "30"}, {CandleTimeFrame::K_60_MIN, "60"},
    {CandleTimeFrame::K_DAY, "D"},     {CandleTimeFrame::K_WEEK, "W"},
    {CandleTimeFrame::K_MONTH, "M"},
};

struct Date {
  Date(){};
  Date(uint32_t y, uint32_t m, uint32_t d) : year(y), month(m), day(d){};
  uint32_t year = 0;
  uint32_t month = 0;
  uint32_t day = 0;
  bool isValid() const {
    bool notInit = (year == 0) && (month == 0) && (day == 0);

    // TODO: do more check
    bool valid = !notInit;

    return valid;
  }
};

inline std::string formatDate(const Date &date) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(4) << std::to_string(date.year) << "-"
     << std::setw(2) << std::to_string(date.month) << "-" << std::setw(2)
     << std::to_string(date.day);
  return ss.str();
}

inline Date getToday() {

  auto currentTime = std::chrono::system_clock::now();

  std::time_t currentTimeStamp =
      std::chrono::system_clock::to_time_t(currentTime);

  std::tm *localTime = std::localtime(&currentTimeStamp);

  uint32_t year = localTime->tm_year + 1900;
  uint32_t month = localTime->tm_mon + 1;
  uint32_t day = localTime->tm_mday;

  return Date{year, month, day};
}

} // namespace fugle_realtime
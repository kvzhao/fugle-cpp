
#pragma once
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace fugle_realtime {

inline std::string addSlashIfNeeded(const std::string &input) {
  std::string result = input;
  if (!result.empty() && result[0] != '/') {
    result = '/' + result;
  }
  return result;
}

inline std::string joinWithSlash(const std::vector<std::string> &strings) {
  std::string result;

  for (const std::string &str : strings) {
    if (!result.empty()) {
      result += "/";
    }
    result += str;
  }

  return result;
}

inline std::string
buildUrlWithQueryParams(std::string &baseUrl,
                        const std::map<std::string, std::string> &queryParams) {
  std::stringstream url;
  url << baseUrl;

  if (!queryParams.empty()) {
    url << "?";
    bool firstParam = true;

    for (const auto &param : queryParams) {
      if (!firstParam) {
        url << "&";
      }
      url << param.first << "=" << param.second;
      firstParam = false;
    }
  }

  return url.str();
}

inline std::string floatToString(float number, int precision = 2) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << number;
  return stream.str();
}

} // namespace fugle_realtime

#pragma once
#include <string>

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

} // namespace fugle_realtime
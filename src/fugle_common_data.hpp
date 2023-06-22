#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using namespace nlohmann;

namespace fugle_realtime {

inline std::string sBoolean(bool isTrue) { return isTrue ? "true" : "false"; }

} // namespace fugle_realtime
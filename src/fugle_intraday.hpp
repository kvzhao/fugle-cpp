#pragma once

#include "fugle_client_base.hpp"
#include "fugle_intraday_data.hpp"
#include <nlohmann/json.hpp>

namespace fugle_realtime {

class FugleIntraday : public FugleHttpClientBase {
public:
  FugleIntraday(const string &key);

  VolumeResponse Volumes(const VolumeParameter &param);

private:
};

} // namespace fugle_realtime
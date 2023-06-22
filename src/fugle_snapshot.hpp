
#pragma once

#include "fugle_client_base.hpp"
#include "fugle_snapshot_data.hpp"
#include <nlohmann/json.hpp>

namespace fugle_realtime {

class FugleSnapshot : public FugleHttpClientBase {
public:
  FugleSnapshot(const string &key);

  ActivesResponse Actives(const ActivesParameter &param);

private:
};

} // namespace fugle_realtime
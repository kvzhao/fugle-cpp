
#pragma once

#include "fugle_client_base.hpp"
#include "fugle_snapshot_data.hpp"
#include <nlohmann/json.hpp>

namespace fugle_realtime {

class FugleSnapshot : public FugleHttpClientBase {
  public:
    FugleSnapshot();

    ActivesResponse Actives(const ActivesParameter &param);

    MoversResponse Movers(const MoversParameter &param);

    QuotesResponse Quotes(const QuotesParameter &param);

  private:
};

} // namespace fugle_realtime
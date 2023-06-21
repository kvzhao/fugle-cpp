#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "CLI/CLI.hpp"

#include "fugle_client.hpp"

using namespace std;
using namespace fugle_terminal;

struct Args {
  string filePath = "api_key.txt";
};

int main(int argc, char **argv) {
  CLI::App app{"Fugle Terminal"};

  Args args;
  app.add_option("-f,--api-file", args.filePath, "Path to api key");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  std::ifstream apiKeyFile(args.filePath);
  if (!apiKeyFile.is_open()) {
    spdlog::error("Can not open the api key file");
    return 1;
  }
  string apiKey;
  getline(apiKeyFile, apiKey);
  spdlog::debug("Key {}", apiKey);

  FugleClient fugleClient(apiKey);

  fugleClient.Get("/intraday/ticker/2330")
      .then([](pplx::task<std::string> previousTask) {
        try {
          string responseString = previousTask.get();
          nlohmann::json json = nlohmann::json::parse(responseString);
          cout << "Response: " << json.dump(4) << std::endl;
        } catch (const std::exception &ex) {
          cerr << "Error occurred: " << ex.what() << std::endl;
        }
      })
      .wait();

  return 0;
}
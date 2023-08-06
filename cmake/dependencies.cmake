include(FetchContent)

CPMAddPackage(
    NAME spdlog
    GITHUB_REPOSITORY gabime/spdlog
    VERSION 1.7.0
)

CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.10.2
)

CPMAddPackage(
    NAME tabulate
    GITHUB_REPOSITORY p-ranav/tabulate
    VERSION 1.0
)

CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11
    GIT_TAG v2.11.1
)

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.2.0
)
FetchContent_MakeAvailable(cli11)

find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
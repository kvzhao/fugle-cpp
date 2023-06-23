cmake_minimum_required(VERSION 3.18)

project(fugleTerminal)

set(CMAKE_CXX_STANDARD 17)
set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT(EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})


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

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.2.0
)
include(FetchContent)
FetchContent_MakeAvailable(cli11)

find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

# Add Thirdpary libs
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/SQLiteCpp)
add_subdirectory(thirdparty/TermOx EXCLUDE_FROM_ALL)

file(
    GLOB_RECURSE
    SOURCES
    "project/*.cpp"
)

include_directories(project)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    spdlog
    tabulate
    cpprestsdk::cpprest
    OpenSSL::SSL
    OpenSSL::Crypto
    CLI11::CLI11
    nlohmann_json
    SQLiteCpp
    TermOx
)
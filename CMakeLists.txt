cmake_minimum_required(VERSION 3.18)

project(fugle_terminal)

set(CMAKE_CXX_STANDARD 17)
set(CPM_DOWNLOAD_VERSION 0.27.2)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT(EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

find_package(cpprestsdk REQUIRED)

CPMAddPackage(
    NAME spdlog
    GITHUB_REPOSITORY gabime/spdlog
    VERSION 1.7.0
)

include(FetchContent)
FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.2.0
)

FetchContent_MakeAvailable(cli11)

CPMAddPackage(
    NAME tabulate
    GITHUB_REPOSITORY p-ranav/tabulate
    VERSION 1.0
)

find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    spdlog
    tabulate
    cpprestsdk::cpprest
    OpenSSL::SSL
    OpenSSL::Crypto
    CLI11::CLI11
)
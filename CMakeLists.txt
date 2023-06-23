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
include(cmake/dependencies.cmake)
add_subdirectory(thirdparty/SQLiteCpp)
add_subdirectory(thirdparty/TermOx EXCLUDE_FROM_ALL)

# file(
#     GLOB_RECURSE
#     SOURCES
#     "project/*.cpp"
# )

add_subdirectory(project)

# add_executable(
#     ${PROJECT_NAME}
#     ${SOURCES}
# )

# target_link_libraries(
#     ${PROJECT_NAME}
#     spdlog
#     tabulate
#     cpprestsdk::cpprest
#     OpenSSL::SSL
#     OpenSSL::Crypto
#     CLI11::CLI11
#     nlohmann_json
#     SQLiteCpp
#     TermOx
# )
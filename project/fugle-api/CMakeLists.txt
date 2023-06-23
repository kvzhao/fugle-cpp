
set(TARGET_NAME fugle-api)

set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(
    GLOB_RECURSE
    TARGET_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

message(${TARGET_SOURCES})

if(BUILD_SHARED_LIBS)
    add_library(${TARGET_NAME} SHARED ${TARGET_SOURCES})
else()
    add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES})
endif()

target_link_libraries(
    ${TARGET_NAME}
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
set(TARGET_NAME rtmonitor)

set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/realtime_monitor.cpp
)

add_executable(${TARGET_NAME} ${TARGET_SOURCES})

target_compile_options(${TARGET_NAME} PRIVATE ${compiler_options})

target_link_options(${TARGET_NAME} PRIVATE ${linker_flags})

target_include_directories(${TARGET_NAME}
    PRIVATE
    ${TARGET_INCLUDE_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/../fugle-api/include
)

set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(
    ${TARGET_NAME}
    spdlog
    nlohmann_json
    cpprestsdk::cpprest
    tabulate
    CLI11::CLI11
    ${CMAKE_BINARY_DIR}/export_libs/libfugle.a
)

set(TARGET_NAME stockdb)

set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TARGET_EXPORT_FOLDER ${CMAKE_BINARY_DIR}/export_libs)

file(
    GLOB_RECURSE
    TARGET_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_SHARED_LIBS)
    add_library(${TARGET_NAME} SHARED ${TARGET_SOURCES})
else()
    add_library(${TARGET_NAME} STATIC ${TARGET_SOURCES})
endif()

target_compile_options(${TARGET_NAME} PRIVATE ${compiler_options})

target_link_options(${TARGET_NAME} PRIVATE ${linker_flags})

set_target_properties(${TARGET_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${TARGET_EXPORT_FOLDER}
    LIBRARY_OUTPUT_DIRECTORY ${TARGET_EXPORT_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${TARGET_EXPORT_FOLDER}
    INCLUDE_DIRECTORIES ${TARGET_INCLUDE_FOLDER}
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${TARGET_INCLUDE_FOLDER}
)

target_link_libraries(
    ${TARGET_NAME}
    spdlog
    nlohmann_json
    SQLiteCpp
)

add_subdirectory(fugle-api)

add_subdirectory(testbed)

add_subdirectory(rtmonitor)

add_subdirectory(sample-pybind)

# make install
install(TARGETS
    fugle
    testbed
    rtmonitor
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(
    DIRECTORY
    ${CMAKE_SOURCE_DIR}/modules/fugle-api/include
    DESTINATION
    include/fugle
)
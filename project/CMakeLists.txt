
add_subdirectory(fugle-api)

add_subdirectory(testbed)

add_subdirectory(rtmonitor)

# make install
install(TARGETS
    fugle
    testbed
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(
    DIRECTORY
    ${CMAKE_SOURCE_DIR}/project/fugle-api/include
    DESTINATION
    include/fugle
)
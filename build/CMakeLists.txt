cmake_minimum_required (VERSION 2.6)

set (PROJECT Ivideon)

project (${PROJECT})

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/../bin
    )
set(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/../bin
    )
set(
    CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}/../lib
    )

add_subdirectory (SRC/commandhandler)
add_subdirectory (SRC/led)
add_subdirectory (SRC/client)
add_subdirectory (SRC/server)

cmake_minimum_required (VERSION 2.6)
add_definitions(-std=c++11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project (algorithms)

file( GLOB SOURCE_FILES *.cpp )
foreach( source_file ${SOURCE_FILES} )
    get_filename_component( source_filename ${source_file} NAME)
    string( REPLACE ".cpp" "" target_name ${source_filename} )
    add_library( ${target_name} ${source_file} )
    # Make sure YourLib is linked to each app
    # target_link_libraries( ${testname} YourLib )
endforeach( source_file *.cpp )
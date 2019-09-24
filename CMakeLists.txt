cmake_minimum_required(VERSION 3.5)
project(algorithms-explained)

# Macro for listing subdirectories
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH (child ${children})
        IF (IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF ()
    ENDFOREACH ()
    SET(${result} ${dirlist})
ENDMACRO()

# Set all the globals
IF (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
ELSE ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
ENDIF ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")


set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
    add_definitions(-DGOOGLETEST_USE)
    add_subdirectory(googletest)
    set(GOOGLETEST_USE TRUE)
else ()
    set(GOOGLETEST_USE FALSE)
endif ()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/gnuplot-iostream)
    add_definitions(-DGNUPLOT_USE)
    include_directories(gnuplot-iostream)

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lboost_iostreams -lboost_system -lboost_filesystem")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_iostreams -lboost_system -lboost_filesystem")
    set(GNUPLOT_USE TRUE)
else ()
    set(GNUPLOT_USE FALSE)
endif ()


# Just add all to single lib, make it easier
file(GLOB ALL_CC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS */*.cc)
add_library(all_algorithms ${ALL_CC_FILES})

# Add all the tests in subdirs
SUBDIRLIST(ALL_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ALL_DIRS})
foreach (LIB_FOLDER ${ALL_DIRS})
    message(${LIB_FOLDER})
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_FOLDER}/tests)
        set(CURRENT_TEST_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/${LIB_FOLDER}/tests)
        file(GLOB CURRENT_LIB_TESTS RELATIVE ${CURRENT_TEST_PREFIX} CONFIGURE_DEPENDS ${CURRENT_TEST_PREFIX}/*.cc)
        foreach (TEST_SOURCE ${CURRENT_LIB_TESTS})
            string(REPLACE ".cc" "" original_name ${TEST_SOURCE})
            add_executable( ${LIB_FOLDER}-${original_name} ${CURRENT_TEST_PREFIX}/${TEST_SOURCE})
            target_link_libraries(${LIB_FOLDER}-${original_name} gtest gtest_main gmock all_algorithms)
        endforeach (TEST_SOURCE)
    endif ()
endforeach (LIB_FOLDER)

## Add base lib, which will be linked against all other libs
#file(GLOB BASE_LIB_SOURCES base/*.cc)
#add_library(base BASE_LIB_SOURCES)
#include_directories(base)
#
## Add all other libs
#SUBDIRLIST(ALL_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
#foreach(LIB_FOLDER ${ALL_DIRS})
#    file(GLOB CURRENT_LIB_SOURCES ${LIB_FOLDER}/*.cc)
#    add_library(${LIB_FOLDER} ${CURRENT_LIB_SOURCES})
#    target_link_library
#endforeach(LIB_FOLDER)

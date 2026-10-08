cmake_minimum_required(VERSION 3.26)
project(PerformancePortablePatterns)

include(FetchContent)
enable_testing()

find_package(GTest 1.10 CONFIG)
if(GTest_FOUND)
  message(STATUS "Gtest found")
else()
  message(STATUS "Gtest not found: fetching")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  )
  FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(patterns)

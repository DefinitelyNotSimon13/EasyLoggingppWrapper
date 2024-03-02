
cmake_minimum_required(VERSION 3.22)

set(CMAKE_BUILD_TYPE MinSizeRel)

project(LoggingWrapper
  VERSION 0.3
  DESCRIPTION "A simple wrapper for Easylogging++")

set (CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

add_library(LoggingWrapper LoggingWrapper.cpp easylogging++.cc)

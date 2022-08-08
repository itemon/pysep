# parse pinyin seq, separate syllable by space

cmake_minimum_required(VERSION 3.7)
project(pysep C)

message("build pysep...")
set(CMAKE_BUILD_TYPE Debug)

add_library(pinyin_parser STATIC pinyin_parser.c)
target_include_directories(pinyin_parser PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(pysep pysep.c)
target_include_directories(pysep PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(pysep PUBLIC pinyin_parser)

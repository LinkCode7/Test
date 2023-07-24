cmake_minimum_required(VERSION 3.12)
project(Test)

set(CMAKE_CXX_STANDARD 17)

# 要测试boost库，请指定头文件、库的路径
set(TEST_BOOST_RTREE OFF)

if(TEST_BOOST_RTREE)
set(Boost_INCLUDE_DIR ../boost_1_79_0)
find_package(Boost REQUIRED)
set(Boost_LIBRARY_DIRS ../boost_1_79_0/stage/lib) # 在find_package之后

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)

add_compile_definitions(TEST_BOOST_RTREE)
endif()

# 工程文件
aux_source_directory(./ SRCS)
aux_source_directory(./algorithm SRCS)
aux_source_directory(./boost SRCS)
aux_source_directory(./boost/filesystem SRCS)
aux_source_directory(./boost/graph SRCS)
aux_source_directory(./boost/regex SRCS)
aux_source_directory(./boost/spatial_index SRCS)
aux_source_directory(./c SRCS)
aux_source_directory(./c/BCPL SRCS)
aux_source_directory(./cpp SRCS)
aux_source_directory(./cpp/basic SRCS)
aux_source_directory(./cpp/cpp0x SRCS)
aux_source_directory(./cpp/mechanism SRCS)
aux_source_directory(./cpp/STL SRCS)
aux_source_directory(./esri SRCS)
aux_source_directory(./graphical SRCS)
aux_source_directory(./other SRCS)
aux_source_directory(./utility SRCS)

# 打印SRC中列表信息
message(STATUS "SRC = ${SRCS}")

add_executable(${PROJECT_NAME} ${SRCS})

if(TEST_BOOST_RTREE)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

# 预编译头
include_directories(.)
target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:./pch.h>")

cmake_minimum_required(VERSION 3.10)
project(GameOfLife C)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
add_executable(GameOfLife_Serial Utils.h Utils.c serial.c)

add_executable(GameOfLife_Cluster Utils.h Utils.c cluster.c)


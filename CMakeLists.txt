cmake_minimum_required(VERSION 3.6)
project(enhancedUdpClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SocketClient.cpp SocketClient.h ../libs/netutils.c ../libs/netutils.h FileWriter.cpp FileWriter.h)
add_executable(enhancedUdpClient ${SOURCE_FILES})
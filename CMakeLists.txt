cmake_minimum_required(VERSION 3.6)
project(enhancedUdpClient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SocketClient.cpp SocketClient.h ./libs/netutils.c ./libs/netutils.h FileWriter.cpp FileWriter.h libs/DataPacket.h libs/AckPacket.h Checksum.cpp Checksum.h Serializer.cpp Serializer.h libs/DataPacket.cpp libs/AckPacket.cpp)
add_executable(enhancedUdpClient ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.6)
project(enhancedUdpClient)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_LINK_LIBS libUdpSocketLib.so)
link_directories(../../UdpSocketLib/cmake-build-debug)
##set ( PROJECT_LINK_LIBS libtestStudent.a )    # static lib

set(SOURCE_FILES main.cpp SocketClient.cpp SocketClient.h FileWriter.cpp FileWriter.h)

# add the include folder that will ahve the headers
include_directories(../../UdpSocketLib/include)

add_executable(enhancedUdpClient ${SOURCE_FILES})

# add the library for linking
target_link_libraries(enhancedUdpClient ${PROJECT_LINK_LIBS} )
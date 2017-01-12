cmake_minimum_required(VERSION 3.6)
project(enhancedUdpClient)

set(CMAKE_CXX_STANDARD 11)

# NOTE change to the directory that matches the file directory
set(Udp_Lib_Directory ../../clg_ReliableUdp_Lib)
set(PROJECT_LINK_LIBS libUdpSocketLib.so)

link_directories(${Udp_Lib_Directory}/cmake-build-debug)
##set ( PROJECT_LINK_LIBS libtestStudent.a )    # static lib

find_package(Boost COMPONENTS system filesystem thread REQUIRED)
set(SOURCE_FILES main.cpp ClientSocket.cpp ClientSocket.h FileWriter.cpp FileWriter.h globaldefs.h GbnReceiver.cpp GbnReceiver.h FileTransfer.cpp FileTransfer.h)

# add the include folder that will ahve the headers
include_directories(${Udp_Lib_Directory}/include)

add_executable(enhancedUdpClient ${SOURCE_FILES})

# add the library for linking
target_link_libraries(enhancedUdpClient ${PROJECT_LINK_LIBS} ${Boost_SYSTEM_LIBRARY} ${Boost_LIBRARIES} ${BOOST_THREAD_USE_LIB})



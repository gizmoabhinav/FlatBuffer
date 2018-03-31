cmake_minimum_required(VERSION 3.4.1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(. flatbuffers)

add_library(hello-jni SHARED
            hello-jni.cpp)

# Include libraries needed for hello-jni lib
target_link_libraries(hello-jni
                      android
                      log)

cmake_minimum_required(VERSION 3.9)
project(OS4)

set(CMAKE_CXX_STANDARD 17)

add_executable(OS4 main.cpp News.cpp News.h LockedQueue.cpp LockedQueue.h BoundedBuffer.cpp BoundedBuffer.h CoEditor.h CoEditor.cpp Dispatcher.cpp Dispatcher.h FlowManager.cpp FlowManager.h Producer.cpp Producer.h ScreenManager.h ScreenManager.cpp)
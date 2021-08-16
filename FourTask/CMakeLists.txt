cmake_minimum_required(VERSION 3.0.0)
project(FourTask VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(FourTask main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

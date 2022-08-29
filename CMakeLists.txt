cmake_minimum_required(VERSION 3.0.0)
project(AP VERSION 0.1.0)

include(CTest)
enable_testing()
add_compile_options(-lpthread)
add_executable(Server main.cpp Iris.cpp)
add_executable(Client tcp_client.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

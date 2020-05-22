cmake_minimum_required(VERSION 3.17)
project(sdl200521)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME}  SDL2::SDL2)

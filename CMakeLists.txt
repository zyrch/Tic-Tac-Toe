cmake_minimum_required(VERSION 3.6)
project(Tic_Tac_Toe)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")



include_directories(${PROJECT_SOURCE_DIR}/include libSDL2-2.0.so.0)
link_directories(/usr/local/lib)

set(SOURCE_FILES main.cpp Headers/Screen.h src/Screen.cpp)
add_executable(Tic_Tac_Toe ${SOURCE_FILES})

target_link_libraries(Tic_Tac_Toe SDL2)
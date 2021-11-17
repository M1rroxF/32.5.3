cmake_minimum_required(VERSION 3.19)

add_executable(skillbox main.cpp
               ${INCLUDE_FOLDER}/Graphs.h)
target_include_directories(skillbox PUBLIC ${INCLUDE_FOLDER})
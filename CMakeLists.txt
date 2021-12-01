cmake_minimum_required(VERSION 3.19)
project(skillbox VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

set(INCLUDE_FOLDER ${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)

target_link_libraries(skillbox PRIVATE nlohmann_json::nlohmann_json)
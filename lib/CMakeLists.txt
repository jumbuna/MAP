cmake_minimum_required(VERSION 3.19)

project(MAP VERSION 1.0 LANGUAGES C)

add_library(map SHARED map.c)

target_include_directories(map INTERFACE "${CMAKE_SOURCE_DIR}/include")

install(TARGETS map DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

install(FILES "${CMAKE_SOURCE_DIR}/include/map.h" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/map")

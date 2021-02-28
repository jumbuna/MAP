cmake_minimum_required(VERSION 3.19)

project(MAP VERSION 1.0 LANGUAGES C)

add_library(map SHARED map.c)

target_include_directories(map PUBLIC "${CMAKE_SOURCE_DIR}/include" "/usr/local/include")

target_link_directories(map PUBLIC "${CMAKE_INSTALL_PREFIX}/lib")

target_link_libraries(map PUBLIC "allocator")

install(TARGETS map DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

install(FILES "${CMAKE_SOURCE_DIR}/include/map.h" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/map")


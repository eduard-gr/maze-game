cmake_minimum_required(VERSION 3.10)

project(maze)

include_directories(src)

set(LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs")

include_directories("${LIBS_PATH}/include")
include_directories("${LIBS_PATH}/include/pdcurses")

IF(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wno-narrowing")
    link_directories("${LIBS_PATH}/unix/pdcurses/")
ELSE (WIN32)
    set(CMAKE_CXX_FLAGS "/std:c++latest")
    link_directories("${LIBS_PATH}/windows/pdcurses/")
ENDIF (UNIX)

add_library(menu src/menu.cpp)
add_library(maze src/maze.cpp)

add_executable(editor src/editor.cpp)
add_executable(game src/game.cpp)

    
IF(UNIX)
    target_link_libraries(editor maze menu m ncurses)
    target_link_libraries(game maze menu m ncurses)
ELSE (WIN32)
    target_link_libraries(editor pdcurses.lib)
    target_link_libraries(game pdcurses.lib)
ENDIF (UNIX)

set(CMAKE_BUILD_TYPE Debug)

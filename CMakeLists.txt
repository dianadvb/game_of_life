cmake_minimum_required(VERSION 3.16)

project(game_of_life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game_of_life main.cpp)

include(GNUInstallDirs)
install(TARGETS game_of_life
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

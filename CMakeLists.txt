cmake_minimum_required (VERSION 3.0.0)
project(nes_emu)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(nes_emu_core)
add_subdirectory(frontend_cli)

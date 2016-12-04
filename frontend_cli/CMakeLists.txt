cmake_minimum_required(VERSION 3.0.0)

set(FRONTEND_CLI main.cpp)

add_executable(frontend_cli ${FRONTEND_CLI})
target_link_libraries(frontend_cli nes_emu_core)

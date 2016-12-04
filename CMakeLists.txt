cmake_minimum_required (VERSION 3.0.0)
project(nes_emu)

set(NES_EMU main.cpp
        nes.cpp
        nes.h
        nes_apu.cpp
        nes_cpu.cpp
        nes_cpu_decode.cpp
        nes_cpu_disassembly.cpp
        nes_cpu_eval.cpp
        nes_ppu.cpp
        nes_mappers.h
        nes_mmu.cpp
        nes_mapper_mmc1.cpp
        nes_mapper_nrom.cpp)

add_executable(nes_emu ${NES_EMU})

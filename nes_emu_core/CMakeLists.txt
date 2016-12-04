cmake_minimum_required(VERSION 3.0.0)

set(NES_EMU_CORE nes.cpp
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

add_library(nes_emu_core STATIC ${NES_EMU_CORE})
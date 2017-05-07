# nes_emu
Yet another NES/FC Emulator that aims to be super precise


This is WIP project. At this point, CPU (2A03/7) should be working fairly well.
The CPU has passed the NESTEST for official instructions, and unofficial instructions will be implemented later.
Only NROM mapper is implemented at this point. MMC3 is in code, but it won't work correctly.
NSF detection is working, but only detection.

Currently only cycle-by-cycle executor is implemented.
When PPU and few common mappers are done, other executor will be implemented.

#include "nes.h"
#include <iostream>
#include <exception>

using namespace std;

NES::MMU::MMU(NES* parent) {
    nes=parent;
    nes->printInfo("MMU", "Default MMU Core is loaded");
}

void NES::MMU::loadFileNES(FILE* f) {
    uint8_t header[16];
    fread((void*)header, sizeof(uint8_t), 16, f);
    prg_rom_units = header[4];
    chr_rom_units = header[5];
    nes->printInfo("MMU", "PRG-ROM size = "+itos(prg_rom_units, false)+" units");
    nes->printInfo("MMU", "CHR-ROM size = "+itos(chr_rom_units, false)+" units");
    int flag = header[6];
    flag_vert_mirror = flag&1;
    flag_hori_mirror = !flag_vert_mirror;
    flag_four_screen_mirror = (flag&0b1000) && (!(flag&0b1));
    flag_has_prg_ram = flag&0b10;
    if(flag&0b100) {
        nes->printWarn("MMU", "This rom has trainer data. Skipping it.");
        fseek(f, 512, SEEK_CUR); //Skip trainer data
    }
    mapper=(flag&0b11110000) >> 4; //TODO: Implement correct detection
    //Other flags are skipped for now
    prg_ram_units = 1;//(prg_ram_units<1)?(1):(prg_ram_units);
    prg_rom = new uint8_t*[prg_rom_units];
    for(int i=0; i<prg_rom_units; i++)
        prg_rom[i] = new uint8_t[16*1024];
    for(int i=0; i<prg_rom_units; i++)
        fread(prg_rom[i], 1, 16*1024, f);
    nes->printInfo("MMU", "Successfully read PRG-ROM");
    if(chr_rom_units != 0) {
        chr_rom = new uint8_t*[prg_ram_units];
        for(int i=0; i<chr_rom_units; i++)
            chr_rom[i] = new uint8_t[8*1024];
        for(int i=0; i<chr_rom_units; i++)
            fread(chr_rom[i], 1, 16*1024, f);
        nes->printInfo("MMU", "Successfully read CHR-ROM");
    } else
        nes->printInfo("MMU", "This rom uses CHR-RAM"); //Mapper's job
}

void NES::MMU::loadFileNSF(FILE* f) {
}

uint8_t NES::MMU::read(unsigned int addr) {
    if(addr==0x2002)
        return nes->ppu->readLatch(2);
    else if(addr==-1) {
        throw "Tried reading A register through MMU. This should be fixed!";
        nes->printWarn("MMU", "Tried reading from register A through MMU.");
        return temporaryValue; //The trick...
    }
    else if(addr<0x2000)
        return ram[addr%0x800];
    else if(addr<0x4000)
        return nes->ppu->readLatch(addr);
    else if(addr<0x4020)
        return nes->apu->readAPU(addr);
    else
        return readPRG(addr);
}

void NES::MMU::write(unsigned int addr, uint8_t data) {
    //Should not write to A through MMU
    if(addr==-1) {
        nes->printWarn("MMU", "Tried writing to A through MMU. (Most likely by store instruction)");
        nes->cpu->A=data;
    }
    else if(addr<0x2000)
        ram[addr%0x800]=data;
    else if(addr<0x4000)
        nes->ppu->writeLatch(addr, data);
    else if(addr<0x4020)
        nes->apu->writeAPU(addr, data);
    else
        writePRG(addr, data);
}

void NES::MMU::reset() {
    wroteAPU=false;
}
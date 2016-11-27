#include <string>
#include "nes.h"
#include "nes_mappers.h"

using namespace std;

void NROM::reset() {
    string type="NROM-";
    if(prg_rom_units==1)
        type+="128";
    else if(prg_rom_units==2)
        type+="256";
    else
        type+="???";
    nes->printInfo("MMU", "Mapper Type : "+type);
}

uint8_t NROM::readPRG(unsigned int addr) {
    addr-=0x8000;
    if(addr < 0x4000 || prg_rom_units==1)
        return prg_rom[0][addr%0x4000];
    else
        return prg_rom[1][addr%0x4000];
}

uint8_t NROM::readCHR(unsigned int addr) {
    switch(mapper) {
        case 0:
            return chr_rom[0][addr];
            break;
    }
}

void NROM::writePRG(unsigned int addr, uint8_t data) {
    switch(mapper) {
        case 0:
            nes->printError("MMU", "Attemped writing to NROM. RAM on NROM is not supported currently.");
    }
}
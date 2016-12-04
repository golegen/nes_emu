#include <string>
#include "nes_mappers.h"

using namespace std;

void MMC1::reset() {
    if(prg_rom_units>=32)
        subtype=1;
    else if(chr_rom_units>=2)
        subtype=0;
    else
        subtype=2;
    //TODO: Search where should subtype=3 go
    string typestr = "Mapper type: MMC1";
    switch(subtype) {
    case 0:
        break;
    case 1:
        typestr+=" (SUROM variant)";
        break;
    case 2:
        typestr+=" (SXROM variant)";
        break;
    }
    prg_ram = new uint8_t*[prg_ram_units];
    for(int i=0; i<prg_ram_units; i++)
        prg_ram[i]=new uint8_t[0x2000];
    prg_bank_mode = 3;
    cpu_map[0]=0;
    cpu_map[1]=0;
    cpu_map[2]=prg_rom_units-1;
    ppu_map[0]=0;
    ppu_map[1]=0;
    nes->printInfo("MMU", typestr);
}

uint8_t MMC1::readPRG(unsigned int addr) {
    /*
     * CPU $6000-$7FFF: 8 KB PRG RAM bank, fixed on all boards but SOROM and SXROM
     * CPU $8000-$BFFF: 16 KB PRG ROM bank, either switchable or fixed to the first bank
     * CPU $C000-$FFFF: 16 KB PRG ROM bank, either fixed to the last bank or switchable
     */
    if(addr<0x6000)
        nes->printWarn("MMU", "Read attemp with MMC1 on address="+itos(addr));
    else if(addr<0x8000)
        return prg_ram[cpu_map[0]][addr-0x6000];
    else if(addr<0xC000)
        return prg_rom[cpu_map[1]][addr-0x8000];
    else
        return prg_rom[cpu_map[2]][addr-0xC000];
    return 0;
}

void MMC1::writePRG(unsigned int addr, uint8_t data) {
    if(addr<0x6000)
        nes->printWarn("MMU", "Write attemp with MMC1 on address="+itos(addr));
    else if(addr<0x8000)
        prg_ram[cpu_map[0]][addr-0x6000]=isWritable ? data : prg_ram[cpu_map[0]][addr-0x6000];
    else if(data&0x40)
        shift_register=1;
    else {
        shift_register<<=1;
        shift_register|=data&1;
    }
    if(shift_register&0x20) {
        if(addr<0x8000)
            nes->printWarn("MMU", "Register write on invalid address");
        else {
            int result = 0;
            for(int i=0; i<5; i++) {
                result|=shift_register&1;
                shift_register>>=1;
                result<<=1;
            }
            if(addr<0xA000) {
                mirroring = result&0b11;
                result>>=2;
                prg_bank_mode = result&0b11;
                result>>=2;
                chr_bank_mode = result&0b1;
            } else if(addr<0xC000) {
                if(chr_bank_mode==1)
                    nes->printError("MMU", "CHR-ROM 4Kib switching is not implemented");
                else
                    ppu_map[0]=result;
            } else if(addr<0xE000) {
                if(chr_bank_mode==1)
                    nes->printError("MMU", "CHR-ROM 4Kib switching is not implemented");
            } else {
                switch(prg_bank_mode) {
                case 0:
                case 1:
                    cpu_map[1]=result&0b1110;
                    cpu_map[2]=(result&0b1110)+1;
                    break;
                case 2:
                    cpu_map[1]=0;
                    cpu_map[2]=result&0b1111;
                    break;
                case 3:
                    cpu_map[1]=result&0b1111;
                    cpu_map[2]=prg_rom_units-1;
                    break;
                }
                isWritable=result&0b10000;
            }
        }
        shift_register=1;
    }
}

uint8_t MMC1::readCHR(unsigned int addr) {
    /*
     * PPU $0000-$0FFF: 4 KB switchable CHR bank
     * PPU $1000-$1FFF: 4 KB switchable CHR bank
     */
    return chr_rom[ppu_map[addr<0x1000?0:1]][addr%0x1000];
}
#ifndef NES_MAPPERS_H
#define NES_MAPPERS_H

#include "nes.h"

class NROM : public NES::MMU {
public:
    NROM(NES* parent) : NES::MMU(parent) {
    }
    void reset() override;
    uint8_t readPRG(unsigned int addr) override;
    void writePRG(unsigned int addr, uint8_t data) override;
    uint8_t readCHR(unsigned int addr) override;
};

class MMC1 : public NES::MMU {
//private:
public:
    int cpu_map[3]; //$6000~$7FFF, $8000~$BFFF, $C000~$FFFF
    int ppu_map[2]; //$0000~$0FFF, $1000~$1FFF
    unsigned int shift_register=0, shift_state=0; //Each being register and number of shifts
    int subtype; //0=normal 1=SUROM 2=SXROM 3=CHR A16 disable PRG-RAM
    bool isWritable; //Is write on PRG-RAM enabled
    int mirroring; //0: lower bank only; 1: upper bank only; 2: vertical; 3: horizontal
    int chr_bank_mode; //0: switch 8 KB at a time; 1: switch two separate 4 KB banks
    int prg_bank_mode;
    /*
     * 0, 1: switch 32 KB at $8000, ignoring low bit of bank number;
     * 2: fix first bank at $8000 and switch 16 KB bank at $C000;
     * 3: fix last bank at $C000 and switch 16 KB bank at $8000
     */
    
public:
    MMC1(NES *parent) : NES::MMU(parent) {
    }
    void reset() override;
    uint8_t readPRG(unsigned int addr) override;
    void writePRG(unsigned int addr, uint8_t data) override;
    uint8_t readCHR(unsigned int addr) override;
};

#endif /* NES_MAPPERS_H */


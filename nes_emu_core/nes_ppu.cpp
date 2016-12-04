#include "nes.h"

NES::PPU::PPU(NES *parent) {
    nes = parent;
    mmu=parent->mmu;
    nes->printInfo("PPU", "Default PPU Core is loaded");
}

void NES::PPU::reset() {
}

void NES::PPU::tick() {
    cycle=(cycle+1)%89342;
    if(cycle==88662) {
        NMI_occurred=true;
        if(isNMIEnabled())
            nes->cpu->interrupt(false, true);
        //FIXME: Allow multiple NMI's
    }
}

uint8_t NES::PPU::readLatch(unsigned int addr) {
    switch(addr%8) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        latch&=0x1F;
        latch|=NMI_occurred?0x80:0;
        latch|=flag_spriteZeroHit?0x40:0;
        latch|=flag_spriteOverflow?0x20:0;
        NMI_occurred=false;
        break;
    case 3:
        break;
    case 4:
        return 0; //TODO: Implement this when we make actual rendering
    case 5:
        break;
    case 6:
        break;
    case 7:
        return 0; //TODO: Implement this when we make actual rendering
    }
    return latch;
}

void NES::PPU::writeLatch(unsigned int addr, uint8_t data) {
    switch(addr%8) {
    case 0:
        PPUCTRL=latch=data;
        break;
    case 1:
        PPUMASK=latch=data;
        break;
    case 2:
        latch=data;
        break;
    case 3:
        OAMADDR=latch=addr;
        break;
    case 4:
        //TODO: Implement it when rendering is implemented
        latch=addr;
        break;
    case 5:
        if(status_secondWrite)
            ScrollY=data;
        else
            ScrollX=data;
        status_secondWrite=!status_secondWrite;
        break;
    case 6:
        if(status_secondWrite) {
            PPUADDR&=0x00FF;
            PPUADDR|=data;
        }
        else {
            PPUADDR&=0xFF00;
            PPUADDR|=data<<8;
        }
        status_secondWrite=!status_secondWrite;
        break;
    case 7:
        nes->printError("PPU", "PPUDATA write: VRAM is not implemented!");
        break;
    }
}
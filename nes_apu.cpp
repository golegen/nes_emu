#include "nes.h"

using namespace std;

uint8_t NES::APU::readAPU(int addr) {
    nes->printWarn("APU", "readAPU() is stub!");
    return 0;
}

void NES::APU::writeAPU(int addr, uint8_t data) {
    switch(addr-0x4000) {
    case 0x00:
        pulse1.volume=data&0xF;
        break;
    case 0x02:
        pulse1.period&=0x700;
        pulse1.period|=0x0FF;
        break;
    case 0x03:
        pulse1.period&=0x0FF;
        pulse1.period|=0x700;
        break;
    case 0x04:
        pulse2.volume=data&0xF;
        break;
    case 0x06:
        pulse2.period&=0x700;
        pulse2.period|=0x0FF;
        break;
    case 0x07:
        pulse2.period&=0x0FF;
        pulse2.period|=0x700;
        break;
    }
}
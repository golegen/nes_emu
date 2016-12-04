#include "nes.h"
#include "nes_mappers.h"
#include <cstdio>
#include <iostream>

using namespace std;

string itos(const int value, const bool base16) {
    char tmp[33];
    snprintf(tmp, 33, base16?"%02X":"%d", value);
    return string(tmp);
}

NES::NES() {
    printDebug("NES", "Creating NES class");
    mmu=new MMU(this);
    cpu=new CPU(this);
    ppu=new PPU(this);
    apu=new APU(this);
}

void NES::tick() {
    if(curr_clock%ppu->clockdiv == 0)
        ppu->tick();
    if(curr_clock%cpu->clockdiv == 0)
        cpu->tick();
    curr_clock=(curr_clock+1)%clock;
}

void NES::openFile(string filename) {
    FILE *f = fopen(filename.c_str(), "rb");
    if(f==nullptr) {
        clog << "No such file or directory [" << filename << "] found";
        return;
    }
    uint8_t header[16];
    fread(header, sizeof(uint8_t), 16, f);
    rewind(f);
    if(header[0]=='N' && header[1]=='E' && header[2]=='S' && header[3]==0x1A) {
        loadMapper((header[6]&0b11110000) >> 4);
        mmu->loadFileNES(f);
        printInfo("NES", "Loaded a NES rom (game)");
    } else if(header[0]=='N' && header[1]=='E' && header[2]=='S' && header[3]=='M' && header[4]==0x1A) {
        //mmu->loadFileNSF(f);
        //printInfo("NES", "Loaded a NSF rom (music)");
        printError("NES", "NSF playback is currently not suported!");
    } else {
        printError("NES", "Unknown file format!");
    }
}

void NES::loadMapper(const int mapper) {
    //TODO: Make this flexible with plugin-system
    MMU* original = mmu;
    if(mapper>=0)
        printInfo("NES", "Mapper id="+itos(mapper));
    switch(mapper) {
    case 0: //NROM
        mmu = new NROM(this);
        break;
    case 1: //MMC1
        mmu = new MMC1(this);
        break;
    default:
        printError("NES", "Unknown mapper id="+itos(mapper, false));
        mmu = new MMU(this);
        break;
    }
    delete original;
    cpu->mmu = mmu;
    apu->mmu = mmu;
    ppu->mmu = mmu;
}

void NES::printError(std::string part, std::string msg) {
    cerr << "[ERROR] [NES:" << part << "] : " << msg << "\n\r";
}

void NES::printWarn(std::string part, std::string msg) {
    cerr << "[WARN]  [NES:" << part << "] : " << msg << "\n\r";
}

void NES::printDebug(std::string part, std::string msg) {
    cout << "[DEBUG] [NES:" << part << "] : " << msg << "\n\r";
}

void NES::printInfo(std::string part, std::string msg) {
    cout << "[INFO]  [NES:" << part << "] : " << msg << "\n\r";
}

/*void ticker(NES * nes) {
    while(!nes->running);
    while(nes->running) {
        this_thread::yield(); //Should sleep instead of yield
        nes->tick();
    }
}*/

void NES::hardReset() {
    mmu->reset();
    cpu->hardReset();
    mmu->write(0x4015, 0);
    ppu->reset();
    mmu->wroteAPU=false;
}

void NES::start() {
}

void NES::resume() {
    //Do something
    //tick_thread = new thread(ticker, this);
    running=true;
}

void NES::softReset() {
    cpu->softReset();
    mmu->write(0x4015, 0);
    ppu->reset();
    mmu->reset();
}

void NES::pause() {
    running=false;
    //tick_thread->join();
    //Do something
}

void NES::stop() {
}
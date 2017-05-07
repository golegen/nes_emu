#include "nes.h"
#include <iostream>

using namespace std;

NES::CPU::CPU(NES *parent) {
    nes=parent;
    mmu=parent->mmu;
    nes->printInfo("CPU", "Default CPU Core is loaded");
}

void NES::CPU::hardReset() {
    A=0;
    X=0;
    Y=0;
    P=0x34;
    S=0xFD;
    PC(mmu->read(0xFFFC) | (mmu->read(0xFFFD)<<8));
}

void NES::CPU::softReset() {
    S -= 3;
    setFlag(CPU::OP::I);
}

//Let's be accurate later :)
void NES::CPU::tick() {
    if(nowCycle==0) {
        ins=mmu->read(PC());
        decode();
        char msg[128];
        sprintf(msg, "[PC=$%04X, A=$%02X, X=$%02X, Y=$%02X, %c%c%c%c%c%c%c%c] $%02X %s"
                , PC(), A, X, Y, getFlag(OP::N)?'N':'.', getFlag(OP::V)?'V':'.'
                , '.', '.', getFlag(OP::D)?'D':'.', getFlag(OP::I)?'I':'.'
                , getFlag(OP::Z)?'Z':'.', getFlag(OP::C)?'C':'.', mmu->read(PC()), disassembly().c_str());
        //printf("%04X\n", PC());
        nes->printDebug("CPU", msg);
        fetchAddr();
        eval();
    }
    nowCycle++;
    if(nowCycle>=cycles)
        nowCycle=0;
}

void NES::CPU::interrupt(const bool fromIns, const bool maskable) {
    if(getFlag(OP::I) && !fromIns && maskable)
        return; //IRQ is masked
    setFlag(fromIns?(OP::B):0 | OP::U);
    push(PC());
    push(P);
    if(maskable || fromIns)
        PC(mmu->read(0xFFFE) | (mmu->read(0xFFFF)<<8)); //IRQ,BRK
    else
        PC(mmu->read(0xFFFA) | (mmu->read(0xFFFB)<<8)); //NMI
    nowCycle=0; //TODO: Should effect cpu cycle properly!
}

void NES::CPU::push(uint8_t data) {
    mmu->write(0x100+S, data);
    S--;
}

uint8_t NES::CPU::peek() {
    S++;
    const int ret = mmu->read(0x100+S);
    S--;
    return ret;
}

void NES::CPU::pop() {
    S++;
}

void NES::CPU::fetchAddr() {
    const unsigned int arg1=mmu->read(PC()+1), arg2=mmu->read(PC()+1) | (mmu->read(PC()+2)<<8);
    int addr;
    readExtraCycle=false;
    writeExtraCycle=false;
    switch(addrMode) {
    case OP::abs:
        addr=arg2;
        opLength=3;
        break;
    case OP::abx:
        addr=arg2+X;
        readExtraCycle=(arg2&0xFF00) != (addr&0xFF);
        writeExtraCycle=true;
        opLength=3;
        break;
    case OP::aby:
        addr=arg2+Y;
        readExtraCycle=(arg2&0xFF00) != (addr&0xFF);
        writeExtraCycle=true;
        opLength=3;
        break;
    case OP::imp:
        mmu->writeTemporaryValue(A);
        addr = -1;
        opLength=1;
        break;
    case OP::imm:
        addr = PC()+1;
        opLength=2;
        break;
    case OP::ind:
        addr = mmu->read(arg2) | (mmu->read(arg2+1)<<8);
        opLength=3;
        break;
    case OP::izx:
        addr = mmu->read((arg1 + X) & 0xFF) + (mmu->read((arg1 + X + 1) & 0xFF) << 8);
        opLength=2;
        break;
    case OP::izy:
        addr = (mmu->read(arg1) | (mmu->read((arg1 + 1)&0xFF) << 8)) + Y;
        readExtraCycle = ((mmu->read(arg1) | (mmu->read((arg1 + 1)&0xFF)<<8))&0xFF00) != (addr&0xFF00);
        writeExtraCycle=true;
        opLength=2;
        break;
    case OP::rel:
        addr = PC() + static_cast<int8_t>(arg1) + 2;
        readExtraCycle = (PC()&0xFF00) != (addr&0xFF00);
        opLength=2;
        break;
    case OP::zp:
        addr = arg1 % 256;
        opLength=2;
        break;
    case OP::zpx:
        addr = (arg1 + X) % 256;
        opLength=2;
        break;
    case OP::zpy:
        addr = (arg1 + Y) % 256;
        opLength=2;
        break;
    }
    nowAddr=addr;
}
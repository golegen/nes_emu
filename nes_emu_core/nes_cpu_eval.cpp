#include "nes.h"

//http://obelisk.me.uk/6502/reference.html
/*#define FLAG(X,Y) (setFlag((X) ? OP::(Y) : 0))*/
#define FLAG_Z() (FLAG(this, (result & 0xFF) == 0, OP::Z))
#define FLAG_V() (FLAG(this, result > 0x7F || result < 0x80, OP::V))
#define FLAG_N() (FLAG(this, result & 0x80, OP::N))

inline void FLAG(NES::CPU* const base, const bool condition, const int flag) {
    if(condition)
        base->setFlag(flag);
    else
        base->clearFlag(flag);
}

void NES::CPU::eval() {
    int result;
    bool inc_pc=true;
    switch (op) {
    case OP::ADC:
        result = A + mmu->read(nowAddr) + (getFlag(OP::C)?1:0);
        FLAG(this, (result&0x100) != 0, OP::C);
        FLAG(this, ((A^result)&(mmu->read(nowAddr)^result)&0x80) != 0, OP::V);
        FLAG_Z();
        FLAG_N();
        A = result;
        if(readExtraCycle)
            cycles++;
        break;
    case OP::AND:
        result = A & mmu->read(nowAddr);
        FLAG_Z();
        FLAG_N();
        A = result;
        if(readExtraCycle)
            cycles++;
        break;
    case OP::ASL:
        result = (nowAddr==-1?A:mmu->read(nowAddr)) << 1;
        FLAG(this, (nowAddr==-1?A:mmu->read(nowAddr)), OP::C);
        if(nowAddr==-1)
            A = result;
        else
            mmu->write(nowAddr, result);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::BCC:
        if(!getFlag(OP::C)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BCS:
        if(getFlag(OP::C)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BEQ:
        if(getFlag(OP::Z)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BIT:
        result = mmu->read(nowAddr);
        FLAG(this, result&(1<<6), OP::V);
        FLAG(this, result&(1<<7), OP::N);
        result&=A;
        FLAG_Z();
        break;
    case OP::BMI:
        if(getFlag(OP::N)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BNE:
        if(!getFlag(OP::Z)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BPL:
        if(!getFlag(OP::N)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BRK:
        interrupt(true);
        break;
    case OP::BVC:
        if(!getFlag(OP::V)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::BVS:
        if(getFlag(OP::V)) {
            PC(nowAddr);
            cycles+=readExtraCycle?3:1;
            inc_pc=false;
        }
        break;
    case OP::CLC:
        clearFlag(OP::C);
        break;
    case OP::CLD:
        clearFlag(OP::D);
        break;
    case OP::CLI:
        clearFlag(OP::I);
        break;
    case OP::CLV:
        clearFlag(OP::V);
        break;
    case OP::CMP:
        result = A - mmu->read(nowAddr);
        FLAG(this, result > 0, OP::C);
        FLAG_Z();
        FLAG_N();
        if(readExtraCycle)
            cycles++;
        break;
    case OP::CPX:
        result = X - mmu->read(nowAddr);
        FLAG(this, result > 0, OP::C);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::CPY:
        result = Y - mmu->read(nowAddr);
        FLAG(this, result > 0, OP::C);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::DEC:
        result = mmu->read(nowAddr)-1;
        mmu->write(nowAddr, result);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::DEX:
        result = --X;
        FLAG_Z();
        FLAG_N();
        break;
    case OP::DEY:
        result = --Y;
        FLAG_Z();
        FLAG_N();
        break;
    case OP::EOR:
        result = A^mmu->read(nowAddr);
        FLAG_Z();
        FLAG_N();
        A = result;
        break;
    case OP::INC:
        result = mmu->read(nowAddr)+1;
        mmu->write(nowAddr, result);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::INX:
        result = ++X;
        FLAG_Z();
        FLAG_N();
        break;
    case OP::INY:
        result = ++Y;
        FLAG_Z();
        FLAG_N();
        break;
    case OP::JMP:
        PC(nowAddr);
        inc_pc=false;
        break;
    case OP::JSR:
        if(true) {
            const int addr = PC()+opLength-1;
            push((addr & 0xFF00)>>8); //TODO: Might be in wrong endian-ness
            push(addr & 0x00FF);
            PC(nowAddr);
            inc_pc=false;
        }
        break;
    case OP::LDA:
        A = result = mmu->read(nowAddr);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::LDX:
        X = result = mmu->read(nowAddr);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::LDY:
        Y = result = mmu->read(nowAddr);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::LSR:
        result = nowAddr==-1 ? A : mmu->read(nowAddr);
        result&=0b01111111; //To ensure bit 7 is empty. Might not be needed.
        if(result&1)
            setFlag(OP::C);
        else
            clearFlag(OP::C);
        if(nowAddr==-1)
            A = result;
        else
            mmu->write(nowAddr, result);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::NOP:
        break;
    case OP::ORA:
        result = A | mmu->read(nowAddr);
        FLAG_Z();
        FLAG_N();
        A = result;
        break;
    case OP::PHA:
        push(A);
        break;
    case OP::PHP:
        setFlag(OP::B | OP::U);
        push(P);
        break;
    case OP::PLA:
        result = A = peek();
        pop();
        FLAG_Z();
        FLAG_N();
        break;
    case OP::PLP:
        P = peek();
        pop();
        clearFlag(OP::B | OP::U);
        break;
    case OP::ROL:
        result = nowAddr==-1 ? A : mmu->read(nowAddr);
        result = (result << 1) | (result >> 7);
        if(nowAddr==-1)
            A=result;
        else
            mmu->write(nowAddr, result);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::ROR:
        result = nowAddr==-1 ? A : mmu->read(nowAddr);
        result = (result >> 1) | (result << 7);
        if(nowAddr==-1)
            A=result;
        else
            mmu->write(nowAddr, result);
        break;
    case OP::RTI:
        if(true) {
            P = peek();
            pop();
            clearFlag(OP::B | OP::U);
            const int addr = peek();
            pop();
            PC((peek()<<8) | addr);
            pop();
            inc_pc=false;
        }
        break;
    case OP::RTS:
        if(true) {
            const int addr = peek();
            pop();
            PC((peek()<<8) | addr);
            pop();
        }
        break;
    case OP::SBC:
        result = A-mmu->read(nowAddr);
        result-= getFlag(OP::C)?1:0;
        FLAG(this, (result&0x100) != 0, OP::C);
        FLAG(this, ((A^result)&(mmu->read(nowAddr)^result)&0x80) != 0, OP::V);
        FLAG_Z();
        FLAG_N();
        break;
    case OP::SEC:
        setFlag(OP::C);
        break;
    case OP::SED:
        setFlag(OP::D);
        break;
    case OP::SEI:
        setFlag(OP::I);
        break;
    case OP::STA:
        mmu->write(nowAddr, A);
        break;
    case OP::STX:
        mmu->write(nowAddr, X);
        break;
    case OP::STY:
        mmu->write(nowAddr, Y);
        break;
    case OP::TAX:
        X=A;
        FLAG(this, A==0, OP::Z);
        FLAG(this, A & 0x80, OP::N);
        break;
    case OP::TAY:
        Y=A;
        FLAG(this, A==0, OP::Z);
        FLAG(this, A & 0x80, OP::N);
        break;
    case OP::TSX:
        X=S;
        FLAG(this, S==0, OP::Z);
        FLAG(this, S & 0x80, OP::N);
        break;
    case OP::TXA:
        A=X;
        FLAG(this, X==0, OP::Z);
        FLAG(this, X & 0x80, OP::N);
        break;
    case OP::TXS:
        S=X;
        FLAG(this, X==0, OP::Z);
        FLAG(this, X & 0x80, OP::N);
        break;
    case OP::TYA:
        A=Y;
        FLAG(this, Y==0, OP::Z);
        FLAG(this, Y & 0x80, OP::N);
        break;
    }
    if(inc_pc)
        incPC();
}
#include "nes.h"

//Auto-generated! (did you expect me to write this all by hand?)
void NES::CPU::decode() {
    switch(ins) {
    case 0x00:
        op=OP::BRK;
        addrMode=OP::imp;
        cycles=7;
        break;
    case 0x01:
        op=OP::ORA;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0x02:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x03:
        op=OP::SLO;
        addrMode=OP::izx;
        cycles=8;
        break;
    case 0x04:
        op=OP::NOP;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x05:
        op=OP::ORA;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x06:
        op=OP::ASL;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x07:
        op=OP::SLO;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x08:
        op=OP::PHP;
        addrMode=OP::imp;
        cycles=3;
        break;
    case 0x09:
        op=OP::ORA;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x0A:
        op=OP::ASL;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x0B:
        op=OP::ANC;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x0C:
        op=OP::NOP;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x0D:
        op=OP::ORA;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x0E:
        op=OP::ASL;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x0F:
        op=OP::SLO;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x10:
        op=OP::BPL;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0x11:
        op=OP::ORA;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0x12:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x13:
        op=OP::SLO;
        addrMode=OP::izy;
        cycles=8;
        break;
    case 0x14:
        op=OP::NOP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x15:
        op=OP::ORA;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x16:
        op=OP::ASL;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x17:
        op=OP::SLO;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x18:
        op=OP::CLC;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x19:
        op=OP::ORA;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0x1A:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x1B:
        op=OP::SLO;
        addrMode=OP::aby;
        cycles=7;
        break;
    case 0x1C:
        op=OP::NOP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x1D:
        op=OP::ORA;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x1E:
        op=OP::ASL;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x1F:
        op=OP::SLO;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x20:
        op=OP::JSR;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x21:
        op=OP::AND;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0x22:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x23:
        op=OP::RLA;
        addrMode=OP::izx;
        cycles=8;
        break;
    case 0x24:
        op=OP::BIT;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x25:
        op=OP::AND;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x26:
        op=OP::ROL;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x27:
        op=OP::RLA;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x28:
        op=OP::PLP;
        addrMode=OP::imp;
        cycles=4;
        break;
    case 0x29:
        op=OP::AND;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x2A:
        op=OP::ROL;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x2B:
        op=OP::ANC;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x2C:
        op=OP::BIT;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x2D:
        op=OP::AND;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x2E:
        op=OP::ROL;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x2F:
        op=OP::RLA;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x30:
        op=OP::BMI;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0x31:
        op=OP::AND;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0x32:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        break;
    case 0x33:
        op=OP::RLA;
        addrMode=OP::izy;
        cycles=8;
        break;
    case 0x34:
        op=OP::NOP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x35:
        op=OP::AND;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x36:
        op=OP::ROL;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x37:
        op=OP::RLA;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x38:
        op=OP::SEC;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x39:
        op=OP::AND;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0x3A:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x3B:
        op=OP::RLA;
        addrMode=OP::aby;
        cycles=7;
        break;
    case 0x3C:
        op=OP::NOP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x3D:
        op=OP::AND;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x3E:
        op=OP::ROL;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x3F:
        op=OP::RLA;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x40:
        op=OP::RTI;
        addrMode=OP::imp;
        cycles=6;
        break;
    case 0x41:
        op=OP::EOR;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0x42:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x43:
        op=OP::SRE;
        addrMode=OP::izx;
        cycles=8;
        break;
    case 0x44:
        op=OP::NOP;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x45:
        op=OP::EOR;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x46:
        op=OP::LSR;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x47:
        op=OP::SRE;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x48:
        op=OP::PHA;
        addrMode=OP::imp;
        cycles=3;
        break;
    case 0x49:
        op=OP::EOR;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x4A:
        op=OP::LSR;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x4B:
        op=OP::ALR;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x4C:
        op=OP::JMP;
        addrMode=OP::abs;
        cycles=3;
        break;
    case 0x4D:
        op=OP::EOR;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x4E:
        op=OP::LSR;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x4F:
        op=OP::SRE;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x50:
        op=OP::BVC;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0x51:
        op=OP::EOR;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0x52:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x53:
        op=OP::SRE;
        addrMode=OP::izy;
        cycles=8;
        break;
    case 0x54:
        op=OP::NOP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x55:
        op=OP::EOR;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x56:
        op=OP::LSR;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x57:
        op=OP::SRE;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x58:
        op=OP::CLI;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x59:
        op=OP::EOR;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0x5A:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x5B:
        op=OP::SRE;
        addrMode=OP::aby;
        cycles=7;
        break;
    case 0x5C:
        op=OP::NOP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x5D:
        op=OP::EOR;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x5E:
        op=OP::LSR;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x5F:
        op=OP::SRE;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x60:
        op=OP::RTS;
        addrMode=OP::imp;
        cycles=6;
        break;
    case 0x61:
        op=OP::ADC;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0x62:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x63:
        op=OP::RRA;
        addrMode=OP::izx;
        cycles=8;
        break;
    case 0x64:
        op=OP::NOP;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x65:
        op=OP::ADC;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x66:
        op=OP::ROR;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x67:
        op=OP::RRA;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0x68:
        op=OP::PLA;
        addrMode=OP::imp;
        cycles=4;
        break;
    case 0x69:
        op=OP::ADC;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x6A:
        op=OP::ROR;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x6B:
        op=OP::ARR;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x6C:
        op=OP::JMP;
        addrMode=OP::ind;
        cycles=5;
        break;
    case 0x6D:
        op=OP::ADC;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x6E:
        op=OP::ROR;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x6F:
        op=OP::RRA;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0x70:
        op=OP::BVS;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0x71:
        op=OP::ADC;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0x72:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x73:
        op=OP::RRA;
        addrMode=OP::izy;
        cycles=8;
        break;
    case 0x74:
        op=OP::NOP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x75:
        op=OP::ADC;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x76:
        op=OP::ROR;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x77:
        op=OP::RRA;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0x78:
        op=OP::SEI;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x79:
        op=OP::ADC;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0x7A:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x7B:
        op=OP::RRA;
        addrMode=OP::aby;
        cycles=7;
        break;
    case 0x7C:
        op=OP::NOP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x7D:
        op=OP::ADC;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0x7E:
        op=OP::ROR;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x7F:
        op=OP::RRA;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0x80:
        op=OP::NOP;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x81:
        op=OP::STA;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0x82:
        op=OP::NOP;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x83:
        op=OP::SAX;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0x84:
        op=OP::STY;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x85:
        op=OP::STA;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x86:
        op=OP::STX;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x87:
        op=OP::SAX;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0x88:
        op=OP::DEY;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x89:
        op=OP::NOP;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x8A:
        op=OP::TXA;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x8B:
        op=OP::XAA;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0x8C:
        op=OP::STY;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x8D:
        op=OP::STA;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x8E:
        op=OP::STX;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x8F:
        op=OP::SAX;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0x90:
        op=OP::BCC;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0x91:
        op=OP::STA;
        addrMode=OP::izy;
        cycles=6;
        break;
    case 0x92:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0x93:
        op=OP::AHX;
        addrMode=OP::izy;
        cycles=6;
        break;
    case 0x94:
        op=OP::STY;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x95:
        op=OP::STA;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0x96:
        op=OP::STX;
        addrMode=OP::zpy;
        cycles=4;
        break;
    case 0x97:
        op=OP::SAX;
        addrMode=OP::zpy;
        cycles=4;
        break;
    case 0x98:
        op=OP::TYA;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x99:
        op=OP::STA;
        addrMode=OP::aby;
        cycles=5;
        break;
    case 0x9A:
        op=OP::TXS;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0x9B:
        op=OP::TAS;
        addrMode=OP::aby;
        cycles=5;
        break;
    case 0x9C:
        op=OP::SHY;
        addrMode=OP::abx;
        cycles=5;
        break;
    case 0x9D:
        op=OP::STA;
        addrMode=OP::abx;
        cycles=5;
        break;
    case 0x9E:
        op=OP::SHX;
        addrMode=OP::aby;
        cycles=5;
        break;
    case 0x9F:
        op=OP::AHX;
        addrMode=OP::aby;
        cycles=5;
        break;
    case 0xA0:
        op=OP::LDY;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xA1:
        op=OP::LDA;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0xA2:
        op=OP::LDX;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xA3:
        op=OP::LAX;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0xA4:
        op=OP::LDY;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xA5:
        op=OP::LDA;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xA6:
        op=OP::LDX;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xA7:
        op=OP::LAX;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xA8:
        op=OP::TAY;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xA9:
        op=OP::LDA;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xAA:
        op=OP::TAX;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xAB:
        op=OP::LAX;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xAC:
        op=OP::LDY;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xAD:
        op=OP::LDA;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xAE:
        op=OP::LDX;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xAF:
        op=OP::LAX;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xB0:
        op=OP::BCS;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0xB1:
        op=OP::LDA;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0xB2:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0xB3:
        op=OP::LAX;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0xB4:
        op=OP::LDY;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0xB5:
        op=OP::LDA;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0xB6:
        op=OP::LDX;
        addrMode=OP::zpy;
        cycles=4;
        break;
    case 0xB7:
        op=OP::LAX;
        addrMode=OP::zpy;
        cycles=4;
        break;
    case 0xB8:
        op=OP::CLV;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xB9:
        op=OP::LDA;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0xBA:
        op=OP::TSX;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xBB:
        op=OP::LAS;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0xBC:
        op=OP::LDY;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0xBD:
        op=OP::LDA;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0xBE:
        op=OP::LDX;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0xBF:
        op=OP::LAX;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0xC0:
        op=OP::CPY;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xC1:
        op=OP::CMP;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0xC2:
        op=OP::NOP;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xC3:
        op=OP::DCP;
        addrMode=OP::izx;
        cycles=8;
        break;
    case 0xC4:
        op=OP::CPY;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xC5:
        op=OP::CMP;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xC6:
        op=OP::DEC;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0xC7:
        op=OP::DCP;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0xC8:
        op=OP::INY;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xC9:
        op=OP::CMP;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xCA:
        op=OP::DEX;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xCB:
        op=OP::AXS;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xCC:
        op=OP::CPY;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xCD:
        op=OP::CMP;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xCE:
        op=OP::DEC;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0xCF:
        op=OP::DCP;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0xD0:
        op=OP::BNE;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0xD1:
        op=OP::CMP;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0xD2:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0xD3:
        op=OP::DCP;
        addrMode=OP::izy;
        cycles=8;
        break;
    case 0xD4:
        op=OP::NOP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0xD5:
        op=OP::CMP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0xD6:
        op=OP::DEC;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0xD7:
        op=OP::DCP;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0xD8:
        op=OP::CLD;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xD9:
        op=OP::CMP;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0xDA:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xDB:
        op=OP::DCP;
        addrMode=OP::aby;
        cycles=7;
        break;
    case 0xDC:
        op=OP::NOP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0xDD:
        op=OP::CMP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0xDE:
        op=OP::DEC;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0xDF:
        op=OP::DCP;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0xE0:
        op=OP::CPX;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xE1:
        op=OP::SBC;
        addrMode=OP::izx;
        cycles=6;
        break;
    case 0xE2:
        op=OP::NOP;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xE3:
        op=OP::ISC;
        addrMode=OP::izx;
        cycles=8;
        break;
    case 0xE4:
        op=OP::CPX;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xE5:
        op=OP::SBC;
        addrMode=OP::zp;
        cycles=3;
        break;
    case 0xE6:
        op=OP::INC;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0xE7:
        op=OP::ISC;
        addrMode=OP::zp;
        cycles=5;
        break;
    case 0xE8:
        op=OP::INX;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xE9:
        op=OP::SBC;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xEA:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xEB:
        op=OP::SBC;
        addrMode=OP::imm;
        cycles=2;
        break;
    case 0xEC:
        op=OP::CPX;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xED:
        op=OP::SBC;
        addrMode=OP::abs;
        cycles=4;
        break;
    case 0xEE:
        op=OP::INC;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0xEF:
        op=OP::ISC;
        addrMode=OP::abs;
        cycles=6;
        break;
    case 0xF0:
        op=OP::BEQ;
        addrMode=OP::rel;
        cycles=2;
        //Illegal
        break;
    case 0xF1:
        op=OP::SBC;
        addrMode=OP::izy;
        cycles=5;
        //Illegal
        break;
    case 0xF2:
        op=OP::KIL;
        addrMode=OP::imp;
        cycles=9;
        //Illegal
        break;
    case 0xF3:
        op=OP::ISC;
        addrMode=OP::izy;
        cycles=8;
        break;
    case 0xF4:
        op=OP::NOP;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0xF5:
        op=OP::SBC;
        addrMode=OP::zpx;
        cycles=4;
        break;
    case 0xF6:
        op=OP::INC;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0xF7:
        op=OP::ISC;
        addrMode=OP::zpx;
        cycles=6;
        break;
    case 0xF8:
        op=OP::SED;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xF9:
        op=OP::SBC;
        addrMode=OP::aby;
        cycles=4;
        //Illegal
        break;
    case 0xFA:
        op=OP::NOP;
        addrMode=OP::imp;
        cycles=2;
        break;
    case 0xFB:
        op=OP::ISC;
        addrMode=OP::aby;
        cycles=7;
        break;
    case 0xFC:
        op=OP::NOP;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0xFD:
        op=OP::SBC;
        addrMode=OP::abx;
        cycles=4;
        //Illegal
        break;
    case 0xFE:
        op=OP::INC;
        addrMode=OP::abx;
        cycles=7;
        break;
    case 0xFF:
        op=OP::ISC;
        addrMode=OP::abx;
        cycles=7;
        break;
    }
}
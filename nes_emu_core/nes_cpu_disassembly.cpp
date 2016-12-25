#include "nes.h"
#include <sstream>

using namespace std;

string NES::CPU::disassembly(unsigned int addr) {
    stringstream ret;
    addr=(addr==-1)?PC():addr;
    const uint8_t opcode=op;
    switch(opcode) {
    case OP::ORA:
        ret << "ORA";
        break;
    case OP::AND:
        ret << "AND";
        break;
    case OP::EOR:
        ret << "EOR";
        break;
    case OP::ADC:
        ret << "ADC";
        break;
    case OP::SBC:
        ret << "SBC";
        break;
    case OP::CMP:
        ret << "CMP";
        break;
    case OP::CPX:
        ret << "CPX";
        break;
    case OP::CPY:
        ret << "CPY";
        break;
    case OP::DEC:
        ret << "DEC";
        break;
    case OP::DEX:
        ret << "DEX";
        break;
    case OP::DEY:
        ret << "DEY";
        break;
    case OP::INC:
        ret << "INC";
        break;
    case OP::INX:
        ret << "INX";
        break;
    case OP::INY:
        ret << "INY";
        break;
    case OP::ASL:
        ret << "ASL";
        break;
    case OP::ROL:
        ret << "ROL";
        break;
    case OP::LSR:
        ret << "LSR";
        break;
    case OP::ROR:
        ret << "ROR";
        break;
    case OP::LDA:
        ret << "LDA";
        break;
    case OP::STA:
        ret << "STA";
        break;
    case OP::LDX:
        ret << "LDX";
        break;
    case OP::STX:
        ret << "STX";
        break;
    case OP::LDY:
        ret << "LDY";
        break;
    case OP::STY:
        ret << "STY";
        break;
    case OP::TAX:
        ret << "TAX";
        break;
    case OP::TXA:
        ret << "TXA";
        break;
    case OP::TAY:
        ret << "YAY";
        break;
    case OP::TYA:
        ret << "TYA";
        break;
    case OP::TSX:
        ret << "TSX";
        break;
    case OP::TXS:
        ret << "TXS";
        break;
    case OP::PLA:
        ret << "PLA";
        break;
    case OP::PHA:
        ret << "PHA";
        break;
    case OP::PLP:
        ret << "PLP";
        break;
    case OP::PHP:
        ret << "PHP";
        break;
    case OP::BPL:
        ret << "BPL";
        break;
    case OP::BMI:
        ret << "BMI";
        break;
    case OP::BVC:
        ret << "BVC";
        break;
    case OP::BVS:
        ret << "BVS";
        break;
    case OP::BCC:
        ret << "BCC";
        break;
    case OP::BCS:
        ret << "BCS";
        break;
    case OP::BNE:
        ret << "BNE";
        break;
    case OP::BEQ:
        ret << "BEQ";
        break;
    case OP::BRK:
        ret << "BRK";
        break;
    case OP::RTI:
        ret << "RTI";
        break;
    case OP::JSR:
        ret << "JSR";
        break;
    case OP::RTS:
        ret << "RTS";
        break;
    case OP::JMP:
        ret << "JMP";
        break;
    case OP::BIT:
        ret << "BIT";
        break;
    case OP::CLC:
        ret << "CLC";
        break;
    case OP::SEC:
        ret << "SEC";
        break;
    case OP::CLD:
        ret << "CLD";
        break;
    case OP::SED:
        ret << "SED";
        break;
    case OP::CLI:
        ret << "CLI";
        break;
    case OP::SEI:
        ret << "SEI";
        break;
    case OP::CLV:
        ret << "CLV";
        break;
    case OP::NOP:
        ret << "NOP";
        break;
    case OP::SLO:
        ret << "SLO";
        break;
    case OP::RLA:
        ret << "RLA";
        break;
    case OP::SRE:
        ret << "SRE";
        break;
    case OP::RRA:
        ret << "RRA";
        break;
    case OP::SAX:
        ret << "SAX";
        break;
    case OP::LAX:
        ret << "LAX";
        break;
    case OP::DCP:
        ret << "DCP";
        break;
    case OP::ISC:
        ret << "ISC";
        break;
    case OP::ANC:
        ret << "ANC";
        break;
    case OP::ALR:
        ret << "ALR";
        break;
    case OP::ARR:
        ret << "ARR";
        break;
    case OP::XAA:
        ret << "XAA";
        break;
    case OP::AXS:
        ret << "AXS";
        break;
    case OP::AHX:
        ret << "AHX";
        break;
    case OP::SHY:
        ret << "SHY";
        break;
    case OP::SHX:
        ret << "SHX";
        break;
    case OP::TAS:
        ret << "TAS";
        break;
    case OP::LAS:
        ret << "LAS";
        break;
    case OP::KIL:
        ret << "KIL";
        break;
    default:
        ret << "???";
    }
    const int arg1=mmu->read(addr+1), arg2 = (mmu->read(addr+1) | (mmu->read(addr+2)<<8));
    switch(addrMode) {
    case OP::imp:
        break;
    case OP::imm:
        ret << ' ' << '#' << itos(arg1);
        break;
    case OP::zp:
        ret << ' ' << "zp" << ' ' << itos(arg1);
        break;
    case OP::zpx:
        ret << ' ' << "zp,X" << ' ' << itos(arg1);
        break;
    case OP::zpy:
        ret << ' ' << "zp,Y" << ' ' << itos(arg1);
        break;
    case OP::izx:
        ret << ' ' << "(d,X)" << ' ' << itos(arg1);
        break;
    case OP::izy:
        ret << ' ' << "(d),Y" << ' ' << itos(arg1);
        break;
    case OP::abs:
        ret << ' ' << "abs" << ' ' << itos(arg2);
        break;
    case OP::abx:
        ret << ' ' << "abs+X" << ' ' << itos(arg1);
        break;
    case OP::aby:
        ret << ' ' << "abs+Y" << ' ' << itos(arg1);
        break;
    case OP::rel:
        ret << ' ' << "pc" << ((arg1>127?arg1-256:arg1)+2<0?'-':'+') << itos(abs((arg1>127 ? arg1-256 : arg1)+2));
        break;
    case OP::ind:
        ret << ' ' << '[' << itos(arg2) << ']';
        break;
    default:
        ret << ' ' << "???" << itos(arg1) << ' ' << itos(mmu->read(addr+2));
        break;
    }
    if(opcode>OP::ILL_INS)
        ret << " (illegal)";
    return ret.str();
}
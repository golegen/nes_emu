#ifndef NES_H
#define NES_H

#include <stdint.h>
#include <string>
#include <atomic>
#include <thread>

/** Base class for emulation*/
class NES {
public:
    /** Emulate CPU (2A03 or its variant) found on NES/FC.*/
    class CPU;
    /** Emulate PPU (2P03 or its variant) found on NES/FC*/
    class PPU;
    class APU;
    class MMU;

//private:
public:
    CPU *cpu;
    PPU *ppu;
    APU *apu;
    MMU *mmu;

public:
    //std::thread *tick_thread;
    int clock=21477272; //Master clock
    int curr_clock=0; //should wrap every 1 second
    std::atomic<bool> running;
    bool NSF=false; //NSF = NES Sound File
    bool debug=false;

    /** Constructs the class, including every single component it needs*/
    NES();
    void tick();
    void loadMapper(const int mapper);
    void openFile(std::string filename);
    void saveStateB(const FILE *f);
    void saveStateV(void *arr);
    void loadStateB(const FILE *f);
    void loadStateV(void *arr);
    
    void printError(std::string part, std::string msg);
    void printWarn(std::string part, std::string msg);
    void printDebug(std::string part, std::string msg);
    void printInfo(std::string part, std::string msg);
    
    void hardReset();
    void start();
    void resume();
    void softReset();
    void pause();
    void stop();
    
    bool isRunning() { return running; }
};

class NES::CPU {
//private:
public:
    NES *nes;
    NES::MMU *mmu;
    uint8_t A, X, Y, S, P, PCH, PCL, ins;
    int op, addrMode, opLength, cycles, nowCycle=0, nowAddr;
    bool readExtraCycle, writeExtraCycle;
    inline bool getFlag(int where) { return P&where; }
    inline void setFlag(int where) { P |= where; }
    inline void clearFlag(int where) { P &= ~where; }
    inline uint16_t PC() const { return (PCH<<8)+PCL; }
    inline void incPC() { if(PCL+opLength > 0xFF) PCH++; PCL+=opLength; }
    inline void PC(uint16_t x) { PCH=x>>8; PCL=x&0xFF; }
    void push(uint8_t data);
    uint8_t peek();
    void pop();
    void interrupt(const bool fromIns, const bool maskable=true);
    class OP;
    
public:
    int clockdiv=12; //or 16 in PAL

    CPU(NES *parent);
    void hardReset();
    void softReset();
    void tick();
    void decode();
    void fetchAddr();
    void eval();
    std::string disassembly(unsigned int addr=-1);
};

class NES::PPU {
//private:
public:
    NES * nes;
    NES::MMU *mmu;
    uint8_t *VRam, OAM;
    uint8_t latch; //Data bus for memory-mapped io
    bool status_secondWrite; //true if second write should come
    bool flag_spriteOverflow, flag_spriteZeroHit;
    bool isEvenFrame, NMI_occurred;
    int PPUADDR, background, cycle;
    uint8_t PPUCTRL, PPUMASK, OAMADDR;
    uint8_t ScrollX, ScrollY;

    inline int getScanline() const { return cycle/341; }
    
    inline bool isVBlank() const { return 240<getScanline() && getScanline()<261; }
    inline bool isLongSprite() const { return PPUCTRL&0x20; }
    inline int getBaseNamtableAddress() const { return 0x2000+(PPUCTRL&4)*0x400; }
    inline int getSpritePatternTable() const { return isLongSprite() ? 0 : (PPUCTRL&8?0x1000:0x0000); }
    inline int getBackgroundPatternTable() const { return (PPUCTRL&0x10)*0x1000; }
    inline bool isNMIEnabled() const { return PPUCTRL&0x80; }
    
    
public:
    int clockdiv=3;

    PPU(NES *parent);
    void reset();
    void tick();
    uint8_t readLatch(unsigned int addr);
    void writeLatch(unsigned int addr, uint8_t data);
    uint8_t readVRAM(unsigned int addr);
    void writeVRAM(unsigned int addr, uint8_t data);
    uint8_t readOAM(unsigned int addr);
    void writeOAM(unsigned int addr, uint8_t data);
};

class NES::APU {
    struct Pulse {
        int duty, volume, period; //timer==period
        int sample();
    };
    struct Triangle {
        int period;
        int sample();
    };
    struct Noise {
        int volume, period;
        bool tone_mode;
        int sample();
    };
    
//private:
public:
    NES *nes;
    NES::MMU *mmu;
    bool status[5];
    Pulse pulse1, pulse2;
    Triangle triangle;
    Noise noise;

public:
    APU(NES *parent) {
        nes=parent;
        mmu=parent->mmu;
        nes->printInfo("APU", "Default APU Core is loaded");
    }
    void tick();
    uint8_t readAPU(int addr);
    void writeAPU(int addt, uint8_t data);
};

class NES::MMU {
//private:
public:
    bool loaded;
    NES *nes;
    uint8_t ram[0x800]; //2KiB internal ram
    uint8_t temporaryValue;
    int mapper, prg_rom_units, chr_rom_units, prg_ram_units;
    uint8_t **prg_rom, **prg_ram;
    uint8_t **chr_rom, **chr_ram;
    
    bool flag_vert_mirror, flag_hori_mirror, flag_ignore_mirror, flag_four_screen_mirror;
    bool flag_has_prg_ram, flag_is_vs_unisystem, flag_is_playchoice;
    bool wroteAPU=false;

public:
    MMU(NES *parent);
    virtual void reset();
    void loadFileNES(FILE *f);
    void loadFileNSF(FILE *f);
    uint8_t read(unsigned int addr);
    void write(unsigned int addr, uint8_t data);
    inline void writeTemporaryValue(uint8_t data) { temporaryValue=data; } ///FIXME: Think of some workaround for this.
    virtual void tick() { } //Mostly for frame counters
    virtual uint8_t readPRG(unsigned int addr) {
        nes->printError("MMU", "Mapper handler is not loaded!");
    }
    virtual void writePRG(unsigned int addr, uint8_t data) {
        nes->printError("MMU", "Mapper handler is not loaded!");
    }
    virtual uint8_t readCHR(unsigned int addr) {
        nes->printError("MMU", "Mapper handler is not loaded!");
    }
};

class NES::CPU::OP {
public:
    /*
     * 00~31 : Logical and arithmetic instructions
     * 32~63 : Move instructions
     * 64~95 : Jump and Flag instructions
     * 96~127: Illegal instructions
     * 
     * 128~onwards : Reserved for future use
     */
    enum opcodes {
        ALU_INS=0,
        ORA, AND, EOR, ADC, SBC, CMP, CPX, CPY, DEC, DEX,
	DEY, INC, INX, INY, ASL, ROL, LSR, ROR,
        
        MOV_INS=32,
        LDA, STA, LDX, STX, LDY, STY, TAX, TXA, TAY, TYA,
        TSX, TXS, PLA, PHA, PLP, PHP,
        
        JMP_INS=64,
        BPL, BMI, BVC, BVS, BCC, BCS, BNE, BEQ, BRK, RTI,
        JSR, RTS, JMP, BIT, CLC, SEC, CLD, SED, CLI, SEI,
        CLV, NOP,
        
        ILL_INS=96,
        SLO, RLA, SRE, RRA, SAX, LAX, DCP, ISC, ANC, ALR,
        ARR, XAA, AXS, AHX, SHY, SHX, TAS, LAS, KIL
    };
    
    /*
     * imp = Implicit
     * imm = Immediate
     * zp  = Zero Page
     * zpx = Zero Page X-indexed
     * zpy = Zero Page Y-indexed
     * izx = X-indexed Indirect
     * izy = indirect Y-indexed 
     * abs = Absolute
     * abx = Absolute X-indexed
     * aby = Absolute Y-indexed
     * rel = Relative
     * ind = Indirect (Only used in JMP instruction)
     */
    enum addrMode {
        imp, imm, zp, zpx, zpy, izx, izy, abs, abx, aby, rel, ind
    };
    
    enum flags {
        no_flags = 0x00,
        C = 1<<0, // Carry
        Z = 1<<1, // Zero
        I = 1<<2, // Interrupt disable
        D = 1<<3, // Decimal mode
        B = 1<<4, // Break command
        U = 1<<5, // Unused. Always set.
        V = 1<<6, // Overflow
        N = 1<<7, // Negative
        all_flags = 0xFF
    };
};

std::string itos(const int value, const bool base16=true);

#endif /* NES_H */
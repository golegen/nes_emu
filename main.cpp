#include <iostream>
#include "nes.h"
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

NES *nes;
int scrwidth, scrheight;

void loop() {
    nes->cpu->ins=nes->mmu->read(nes->cpu->PC());
    nes->cpu->decode();
    nes->printDebug("CPU", "[PC=$"+itos(nes->cpu->PC())+"] $"+itos(nes->mmu->read(nes->cpu->PC()))+" "+nes->cpu->disassembly(nes->cpu->PC()));
    while(true) {
        cout << "> ";
        string str;
        cin >> str;
        if(str=="tick")
            nes->tick();
        else if(str=="step" || str==".") {
            for(int i=0; i<12; i++)
                nes->tick();
        }
        else if(str=="start")
            nes->start();
        else if(str=="stop")
            nes->stop();
        else if(str=="mov-pc") {
            int new_addr;
            scanf("%x", &new_addr);
            nes->cpu->PC(new_addr);
        }
        else if(str=="push") {
            int data;
            scanf("%x", &data);
            nes->cpu->push(data);
        }
        else if(str=="pop") {
            printf("%02X", nes->cpu->peek());
            nes->cpu->pop();
        }
        else if(str=="run") {
            while(true) {
                for(int i=0; i<12; i++)
                    nes->tick();
                if(nes->mmu->wroteAPU)
                    break;
                this_thread::sleep_for(250ms);
            }
        }
        else if(str=="quit")
            return;
    }
}

int main(int argc, char** argv) {
    nes = new NES();
    nes->openFile("/home/minary/nestest.nes");
    nes->hardReset();
    loop();
    delete nes;
    return 0;
}

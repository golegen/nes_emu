#include <iostream>
#include "../nes_emu_core/nes.h"
#include <unistd.h>
#include <chrono>
#include <thread>
#include <sstream>

#include "nestest.h"

using namespace std;

NES *nes;
int scrwidth, scrheight;

string toUpperCase(const string& str) {
    string ret;
    ret.resize(str.size());
    for(int i=0; i<str.size(); i++)
        if(97 <= str[i] && str[i] <= 122)
            ret[i] = str[i] - (char)32;
        else
            ret[i] = str[i];
    return ret;
}

string trim(string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last-first+1));
}

void loop() {
    string nowline, command;
    while(true) {
        cout << "> ";
        getline(cin, nowline);
        istringstream stream(nowline);
        stream.unsetf(ios::dec);
        stream.unsetf(ios::hex);
        stream >> command;
        command = toUpperCase(command);
        if(command == "TICK")
            nes->tick();
        else if(command == "STEP") {
            int steps = 12; // Default step; One CPU tick
            stream >> steps;
            for(int i=0; i<steps; i++)
                nes->tick();
        }
        else if(command == "JMP" || command == "JUMP") {
            uint16_t pc = nes->cpu->PC();
            stream >> pc;
            nes->cpu->PC(pc);
        }
        else if(command == "PUSH") {
            unsigned int val;
            stream >> val;
            nes->cpu->push((uint8_t)val);
        }
        else if(command == "PEEK" || command == "POP") {
            printf("%02X", nes->cpu->peek());
            if(command == "POP")
                nes->cpu->pop();
        }
        else if(command == "OPEN" || command == "LOAD") {
            string filename;
            getline(stream, filename);
            filename = trim(filename);
            nes->openFile(filename);
            nes->hardReset();
        }
        else if(command == "QUIT" || command == "EXIT")
            return;
#ifdef TEST_NESTEST
        else if(command == "RUN_NESTEST")
            test_nestest(nes);
#endif
        else
            clog << "Unrecognized command '" << command << '\'' << endl;
    }
}

int main(int argc, char** argv) {
    nes = new NES();
    loop();
    delete nes;
    return 0;
}

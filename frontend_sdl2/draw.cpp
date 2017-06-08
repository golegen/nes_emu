#include "frontend_sdl2.h"
#include <cstdint>

uint32_t screen_buffer[320][240];

void draw(SDL_Renderer *ren) {
    //TODO: Use streaming texture instead
    for(int i=0; i<320; i++) {
        for (int j = 0; j < 240; j++) {
            SDL_SetRenderDrawColor(ren, (screen_buffer[i][j]>>24)&0xFF, (screen_buffer[i][j]>>16)&0xFF, (screen_buffer[i][j]>>8)&0xFF, 0);
            SDL_RenderDrawPoint(ren, i, j);
        }
    }
}
#include "frontend_sdl2.h"
#include <cstdint>

uint32_t screen_buffer[320][240];

//TODO: Bad interface. Should not contain any static variable
void draw(SDL_Renderer *ren) {
    static SDL_Texture *tex = nullptr;
    if(tex == nullptr)
        tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 320, 240);
    void *pixels;
    int pitch;

    SDL_LockTexture(tex, nullptr, &pixels, &pitch);
    for(int i=0; i<320; i++)
        for(int j=0; j<240; j++)
            reinterpret_cast<uint32_t*>(pixels)[(pitch/4)*i + j] = screen_buffer[i][j];
    SDL_UnlockTexture(tex);
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
}
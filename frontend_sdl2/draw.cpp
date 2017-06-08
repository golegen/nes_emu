#include "frontend_sdl2.h"
#include <cstdint>

#define RGB(R,G,B) (static_cast<uint32_t>((((R)&0xFF)<<24)|(((G)&0xFF)<<16)|(((B)&0xFF)<<8)))

uint32_t screen_buffer[256][240];

void draw(SDL_Renderer *ren) {
    for(int i=0; i<256; i++)
        for(int j=0; j<240; j++)
            screen_buffer[i][j] = RGB(i, j, i*j);
    static SDL_Texture *tex = nullptr;
    if(tex == nullptr)
        tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 240, 256);
    void *pixels;
    int pitch;

    SDL_LockTexture(tex, nullptr, &pixels, &pitch);
    for(int i=0; i<256; i++)
        for(int j=0; j<240; j++)
            reinterpret_cast<uint32_t*>(pixels)[(pitch/4)*i + j] = screen_buffer[i][j];
    SDL_UnlockTexture(tex);
    SDL_RenderCopy(ren, tex, nullptr, nullptr);
}

#include "SDL.h"
#include <cstdio>
#include "frontend_sdl2.h"

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init() Error: %s", SDL_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(win == nullptr){
        printf("SDL_CreateWindow() Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr) {
        printf("SDL_CreateRender() Error: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Event event;
    bool bRunning = true;
    while(bRunning) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                bRunning = false;
                break;
            }
        }
        draw(ren);
        SDL_RenderPresent(ren);
        SDL_Delay(1); // Prevent busy-waiting
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

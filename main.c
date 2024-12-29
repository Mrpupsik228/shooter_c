//
// Created by roman on 27.12.2024.
//
//#include <SDL2/SDL.h>

/*#include "SDL.h"
#include <stdio.h>
#include <string.h>
//#include "SDL2_image.dll"

const int WIDTH = 500;
const int HEIGHT = 500;


int main(int argc, const char * argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stderr, "----------------Failed-------------- s% \n", SDL_GetError());
        exit(1);

    }

    SDL_Window *window = SDL_CreateWindow("Shooter",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    SDL_Quit();
    return 0;
};*/

#include "SDL.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int WIDTH = 500;
const int HEIGHT = 500;
const int HERO_WIDTH = 20;
const int HERO_HEIGHT = 50;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool Initialize(void);
void Shutdown(void);
void Update(float);



int main(int argc, const char * argv[]) {

    if (!Initialize()) {
        exit(1);
    }








    Uint32 lastTick = SDL_GetTicks();

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        Uint32 curTick = SDL_GetTicks();
        Uint32 diff = curTick - lastTick;
        float elapsed = diff / 1000.0f;
        Update(elapsed);
        lastTick = curTick;


    }

    Shutdown();
    return 0;
}

bool Initialize(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Shooter",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
            SDL_Quit();
            return false;
        }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
    return true;
}

void Shutdown(void) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}


void Update(float elapsed) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_Rect rect = {.x = WIDTH / 2 - HERO_WIDTH/2,
            .y = HEIGHT-HERO_HEIGHT,
            .w = HERO_WIDTH,
            .h = HERO_HEIGHT,};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
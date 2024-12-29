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

const int WIDTH = 500;
const int HEIGHT = 500;

int main(int argc, const char * argv[]) {
    // Ініціалізація SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Створення вікна
    SDL_Window *window = SDL_CreateWindow("Shooter",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Створення рендерера
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Головний цикл
    SDL_Event event;
    int running = 1;
    while (running) {
        // Обробка подій
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Очистка екрану
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Оновлення екрану
        SDL_RenderPresent(renderer);
    }

    // Очистка ресурсів
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

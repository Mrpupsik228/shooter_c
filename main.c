#include "SDL.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int WIDTH = 500;
const int HEIGHT = 500;
const int HERO_WIDTH = 20;
const int HERO_HEIGHT = 50;
const int HERO_SPEED = 120;
const int ENEMY_WIDTH = 40;
const int ENEMY_HEIGHT = 20;
const int ENEMY_SPEED = 80;


typedef struct Enemy {
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int width;
    int height;
} Enemy;


typedef struct Rocket {
    int score;
    float xPos;
} Rocket;




Enemy enemy;
Enemy enemy1;
Rocket rocket;

Rocket MakeRocket(void);
void UpdateRocket(float elapsed);
void RenderRocket(void);


Enemy MakeEnemy(int xPos, int yPos);
void UpdateEnemy(Enemy *enemy, float elapsed);
void RenderEnemy(Enemy *enemy);


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool Initialize(void);
void Update(float);
void Shutdown(void);


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

        rocket = MakeRocket();
        enemy = MakeEnemy(100,200);
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

    UpdateEnemy(&enemy, elapsed);
    RenderEnemy(&enemy);

    UpdateRocket(elapsed);
    RenderRocket();

    SDL_RenderPresent(renderer);
}

Enemy MakeEnemy(int xPos, int yPos){
    Enemy enemy= {
            .x = xPos,
            .y = yPos,
            .width = ENEMY_WIDTH,
            .height = ENEMY_HEIGHT,
            .xSpeed = ENEMY_SPEED,
            .ySpeed = ENEMY_SPEED/4
    };
    return enemy;
};

void RenderEnemy(Enemy *enemy) {
    int width = enemy->width;
    int height = enemy->height;
    SDL_Rect rect = {
        .x = enemy->x-width/2,
        .y = enemy->y,
        .w = width,
        .h = height,
    };
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &rect);
}


void UpdateEnemy(Enemy *enemy, float elapsed) {
    enemy->x += enemy->xSpeed * elapsed;
    enemy->y += enemy->ySpeed * elapsed;
    if (enemy->x > WIDTH-enemy->width) {
        enemy->xSpeed = -fabs(enemy->xSpeed);
    }
    if  (enemy->x < 0) {
        enemy->xSpeed = fabs(enemy->xSpeed);
    }
    if (enemy->y > HEIGHT) {
        enemy->y = -20;
    }
}

Rocket MakeRocket(void) {
    Rocket rocket = {
            .xPos = WIDTH/2,
    };
    return rocket;
};
void UpdateRocket(float elapsed){
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_D]) {
        if (rocket.xPos < (WIDTH)) {
            rocket.xPos+=HERO_SPEED * elapsed;
        };
    };
    if (keyboardState[SDL_SCANCODE_A]) {
        if (rocket.xPos > 0+HERO_WIDTH) {
            rocket.xPos-=HERO_SPEED * elapsed;
        };
    };
};
void RenderRocket(void) {
    SDL_SetRenderDrawColor(renderer, 0,125,125,255);
    SDL_Rect rocketRect = {
            .x = (int)(rocket.xPos) - HERO_WIDTH,
            .y = HEIGHT - HERO_HEIGHT,
            .w = HERO_WIDTH,
            .h = HERO_HEIGHT,
    };
    SDL_RenderFillRect(renderer, &rocketRect);
};
#include "SDL.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

//const int WIDTH = 500;
//const int HEIGHT = 500;
//const int HERO_WIDTH = 20;
//const int HERO_HEIGHT = 50;
//const int HERO_SPEED = 120;
//const int ENEMY_WIDTH = 40;
//const int ENEMY_HEIGHT = 20;
//const int ENEMY_SPEED = 80;
//const int MAX_ENEMIES = 5;
//const int MAX_BULLETS = 10;
//const int BULLET_WIDTH = 5;
//const int BULLET_HEIGHT = 10;
//const int BULLET_SPEED = 300;


#define WIDTH 500
#define HEIGHT 500
#define HERO_WIDTH 20
#define HERO_HEIGHT 50
#define HERO_SPEED 120
#define ENEMY_WIDTH 40
#define ENEMY_HEIGHT 20
#define ENEMY_SPEED 80
#define MAX_ENEMIES 5
#define MAX_BULLETS 10
#define BULLET_WIDTH 5
#define BULLET_HEIGHT 10
#define BULLET_SPEED 300


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
    bool isAlive;
} Rocket;

typedef struct Bullet {
    float x;
    float y;
    bool active;
} Bullet;




Enemy enemies[MAX_ENEMIES];
Bullet bullets[MAX_BULLETS];
Rocket rocket;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool Initialize(void);
void Update(float);
void Shutdown(void);
Rocket MakeRocket(void);
void UpdateRocket(float elapsed);
void RenderRocket(void);
Enemy MakeEnemy(int xPos, int yPos);
void UpdateEnemy(Enemy *enemy, float elapsed);
void RenderEnemy(Enemy *enemy);
void InitEnemies(void);
void UpdateBullets(float elapsed);
void RenderBullets(void);
void ShootBullet(void);
bool CheckCollision(SDL_Rect a, SDL_Rect b);
void ResetEnemy(Enemy* enemy);





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
        InitEnemies();
        for (int i = 0; i < MAX_BULLETS; i++) {
            bullets[i].active = false;
        }

    return true;
}




void Update(float elapsed) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (rocket.isAlive) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            UpdateEnemy(&enemies[i], elapsed);
            RenderEnemy(&enemies[i]);
            SDL_Rect enemyRect = {
                    .x = enemies[i].x - enemies[i].width / 2,
                    .y = enemies[i].y,
                    .w = enemies[i].width,
                    .h = enemies[i].height
            };
            SDL_Rect playerRect = {
                    .x = (int) (rocket.xPos) - HERO_WIDTH,
                    .y = HEIGHT - HERO_HEIGHT,
                    .w = HERO_WIDTH,
                    .h = HERO_HEIGHT
            };

            if (CheckCollision(enemyRect, playerRect)) {
                rocket.isAlive = false;
            }
        }

        UpdateBullets(elapsed);
        RenderBullets();

        UpdateRocket(elapsed);
        RenderRocket();
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }

    SDL_RenderPresent(renderer);
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

Rocket MakeRocket(void) {
    Rocket rocket = {
            .xPos = WIDTH/2,
            .score = 0,
            .isAlive = true
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
    if (keyboardState[SDL_SCANCODE_SPACE]) {
        ShootBullet();
    }
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
        rocket.score--;
        ResetEnemy(enemy);
    }
}

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

void InitEnemies(void) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i] = MakeEnemy(100 + i * 80, -i * 50);
    }
}
/*******************************************************************************************************/

void UpdateBullets(float elapsed) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= BULLET_SPEED * elapsed;
            if (bullets[i].y < 0) {
                bullets[i].active = false;
                continue;
            }
            SDL_Rect bulletRect = {
                    .x = bullets[i].x,
                    .y = bullets[i].y,
                    .w = BULLET_WIDTH,
                    .h = BULLET_HEIGHT
            };
            for (int j = 0; j < MAX_ENEMIES; j++) {
                SDL_Rect enemyRect = {
                        .x = enemies[j].x - enemies[j].width/2,
                        .y = enemies[j].y,
                        .w = enemies[j].width,
                        .h = enemies[j].height
                };
                if (CheckCollision(bulletRect, enemyRect)) {
                    bullets[i].active = false;
                    ResetEnemy(&enemies[j]);
                    rocket.score++;
                    break;
                }
            }
        }
    }
}

void RenderBullets(void) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            SDL_Rect bulletRect = {
                    .x = bullets[i].x,
                    .y = bullets[i].y,
                    .w = BULLET_WIDTH,
                    .h = BULLET_HEIGHT
            };
            SDL_RenderFillRect(renderer, &bulletRect);
        }
    }
}
void ShootBullet(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].active = true;
            bullets[i].x = rocket.xPos;
            bullets[i].y = HEIGHT - HERO_HEIGHT;
            break;
        }
    }
}
bool CheckCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

void ResetEnemy(Enemy* enemy) {
    enemy->y = -20;
    enemy->x = rand() % (WIDTH - ENEMY_WIDTH) + ENEMY_WIDTH/2;
}



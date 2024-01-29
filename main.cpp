#include <SDL.h>
#include <iostream>

constexpr int FOV_WIDTH = 1280;
constexpr int FOV_HEIGHT = 720;
constexpr int TILE_SIZE = 40;
constexpr int GRID_WIDTH = 1280 / TILE_SIZE;
constexpr int GRID_HEIGHT = 720 / TILE_SIZE;

struct Character {
    int x; // X position in tiles
    int y; // Y position in tiles
};

void renderTiles(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 10);

    for (int row = 0; row < GRID_HEIGHT; ++row) {
        for (int col = 0; col < GRID_WIDTH; ++col) {
            SDL_Rect tileRect = {col * TILE_SIZE + 1, row * TILE_SIZE + 1, TILE_SIZE - 2, TILE_SIZE - 2};
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

void renderCharacter(SDL_Renderer *renderer, const Character &character) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for the character
    SDL_Rect charRect = {character.x * TILE_SIZE, character.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_RenderFillRect(renderer, &charRect);
}

void moveCharacter(Character &character, SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_w: character.y = std::max(0, character.y - 1);
                break; // Move up
            case SDLK_s: character.y = std::min(GRID_HEIGHT - 1, character.y + 1);
                break; // Move down
            case SDLK_a: character.x = std::max(0, character.x - 1);
                break; // Move left
            case SDLK_d: character.x = std::min(GRID_WIDTH - 1, character.x + 1);
                break; // Move right
        }
    }
}

SDL_Window *initWindow(int &width, int &height) {
    SDL_DisplayMode current;
    if (SDL_GetCurrentDisplayMode(0, &current) != 0) {
        std::cerr << "SDL could not get display mode! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    width = current.w;
    height = current.h;
    return SDL_CreateWindow("LOD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}

SDL_Renderer *createRenderer(SDL_Window *window) {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void runGameLoop(SDL_Renderer *renderer) {
    bool quit = false;
    SDL_Event e;
    Character player = {GRID_WIDTH / 2, GRID_HEIGHT / 2}; // Center of the grid

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                moveCharacter(player, e); // Handle character movement
            }
        }

        constexpr int fovX = 0;
        constexpr int fovY = 0;


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderTiles(renderer);

        renderCharacter(renderer, player); // Render the character

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect fovRect = {fovX, fovY, FOV_WIDTH, FOV_HEIGHT};
        SDL_RenderDrawRect(renderer, &fovRect);

        SDL_RenderPresent(renderer);
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int windowWidth, windowHeight;
    SDL_Window *window = initWindow(windowWidth, windowHeight);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = createRenderer(window);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    runGameLoop(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

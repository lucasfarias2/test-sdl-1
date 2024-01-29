#include <SDL.h>
#include <iostream>

const int TILE_SIZE = 32;
const int GRID_SIZE = 32;
const int WINDOW_WIDTH = TILE_SIZE * GRID_SIZE;
const int WINDOW_HEIGHT = TILE_SIZE * GRID_SIZE;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("LOD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red

        // Draw grid
        for (int i = 0; i <= GRID_SIZE; ++i) {
            // Vertical lines
            SDL_RenderDrawLine(renderer, i * TILE_SIZE, 0, i * TILE_SIZE, WINDOW_HEIGHT);
            // Horizontal lines
            SDL_RenderDrawLine(renderer, 0, i * TILE_SIZE, WINDOW_WIDTH, i * TILE_SIZE);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Delay to limit frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

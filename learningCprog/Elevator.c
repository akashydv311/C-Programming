#include <SDL3.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
#define FLOOR_HEIGHT 100
#define NUM_FLOORS 5
#define LIFT_WIDTH 80
#define LIFT_HEIGHT 80

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Lift Simulation",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int currentFloor = 0;
    bool running = true;
    SDL_Event event;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP && currentFloor < NUM_FLOORS - 1)
                    currentFloor++;
                else if (event.key.keysym.sym == SDLK_DOWN && currentFloor > 0)
                    currentFloor--;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white background
        SDL_RenderClear(renderer);

        // Draw lift shaft
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_Rect shaft = {150, 0, LIFT_WIDTH, SCREEN_HEIGHT};
        SDL_RenderDrawRect(renderer, &shaft);

        // Draw floors
        for (int i = 0; i < NUM_FLOORS; i++) {
            int y = i * FLOOR_HEIGHT;
            SDL_RenderDrawLine(renderer, 150, y, 150 + LIFT_WIDTH, y);
        }

        // Draw lift
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255); // blue
        int liftY = SCREEN_HEIGHT - (currentFloor + 1) * FLOOR_HEIGHT + 10;
        SDL_Rect lift = {150 + 5, liftY, LIFT_WIDTH - 10, LIFT_HEIGHT};
        SDL_RenderFillRect(renderer, &lift);

        SDL_RenderPresent(renderer);

        SDL_Delay(30); // Small delay to reduce CPU usage
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

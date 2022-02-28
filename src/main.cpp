#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

bool main_loop(SDL_Renderer* renderer)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {

#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif

        return false;
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return true;
}

void run_main_loop(void* renderer) {
    main_loop((SDL_Renderer*)renderer);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Getting Started",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(run_main_loop, (void*)renderer, 0, true);
#else
    while(main_loop(renderer)) {
        SDL_Delay(0);
    };
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

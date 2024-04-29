#include"header.h"

int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    sdl_r.window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_MAXIMIZED
    );
    if (!sdl_r.window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    sdl_r.renderer = SDL_CreateRenderer(sdl_r.window, -1, 0);
    if (!sdl_r.renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }

    SDL_SetRenderDrawBlendMode(sdl_r.renderer, SDL_BLENDMODE_BLEND);

    sdl_r.color_buffer_texture = SDL_CreateTexture(sdl_r.renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    sdl_r.color_buffers = malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
    return true;
}


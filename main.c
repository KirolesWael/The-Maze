#include "header.h"

int last_frame_time = 0;



void setup(void) 
{
    player.x = 30;
    player.y = 30;
    player.angle = 0;
    player.fov = PI / 3;
    player.speed = 5;
    player.ang_speed = 0.08726646;

    sdl_r.window = NULL;
    sdl_r.renderer = NULL;
    sdl_r.color_buffers = NULL;
    sdl_r.color_buffer_texture = NULL;
}


void update(void) 
{
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

    last_frame_time = SDL_GetTicks();

    draw_3d_rays();
}


void render(void) 
{
    SDL_SetRenderDrawColor(sdl_r.renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_r.renderer);

    // Draw a rectangle for the ball object
    SDL_Rect player_rect = 
    {
        (int)player.x,
        (int)player.y,
        20,
        20,
    };

    
    SDL_SetRenderDrawColor(sdl_r.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(sdl_r.renderer, &player_rect);

    SDL_RenderPresent(sdl_r.renderer);
}


void destroy_window(void) 
{
    SDL_DestroyRenderer(sdl_r.renderer);
    SDL_DestroyWindow(sdl_r.window);
    SDL_Quit();
}


int main(int argc, char* args[]) 
{
    setup();
    game_is_running = initialize_window();

    while (game_is_running) 
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
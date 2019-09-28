#include <stdio.h>
#include <SDL2/SDL.h>

typedef enum {
    false = 0,
    true = 1
} bool;

void cleanup(char *types, ...);

int main(int argc, char* argv[])
{
    int posx, posy, width, height, duration;
    posx = posy = 64;
    width = height = 400;

    Uint8 red, green, blue, alpha;
    red = 255;
    green = 20;
    blue = 20;
    alpha = 25;

    SDL_Window *window;
    SDL_Renderer *renderer;
    const Uint8 *kbstate;
    bool quit = false;
    SDL_Event e;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Hello World", posx, posy, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);        
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    
    cleanup("rw", renderer, window);
    SDL_Quit();

    return 0;
}

void cleanup(char *types, ...)
{
    va_list objs;
    va_start(objs, types);

    while (*types != '\0')
    {
        switch (*types)
        {
        case 'T':
        case 't':
            SDL_DestroyTexture(va_arg(objs, SDL_Texture *));
            break;
        case 'R':
        case 'r':
            SDL_DestroyRenderer(va_arg(objs, SDL_Renderer *));
            break;
        case 'W':
        case 'w':
            SDL_DestroyWindow(va_arg(objs, SDL_Window *));
            break;
        default:
            printf("\nCLEANUP: INVALID TYPE\n");
            break;
        }
        types++;
    }
    va_end(objs);
}
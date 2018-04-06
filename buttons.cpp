#include "buttons.h"

using namespace myNamespace;

void button::init() {

    r.w = mainWindowsWidth * 0.2;
    r.h = mainWindowsHeight * 0.15;
    r.x = mainWindowsWidth * 0.5 - r.w * 0.5;
    r.y = mainWindowsHeight * 0.85 - r.h * 0.5;
    link = buttonStart_link;

}

void button::createButton (SDL_Window *&window) {

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    background = SDL_LoadBMP( link.c_str() );
    SDL_SetColorKey( background, 1, SDL_MapRGB( background->format, 255, 0, 255 ) );

    if (background == NULL) {
        SDL_ShowSimpleMessageBox(0, "Background init error!", SDL_GetError(), window);
    }

    texture = SDL_CreateTextureFromSurface(renderer,background);

    if(texture == NULL) {
        SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
    }

    SDL_RenderCopy (renderer, texture, NULL, &(r) );

    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);

    SDL_DestroyRenderer(renderer);
}

void button :: freeButton () {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

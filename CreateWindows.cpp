#include "CreateWindows.h"
using namespace myNamespace;
using namespace std;

void UI:: init() {
    window = NULL;
}

void UI::initWindow (SDL_Window *&window, const string title, const int &width, const int &height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Cannot initialize SDL! Error: %s\n", SDL_GetError() );
        return;
    }

    window = SDL_CreateWindow("Renewed Hang Man",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                width, height,
                                SDL_WINDOW_SHOWN
                             );

    if(window == NULL) {
        printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }

    return;
}

void UI::initSurface (SDL_Window *&window, const int &width, const int &height) {

    SDL_Surface *screenSurface;
    screenSurface = SDL_GetWindowSurface( window );
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
    SDL_SetColorKey( screenSurface, 1, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
    SDL_UpdateWindowSurface( window );
}

void UI::initBackground (SDL_Window * &window, const string &background_link) {

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        SDL_ShowSimpleMessageBox(0, "Renderer init error!", SDL_GetError(), window);
    }

    SDL_Surface *background = SDL_LoadBMP( (background_link).c_str());
    if (background == NULL) {
        SDL_ShowSimpleMessageBox(0, "Background init error!", SDL_GetError(), window);
    }

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer,background);
    if(texture == NULL) {
        SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
    }

    SDL_RenderCopy (renderer, texture, NULL, NULL);

    SDL_DestroyTexture(texture);


    SDL_RenderPresent (renderer);
    SDL_DestroyRenderer(renderer);

    return;
}

void UI::destroyWindow (SDL_Window * &window) {
    SDL_DestroyWindow (window);
}

void UI::quitSDL () {
    destroyWindow ( window );
    SDL_Quit ();
}

void UI::_make_main_windows (const string title, const int &width, const int &height) {

    init();

    initWindow ( window, title, width, height );

    initSurface ( window, width, height );

    //initBackground (window, background_link);

    return;
}














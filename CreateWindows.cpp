#include "CreateWindows.h"
using namespace myNamespace;
using namespace std;

void UI::quitSDL () {
    destroyWindow ();
    SDL_Quit ();
}

void UI::_make_main_windows (const string title, const int &width, const int &height) {

    init();

    initWindow (title, width, height );
    return;
}

void UI::initBackground (const string &background_link) {

    SDL_Surface *background = SDL_LoadBMP( (background_link).c_str());

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer,background);

    SDL_RenderCopy (renderer, texture, NULL, NULL);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(texture);

    return;
}






// public --------------------------------------------------------------------------------------
// private -------------------------------------------------------------------------------------







void UI:: init() {
    window = NULL;
}

void UI::initWindow (const string title, const int &width, const int &height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Cannot initialize SDL! Error: %s\n", SDL_GetError() );
        return;
    }

    window = SDL_CreateWindow("IQ",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                width, height,
                                SDL_WINDOW_SHOWN
                             );

    return;
}

void UI::destroyWindow () {
    SDL_DestroyWindow (window);
}
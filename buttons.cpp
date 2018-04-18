#include "buttons.h"

using namespace myNamespace;

void StartButton::init() {

    r.w = mainWindowsWidth * 0.2;
    r.h = mainWindowsHeight * 0.15;
    r.x = mainWindowsWidth * 0.5 - r.w * 0.5;
    r.y = mainWindowsHeight * 0.85 - r.h * 0.5;
    link = buttonStart_link;

}

void RotateButton :: init(const string &type) {

    r.w = r.h = mainWindowsWidth * 0.1;

    r.y = mainWindowsHeight * 0.85 - r.h * 0.5;
    if (type == "left") {
        r.x = mainWindowsWidth * 0.35 - r.w * 0.5;
        link = RotateLeft_link;
    }
    else {
        r.x = mainWindowsWidth * 0.65 - r.w * 0.5;
        link = RotateRight_link;
    }
}

void BackButton :: init () {
    r.w = r.h = mainWindowsWidth * 0.09;
    r.x = r.y = 0;
    link = back_link;
}

void button::createButton (SDL_Renderer *&renderer) {

    background = SDL_LoadBMP( link.c_str() );
    SDL_SetColorKey( background, 1, SDL_MapRGB( background->format, 255, 0, 255 ) );

    texture = SDL_CreateTextureFromSurface(renderer,background);

    SDL_RenderCopy (renderer, texture, NULL, &(r) );
    SDL_FreeSurface(background);
    SDL_DestroyTexture(texture);
}

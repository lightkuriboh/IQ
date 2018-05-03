#include "buttons.h"

using namespace myNamespace;

void StartButton::init() {

    r.w = MainWindowsWidth * 0.2;
    r.h = MainWindowsHeight * 0.15;
    r.x = MainWindowsWidth * 0.5 - r.w * 0.5;
    r.y = MainWindowsHeight * 0.85 - r.h * 0.5;
    link = buttonStart_link;

}

void RotateButton :: init(const string &type) {

    r.w = r.h = MainWindowsWidth * 0.1;

    r.y = MainWindowsHeight * 0.85 - r.h * 0.5;
    if (type == "left") {
        r.x = MainWindowsWidth * 0.35 - r.w * 0.5;
        link = RotateLeft_link;
    }
    else {
        r.x = MainWindowsWidth * 0.65 - r.w * 0.5;
        link = RotateRight_link;
    }
}

void BackButton :: init () {
    r.w = r.h = MainWindowsWidth * 0.09;
    r.x = r.y = 0;
    link = back_link;
}

void RestartButton :: init () {
    r.w = r.h = MainWindowsWidth * 0.09;
    r.x = MainWindowsWidth - r.w;
    r.y = r.h;
    link = restart_link;
}

void UndoButton :: init () {
    r.w = r.h = MainWindowsWidth * 0.09;
    r.x = MainWindowsWidth - r.w;
    r.y = 0;
    link = undo_link;
}

void button::createButton (SDL_Renderer *&renderer, SDL_Surface *surface) {

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_RenderCopy (renderer, texture, NULL, &(r) );

    SDL_DestroyTexture(texture);
}

#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "SDL2/SDL.h"
#include "CreateWindows.h"
#include "EventHandler.h"
#include "config.h"
#include "gamePresenter.h"
#include "buttons.h"

namespace myNamespace {
    void processLevel (SDL_Window *&window, int &level, bool &stopGame, bool &levelUp);
    void StartOneThread (const int &height, const int &width);
}

#endif // GAMEENGINE_H_INCLUDED

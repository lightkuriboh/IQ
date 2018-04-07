#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "SDL2/SDL.h"
#include "CreateWindows.h"
#include "EventHandler.h"
#include "config.h"
#include "gamePresenter.h"
#include "buttons.h"

using namespace myNamespace;

namespace myNamespace {
    void processLevel (SDL_Window *&window, int &level, bool &stopGame, bool &levelUp, bool &backMenu);
    void StartOneThread (const int &height, const int &width);
    void initGameMenu (UI &thisUI);
}

#endif // GAMEENGINE_H_INCLUDED

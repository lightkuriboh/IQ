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
    void processLevel (int &level, bool &stopGame, bool &levelUp, bool &backMenu);
    void StartOneThread (const int &height, const int &width);
    void initGameMenu (UI &thisUI);
    void initOneImage (SDL_Surface *&surface, const string &link);
    void initGameData ();
}

#endif // GAMEENGINE_H_INCLUDED

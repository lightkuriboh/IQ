#ifndef EVENTHANDLER_INCLUDED
#define EVENTHANDLER_INCLUDED
#include <iostream>
#include <SDL2/SDL.h>
#include "CreateWindows.h"

using namespace std;

namespace myNamespace {
    bool inRect (const int &x, const int &y, const SDL_Rect &r);
    pair <int, int> mouseClickLeft (const SDL_Event &event);
    pair <int, int> mouseClickRight (const SDL_Event &event);
    bool clickStart (const SDL_Event & event);
    bool quit (const SDL_Event & event) ;
}

#endif // EVENTHANDLER_INCLUDED

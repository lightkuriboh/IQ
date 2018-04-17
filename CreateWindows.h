#ifndef CREATEWINDOWS_H_INCLUDED
#define CREATEWINDOWS_H_INCLUDED
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "config.h"
using namespace std;

namespace myNamespace {

    class UI {
        private:
            void init ();
            void initWindow (const string title, const int &width, const int &height);
            void destroyWindow ();

        public:
            SDL_Renderer *renderer;
            void quitSDL () ;
            void _make_main_windows (const string title, const int &width, const int &height);
            void initBackground (const string &background_link);

    };
}

#endif // CREATEWINDOWS_H_INCLUDED

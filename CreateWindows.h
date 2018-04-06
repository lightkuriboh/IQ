#ifndef CREATEWINDOWS_H_INCLUDED
#define CREATEWINDOWS_H_INCLUDED
#include <SDL2/SDL.h>
#include <string>
#include "config.h"
using namespace std;

namespace myNamespace {

    class UI {

        public:
            SDL_Window * window;

        private:
            void init ();
            void initWindow (SDL_Window *&window, const string title, const int &width, const int &height);
            void initSurface (SDL_Window *&window, const int &width, const int &height );
            void destroyWindow (SDL_Window *&window);

        public:
            void quitSDL () ;
            void _make_main_windows (const string title, const int &width, const int &height);
            void _make_surface (SDL_Window *&window);
            void initBackground (SDL_Window * &window, const string &background_link);
    };
}

#endif // CREATEWINDOWS_H_INCLUDED

#ifndef CREATEWINDOWS_H_INCLUDED
#define CREATEWINDOWS_H_INCLUDED
#include <SDL2/SDL.h>
#include <string>
#include "config.h"
using namespace std;

namespace myNamespace {

    class buttonStart {
        public:
            SDL_Rect r;
            string link;
            void init();
    };

    class UI {

        public:
            SDL_Window * window;

        private:
            void init ();
            void initWindow (SDL_Window *&window, const string title, const int &width, const int &height);
            void initSurface (SDL_Window *&window, const int &width, const int &height );
            void initBackground (SDL_Window * &window, const string &background_link);
            void createButton (SDL_Window *&window, const buttonStart &button);
            void destroyWindow (SDL_Window * &window);

        public:
            void quitSDL () ;
            void _make_main_windows (const string title, const int &width, const int &height);
    };
}

#endif // CREATEWINDOWS_H_INCLUDED

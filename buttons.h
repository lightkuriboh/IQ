#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED
#include "config.h"
#include <SDL2/SDL.h>

namespace myNamespace {

    class button {
        private:
            SDL_Texture *texture;
            SDL_Renderer *renderer;
            SDL_Surface *background;
        public:
            SDL_Rect r;
            string link;
            void createButton (SDL_Window *&window);
    };

    class StartButton: public button {
        public:
            void init();
    };

    class RotateButton: public button {
        public:
            void init(const string &type);
    };

}

#endif // BUTTONS_H_INCLUDED

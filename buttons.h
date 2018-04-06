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
            string link;
            SDL_Rect r;
            void init();
            void createButton (SDL_Window *&window);
            void freeButton ();
    };

}

#endif // BUTTONS_H_INCLUDED

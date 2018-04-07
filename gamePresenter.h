#ifndef GAMEPRESENTER_H_INCLUDED
#define GAMEPRESENTER_H_INCLUDED
using namespace std;

#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include "config.h"

namespace myNamespace {
    class gameInfo {
        public:
            vector <pair <int, int> > block;
            vector <pair <int, int> > ball;
            vector <pair <int, int> > destination;

            gameInfo (const int level, SDL_Window *&window);
            void RotateLeftAll  ();
            void RotateRightAll ();
            void updateAllState (SDL_Window *&window);
            bool completeLevel ();

        private:
            SDL_Renderer *renderer;
            SDL_Texture *texture;
            SDL_Rect positionFrame;

            void presentFrame (SDL_Window *&window);
            void presentGameState (SDL_Window *&window);
            void RotateLeft (vector <pair <int, int> > &v);
            void RotateRight (vector <pair <int, int> > &v);
            void presentImage (SDL_Window *&window, const SDL_Rect r, const string &image_link);
    };
}

#endif // GAMEPRESENTER_H_INCLUDED

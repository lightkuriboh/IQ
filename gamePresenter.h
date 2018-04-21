#ifndef GAMEPRESENTER_H_INCLUDED
#define GAMEPRESENTER_H_INCLUDED
using namespace std;

#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <set>
#include <algorithm>
#include <SDL2/SDL.h>
#include "config.h"
#include "buttons.h"

namespace myNamespace {

    class gameInfo {
        public:
            SDL_Renderer *renderer;
            vector <pair <int, int> > block;
            vector <pair <int, int> > ball;
            vector <pair <int, int> > destination;

            gameInfo (const int level);
            void RotateLeftAll  (const int &level);
            void RotateRightAll (const int &level);
            void update(const double &angle, const int &level);
            void displayComplete ();
            bool completeLevel ();

        private:
            SDL_Point center;
            SDL_Texture *texture;
            SDL_Rect positionFrame;
            bool inrange(const int &x, const int &y);
            void presentAllOtherThings (const int &level);
            void updateAllState (const double &angle);
            void presentIFrame (const double &angle);
            void presentFrameBackground (const bool &levelComplete, const double &angle);
            void presentGameState (const double &angle);
            void RotateLeft (vector <pair <int, int> > &v);
            void RotateRight (vector <pair <int, int> > &v);
            void presentImage (const SDL_Rect r, const string &image_link, const double &angle);
            void presentLevelInfo (const int &level);
    };
}

#endif // GAMEPRESENTER_H_INCLUDED

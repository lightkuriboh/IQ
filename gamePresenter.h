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
#include <deque>

namespace myNamespace {

    class gamePresenter {
        public:
            vector <pair <int, int> > balls;
            vector <pair <int, int> > blocks;
            vector <pair <int, int> > destinations;

            gamePresenter (const int level);
            void RotateLeftAll  (const int &level);
            void RotateRightAll (const int &level);
            void update(const double &angle, const int &level);
            bool completeLevel ();
            void displayComplete ();
            void undo ();
            void restart ();
            void freeResource ();

        private:
            SDL_Point center;
            SDL_Rect positionFrame;
            SDL_Texture *texture;
            SDL_Renderer *renderer;
            struct gameState {
                vector <pair <int, int> > balls, blocks, destinations;
            };
            deque <gameState> undoQueue;
            struct gameState originalGameState;


            bool cmp (const pair <int, int> &a, const pair <int, int> &b);
            bool inrange(const int &x, const int &y);

            void compressData (gameState &gameState);
            void extractData  (gameState &gameState);
            void pushUndo ();

            void generateLevel (const int &level);
            void presentAllOtherThings (const int &level);
            void updateAllState (const double &angle, const bool &presentState);
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


#include "gamePresenter.h"

using namespace myNamespace;
using namespace std;

gameInfo :: gameInfo (const int level) {
    stringstream ss;
    ss << level;
    string levelNow = "";
    ss >> levelNow;

    block.clear();
    ball.clear();
    destination.clear();
    //--------------------------------------------------------------------

    ifstream fi;
    int x, y;
    fi.open(("bin/level" + levelNow + "/block.txt").c_str());
    while (fi >> x >> y) { block.push_back(make_pair(x, y)); }
    fi.close ();
    //--------------------------------------------------------------------
    fi.open(("bin/level" + levelNow + "/ball.txt").c_str());
    while (fi >> x >> y) { ball.push_back(make_pair(x, y)); }
    fi.close ();
    //--------------------------------------------------------------------
    fi.open(("bin/level" + levelNow + "/destination.txt").c_str());
    while (fi >> x >> y) { destination.push_back(make_pair(x, y)); }
    fi.close ();
    //--------------------------------------------------------------------
}



void updateBallPotision (vector <pair <int, int> > &v) {

}

void gameInfo :: RotateLeft (vector <pair <int, int> > &v) {

}

void gameInfo :: RotateRight (vector <pair <int, int> > &v) {

}

void gameInfo :: presentImage (SDL_Window *& window, const SDL_Rect r, const string &image_link) {

    SDL_Renderer * renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface *background = SDL_LoadBMP(image_link.c_str());

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, background);

    SDL_RenderCopy (renderer, texture, NULL, &r);

    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_DestroyRenderer(renderer);
}

void gameInfo :: presentFrame (SDL_Window *&window) {

    positionFrame.w = mainWindowsWidth * 0.4;
    positionFrame.h = positionFrame.w;
    positionFrame.x = mainWindowsWidth * 0.5 - positionFrame.w * 0.5;
    positionFrame.y = mainWindowsHeight * 0.4 - positionFrame.h * 0.5;

    presentImage (window, positionFrame, "img/BG_Frame.bmp");
}

void gameInfo :: presentGameState (SDL_Window *&window) {
    double eachSize = positionFrame.h / 10.0;
    for (auto pos: block) {
        SDL_Rect blocks;
        blocks.w = blocks.h = eachSize;
        blocks.x = positionFrame.x + (pos.first - 1) * eachSize;
        blocks.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(window, blocks, "img/block.bmp");
    }
    for (auto pos: ball) {
        SDL_Rect balls;
        balls.w = balls.h = eachSize;
        balls.x = positionFrame.x + (pos.first - 1) * eachSize;
        balls.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(window, balls, "img/ball.bmp");
    }
    for (auto pos: destination) {
        SDL_Rect destinations;
        destinations.w = destinations.h = eachSize;
        destinations.x = positionFrame.x + (pos.first - 1) * eachSize;
        destinations.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(window, destinations, "img/destination.bmp");
    }
}


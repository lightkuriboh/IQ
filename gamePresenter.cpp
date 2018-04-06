
#include "gamePresenter.h"

using namespace myNamespace;
using namespace std;

gameInfo :: gameInfo (const int level, SDL_Window *&window) {
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
    renderer = SDL_CreateRenderer (window, -1, 0);
}

void gameInfo :: updateAllState (SDL_Window *&window) {
    bool state[11][11];
    memset (state, false, sizeof(state));
    for (auto info: block)
        state [info.first][info.second] = true;

    int cnt;
    do {
        cnt = 0;
        for (int i = 0; i < int(ball.size()); i++) {
            if (ball[i].second + 1 < 11 && state[ball[i].first][ball[i].second + 1] == false) {
                ball[i].second++;
                cnt++;
            }
        }
        presentFrame(window);
        presentGameState(window);
    } while (cnt > 0);
}

void gameInfo :: RotateRight (vector <pair <int, int> > &v) {
    int w = 10,
        h = 10;
    for (int i = 0; i < int(v.size()); i++) {
        int tmp = v[i].second;
        v[i].second = v[i].first;
        v[i].first = h - tmp + 1;
    }
}

void gameInfo :: RotateLeft (vector <pair <int, int> > &v) {
    int w = 10,
        h = 10;
    for (int i = 0; i < int(v.size()); i++) {
        int tmp = v[i].first;
        v[i].first = v[i].second;
        v[i].second = w - tmp + 1;
    }
}

void gameInfo :: RotateLeftAll () {
    RotateLeft (ball);
    RotateLeft (destination);
    RotateLeft (block);
}

void gameInfo :: RotateRightAll () {
    RotateRight (ball);
    RotateRight (destination);
    RotateRight (block);
}

void gameInfo :: presentImage (SDL_Window *& window, const SDL_Rect r, const string &image_link) {

    SDL_Surface *background = SDL_LoadBMP(image_link.c_str());

    texture = SDL_CreateTextureFromSurface(renderer, background);

    SDL_RenderCopy (renderer, texture, NULL, &r);
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
    SDL_RenderPresent(renderer);
}


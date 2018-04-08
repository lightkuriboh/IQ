
#include "gamePresenter.h"

using namespace myNamespace;
using namespace std;

bool cmp (const pair <int, int> &a, const pair <int, int> &b) {
    return a.second > b.second;
}

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
    fi.open(("levels/level" + levelNow + "/block.txt").c_str());
    while (fi >> x >> y) { block.push_back(make_pair(x, y)); }
    fi.close ();
    //--------------------------------------------------------------------
    fi.open(("levels/level" + levelNow + "/ball.txt").c_str());
    while (fi >> x >> y) { ball.push_back(make_pair(x, y)); }
    fi.close ();
    //--------------------------------------------------------------------
    fi.open(("levels/level" + levelNow + "/destination.txt").c_str());
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
    //------------------------------------------------------------------
    sort (ball.begin(), ball.end(), cmp); // sort balls to easy manage
    set <pair <int, int> > isBall;
    isBall.clear();
    for (auto balls: ball) {
        isBall.insert (balls);
    }
    //------------------------------------------------------------------
    //SDL_RenderClear (renderer);
    //------------------------------------------------------------------
    int cnt;
    do {

        presentFrameBackground(window, false);
        presentGameState(window);
        presentIFrame (window);
        SDL_RenderPresent(renderer);

        cnt = 0;
        for (int i = 0; i < int(ball.size()); i++) {
            if (isBall.find (make_pair(ball[i].first, ball[i].second + 1)) == isBall.end()) { // is not another ball

                if (ball[i].second + 1 < 11 && state[ball[i].first][ball[i].second + 1] == false) {

                    isBall.erase(ball[i]);
                    isBall.insert (make_pair(ball[i].first, ball[i].second + 1));
                    ball[i].second++;
                    cnt++;
                }
            }
        }

        SDL_Delay (200);

    } while (cnt > 0);
}

void gameInfo :: RotateRight (vector <pair <int, int> > &v) {
    int h = 10;
    for (int i = 0; i < int(v.size()); i++) {
        int tmp = v[i].second;
        v[i].second = v[i].first;
        v[i].first = h - tmp + 1;
    }
}

void gameInfo :: RotateLeft (vector <pair <int, int> > &v) {
    int w = 10;
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

void gameInfo::presentLevelInfo (SDL_Window *&window, const int &level) {
    stringstream ss;
    ss << level;
    string levelNow = "";
    ss >> levelNow;
    levelNow = "img/level" + levelNow + ".bmp";

    SDL_Rect r;

    r.w = r.h = mainWindowsWidth * 0.1;
    r.y = mainWindowsHeight * 0.85 - r.h * 0.5;
    r.x = mainWindowsWidth * 0.5 - r.w * 0.5;

    presentImage (window, r, levelNow);
}

void gameInfo :: presentImage (SDL_Window *& window, const SDL_Rect r, const string &image_link) {

    SDL_Surface *background = SDL_LoadBMP(image_link.c_str());

    if (background == NULL) {
        SDL_ShowSimpleMessageBox(0, "Background init error!", SDL_GetError(), window);
    }

    texture = SDL_CreateTextureFromSurface(renderer, background);

    if(texture == NULL) {
        SDL_ShowSimpleMessageBox(0, "Texture init error", SDL_GetError(), window);
    }

    SDL_RenderCopy (renderer, texture, NULL, &r);

    SDL_FreeSurface (background);
    SDL_DestroyTexture (texture);

}

void gameInfo :: presentIFrame (SDL_Window *&window) {
    SDL_Rect iframe;
    iframe.w = mainWindowsWidth * 0.55;
    iframe.h = iframe.w * 0.89;
    iframe.x = mainWindowsWidth * 0.5 - iframe.w * 0.5;
    iframe.y = mainWindowsHeight * 0.4 - iframe.h * 0.5;

    presentImage (window, iframe, frame_link);

}

void gameInfo :: presentFrameBackground (SDL_Window *&window, const bool &levelComplete) {

    positionFrame.w = mainWindowsWidth * 0.36;
    positionFrame.h = positionFrame.w;
    positionFrame.x = mainWindowsWidth * 0.5 - positionFrame.w * 0.5;
    positionFrame.y = mainWindowsHeight * 0.4 - positionFrame.h * 0.5;

    if (levelComplete == false){
        presentImage (window, positionFrame, bgFrame_link);
    }
    else {
        presentImage (window, positionFrame, completeLevel_link);
    }
}

void gameInfo :: presentGameState (SDL_Window *&window) {

    double eachSize = positionFrame.h / 10.0;
    for (auto pos: block) {
        SDL_Rect blocks;
        blocks.w = blocks.h = eachSize;
        blocks.x = positionFrame.x + (pos.first - 1) * eachSize;
        blocks.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(window, blocks, block_link);
    }

    for (auto pos: destination) {
        SDL_Rect destinations;
        destinations.w = destinations.h = eachSize;
        destinations.x = positionFrame.x + (pos.first - 1) * eachSize;
        destinations.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(window, destinations, destination_link);
    }

    for (auto pos: ball) {
        SDL_Rect balls;
        balls.w = balls.h = eachSize;
        balls.x = positionFrame.x + (pos.first - 1) * eachSize;
        balls.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(window, balls, ball_link);
    }
}

bool gameInfo :: completeLevel () {
    for (auto destinations: destination) {
        bool found = false;
        for (auto balls: ball)
            if (destinations.first == balls.first && destinations.second == balls.second)
                found = true;
        if (!found) return false;
    }
    return true;
}

void gameInfo :: displayComplete (SDL_Window *&window) {
    presentFrameBackground (window, true);
    presentIFrame (window);
    SDL_RenderPresent (renderer);
}

void gameInfo :: freeResource () {
    SDL_DestroyRenderer (renderer);
}

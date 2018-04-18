
#include "gamePresenter.h"

using namespace myNamespace;
using namespace std;

bool cmp (const pair <int, int> &a, const pair <int, int> &b) {
    return a.second > b.second;
}

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
    positionFrame.w = mainWindowsWidth * 0.36;
    positionFrame.h = positionFrame.w;
    positionFrame.x = mainWindowsWidth * 0.5 - positionFrame.w * 0.5;
    positionFrame.y = mainWindowsHeight * 0.4 - positionFrame.h * 0.5;
    //--------------------------------------------------------------------
    center.x = positionFrame.x + positionFrame.w * 0.5;
    center.y = positionFrame.y + positionFrame.h * 0.5;
}

void gameInfo :: updateAllState (const double &angle) {
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

    int cnt;
    do {

        presentFrameBackground(false, angle);
        presentGameState(angle);
        presentIFrame (angle);
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

        SDL_Delay (20);

    } while (cnt > 0);
    SDL_DestroyRenderer(renderer);
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

void gameInfo :: RotateLeftAll (const int &level) {
    for (double angle = -10; angle >= -90; angle -= 10) {
        update(angle, level);
        SDL_Delay (0);
    }
    RotateLeft (ball);
    RotateLeft (destination);
    RotateLeft (block);
}

void gameInfo :: RotateRightAll (const int &level) {
    for (double angle = 10; angle <= 90; angle += 10) {
        update(angle, level);
        SDL_Delay (0);
    }
    RotateRight (ball);
    RotateRight (destination);
    RotateRight (block);
}

void gameInfo::presentLevelInfo (const int &level) {
    stringstream ss;
    ss << level;
    string levelNow = "";
    ss >> levelNow;
    levelNow = "img/level" + levelNow + ".bmp";

    SDL_Rect r, rbg;

    r.w = r.h = mainWindowsWidth * 0.1;
    r.y = mainWindowsHeight * 0.85 - r.h * 0.5;
    r.x = mainWindowsWidth * 0.5 - r.w * 0.5;

    rbg.x = rbg.y = 0;
    rbg.w = mainWindowsWidth;
    rbg.h = mainWindowsHeight;

    presentImage (rbg, background_link, 0);
    presentImage (r, levelNow, 0);
}

void gameInfo :: presentImage (const SDL_Rect r, const string &image_link, const double&angle) {

    SDL_Surface *background = SDL_LoadBMP(image_link.c_str());

    texture = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Point realCenter;
    realCenter.x = center.x - r.x;
    realCenter.y = center.y - r.y;

    SDL_RenderCopyEx (renderer, texture, NULL, &r, angle, &realCenter, SDL_FLIP_NONE);

    SDL_FreeSurface (background);
    SDL_DestroyTexture (texture);

}

void gameInfo :: presentIFrame (const double &angle) {
    SDL_Rect iframe;
    iframe.w = mainWindowsWidth * 0.44;
    iframe.h = iframe.w;
    iframe.x = mainWindowsWidth * 0.5 - iframe.w * 0.5;
    iframe.y = mainWindowsHeight * 0.4 - iframe.h * 0.5;
    presentImage (iframe, frame_link, angle);

}

void gameInfo :: presentFrameBackground (const bool &levelComplete, const double &angle) {

    if (levelComplete == false){
        presentImage (positionFrame, bgFrame_link, angle);
    }
    else {
        presentImage (positionFrame, completeLevel_link, angle);
    }
}

void gameInfo :: presentGameState (const double &angle) {

    double eachSize = positionFrame.h / 10.0;
    for (auto pos: block) {
        SDL_Rect blocks;
        blocks.w = blocks.h = eachSize;
        blocks.x = positionFrame.x + (pos.first - 1) * eachSize;
        blocks.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(blocks, block_link, angle);
    }

    for (auto pos: destination) {
        SDL_Rect destinations;
        destinations.w = destinations.h = eachSize;
        destinations.x = positionFrame.x + (pos.first - 1) * eachSize;
        destinations.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(destinations, destination_link, angle);
    }

    for (auto pos: ball) {
        SDL_Rect balls;
        balls.w = balls.h = eachSize;
        balls.x = positionFrame.x + (pos.first - 1) * eachSize;
        balls.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(balls, ball_link, angle);
    }
}

void gameInfo:: presentAllOtherThings ( const int &level) {

    renderer = SDL_CreateRenderer(window, -1, 0);

    presentLevelInfo(level);
    RotateButton myRotateLeftButton;
    myRotateLeftButton.init ("left");
    myRotateLeftButton.createButton (renderer);

    RotateButton myRotateRightButton;
    myRotateRightButton.init ("right");
    myRotateRightButton.createButton (renderer);

    BackButton myBackButton;
    myBackButton.init ();
    myBackButton.createButton (renderer);

}

void gameInfo:: update(const double &angle, const int &level) {
    presentAllOtherThings(level);
    updateAllState(angle);
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

void gameInfo :: displayComplete () {
    renderer = SDL_CreateRenderer(window, -1, 0);
    presentFrameBackground (true, 0);
    presentIFrame (0);
    SDL_RenderPresent (renderer);
    SDL_DestroyRenderer(renderer);
}

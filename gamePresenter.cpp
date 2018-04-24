
#include "gamePresenter.h"

using namespace myNamespace;
using namespace std;

gamePresenter :: gamePresenter (const int level) {
    generateLevel(level);
    positionFrame.w = MainWindowsWidth * 0.36;
    positionFrame.h = positionFrame.w;
    positionFrame.x = MainWindowsWidth * 0.5 - positionFrame.w * 0.5;
    positionFrame.y = MainWindowsHeight * 0.4 - positionFrame.h * 0.5;
    //--------------------------------------------------------------------
    center.x = positionFrame.x + positionFrame.w * 0.5;
    center.y = positionFrame.y + positionFrame.h * 0.5;
}

void gamePresenter :: RotateLeftAll (const int &level) {

    pushUndo ();

    for (double angle = -10; angle >= -90; angle -= 10) {
        update(angle, level);
        SDL_Delay (0);
    }
    RotateLeft (balls);
    RotateLeft (destinations);
    RotateLeft (blocks);
}

void gamePresenter :: RotateRightAll (const int &level) {

    pushUndo ();

    for (double angle = 10; angle <= 90; angle += 10) {
        update(angle, level);
        SDL_Delay (0);
    }
    RotateRight (balls);
    RotateRight (destinations);
    RotateRight (blocks);
}

void gamePresenter:: update(const double &angle, const int &level) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    presentAllOtherThings(level);
    updateAllState(angle, true);
    SDL_DestroyRenderer(renderer);
}

bool gamePresenter :: completeLevel () {
    for (auto destination: destinations) {
        bool found = false;
        for (auto ball: balls)
            if (destination.first == ball.first && destination.second == ball.second)
                found = true;
        if (!found) return false;
    }
    return true;
}

void gamePresenter :: displayComplete () {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    presentFrameBackground (true, 0);
    presentIFrame (0);
    SDL_RenderPresent (renderer);
    SDL_DestroyRenderer(renderer);
}

void gamePresenter :: undo () {
    if (undoQueue.empty ()) {
        SDL_ShowSimpleMessageBox (-1, "Nothing to undo!", "Nothing to undo!", window);
    } else {
        struct gameState previousGameState = undoQueue.back ();
        undoQueue.pop_back ();
        extractData (previousGameState);
    }
}

void gamePresenter :: restart () {
    pushUndo ();
    extractData (originalGameState);
}


void gamePresenter::freeResource() {
    while (int(balls.size()) > 0) balls.pop_back ();
    while (int(blocks.size()) > 0) blocks.pop_back ();
    while (int(destinations.size()) > 0) destinations.pop_back ();

    while (int(originalGameState.balls.size()) > 0) originalGameState.balls.pop_back ();
    while (int(originalGameState.blocks.size()) > 0) originalGameState.blocks.pop_back ();
    while (int(originalGameState.destinations.size()) > 0) originalGameState.destinations.pop_back ();

    while (!undoQueue.empty ()) undoQueue.pop_back ();
}


// public --------------------------------------------------------------------------------------
// private -------------------------------------------------------------------------------------


bool gamePresenter :: cmp (const pair <int, int> &a, const pair <int, int> &b) {
    return a.second > b.second;
}

void gamePresenter ::generateLevel(const int &levelNow) {
    int level = levelNow;
    if (level > MaxLevel) {
        level = rand () % MaxLevel + 1;
    }
    srand(time(NULL));
    set <pair <int, int> > myBalls, myBlocks;
    // generate balls
    vector < pair <int, int> > candidateBalls;
    for (int i = 0; i < Table_size; i++)
        for (int j = 0; j < Table_size; j++) {
            candidateBalls.push_back (make_pair(i + 1, j + 1));
        }
    random_shuffle(candidateBalls.begin(), candidateBalls.end());
    for (auto ball: candidateBalls) {
        myBalls.insert (ball);
        if (myBalls.size() >= level) {
            break;
        }
    }
    // generate blocks
    for (auto ball: myBalls) {
        int x = ball.first,
            y = ball.second;
        if (y == Table_size) continue;
        if (myBalls.find(make_pair(x, y + 1)) == myBalls.end()) {
            myBlocks.insert(make_pair(x, y + 1));
        }
    }
    // generate destinations
    for (auto ball: myBalls) {
        balls.push_back(ball);
    }
    for (auto block: myBlocks) {
        blocks.push_back(block);
    }
    vector <char> trace;
    for (int i = 0; i < level; i++) {
        bool Left = rand () % 2;
        if (Left == 1) {
            RotateLeft(balls);
            RotateLeft(blocks);
            trace.push_back('L');
            cout << "Left\n";
        } else {
            RotateRight(balls);
            RotateRight(blocks);
            trace.push_back('R');
            cout << "Right\n";
        }
        updateAllState(0, true);
    }
    cout << "------------------------------\n";

    // update vector destinations, blocks, balls
    destinations.clear ();
    for (auto destination: balls) {
        destinations.push_back(destination);
    }
    for (int i = level - 1; i > -1; i--) {
        char c = trace[i];
        if (c == 'L')
            RotateRight(destinations);
        else
            RotateLeft (destinations);
    }
    balls.clear ();
    blocks.clear ();
    for (auto block: myBlocks) {
        blocks.push_back(block);
    }
    for (auto ball: myBalls) {
        balls.push_back(ball);
    }
    compressData (originalGameState);
}

void gamePresenter :: RotateRight (vector <pair <int, int> > &v) {
    int h = Table_size;
    for (int i = 0; i < int(v.size()); i++) {
        int tmp = v[i].second;
        v[i].second = v[i].first;
        v[i].first = h - tmp + 1;
    }
}

void gamePresenter :: RotateLeft (vector <pair <int, int> > &v) {
    int w = Table_size;
    for (int i = 0; i < int(v.size()); i++) {
        int tmp = v[i].first;
        v[i].first = v[i].second;
        v[i].second = w - tmp + 1;
    }
}

void gamePresenter::presentLevelInfo (const int &level) {
    stringstream ss;
    ss << level;
    string levelNow = "";
    ss >> levelNow;
    levelNow = "img/level" + levelNow + ".bmp";

    SDL_Rect r, rbg;

    r.w = r.h = MainWindowsWidth * 0.1;
    r.y = MainWindowsHeight * 0.85 - r.h * 0.5;
    r.x = MainWindowsWidth * 0.5 - r.w * 0.5;

    rbg.x = rbg.y = 0;
    rbg.w = MainWindowsWidth;
    rbg.h = MainWindowsHeight;

    if (level > MaxLevel)
        levelNow = endless_link;

    presentImage (rbg, background_link, 0);
    presentImage (r, levelNow, 0);
}

void gamePresenter :: presentImage (const SDL_Rect r, const string &image_link, const double&angle) {

    SDL_Surface *background = SDL_LoadBMP(image_link.c_str());

    texture = SDL_CreateTextureFromSurface(renderer, background);

    SDL_Point realCenter;
    realCenter.x = center.x - r.x;
    realCenter.y = center.y - r.y;

    SDL_RenderCopyEx (renderer, texture, NULL, &r, angle, &realCenter, SDL_FLIP_NONE);

    SDL_FreeSurface (background);
    SDL_DestroyTexture (texture);

}

void gamePresenter :: presentIFrame (const double &angle) {
    SDL_Rect iframe;
    iframe.w = MainWindowsWidth * 0.44;
    iframe.h = iframe.w;
    iframe.x = MainWindowsWidth * 0.5 - iframe.w * 0.5;
    iframe.y = MainWindowsHeight * 0.4 - iframe.h * 0.5;
    presentImage (iframe, frame_link, angle);

}

void gamePresenter :: presentFrameBackground (const bool &levelComplete, const double &angle) {

    if (levelComplete == false){
        presentImage (positionFrame, bgFrame_link, angle);
    }
    else {
        presentImage (positionFrame, completeLevel_link, angle);
    }
}

bool gamePresenter :: inrange(const int &x, const int &y) {
    return 0 < x && x <= Table_size && 0 < y && y <= Table_size;
}

void gamePresenter :: presentGameState (const double &angle) {

    double eachSize = positionFrame.h / (1.0 * Table_size);
    for (auto pos: blocks) {
        SDL_Rect blocks;
        blocks.w = blocks.h = eachSize;
        blocks.x = positionFrame.x + (pos.first - 1) * eachSize;
        blocks.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(blocks, block_link, angle);
    }

    for (auto pos: destinations) {
        SDL_Rect destinations;
        destinations.w = destinations.h = eachSize;
        destinations.x = positionFrame.x + (pos.first - 1) * eachSize;
        destinations.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(destinations, destination_link, angle);
    }

    for (auto pos: balls) {
        SDL_Rect balls;
        balls.w = balls.h = eachSize;
        balls.x = positionFrame.x + (pos.first - 1) * eachSize;
        balls.y = positionFrame.y + (pos.second - 1) * eachSize;
        presentImage(balls, ball_link, angle);
    }
}

void gamePresenter:: presentAllOtherThings ( const int &level) {

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

    RestartButton myRestartButton;
    myRestartButton.init ();
    myRestartButton.createButton (renderer);

    UndoButton myUndoButton;
    myUndoButton.init ();
    myUndoButton.createButton (renderer);

}

void gamePresenter :: updateAllState (const double &angle, const bool &presentState) {
    bool state[Table_size + 1][Table_size + 1];
    memset (state, false, sizeof(state));
    for (auto info: blocks)
        state [info.first][info.second] = true;
    //------------------------------------------------------------------
    //sort (ball.begin(), ball.end(), cmp); // sort balls to easy manage
    set <pair <int, int> > isBall;
    isBall.clear();
    for (auto ball: balls) {
        isBall.insert (ball);
    }
    //------------------------------------------------------------------

    int cnt;
    do {
        if (presentState == true) {
            presentFrameBackground(false, angle);
            presentGameState(angle);
            presentIFrame(angle);
            SDL_RenderPresent(renderer);
        }

        cnt = 0;
        for (int i = 0; i < int(balls.size()); i++) {
            if (isBall.find (make_pair(balls[i].first, balls[i].second + 1)) == isBall.end()) { // is not another ball

                if (balls[i].second < Table_size && state[balls[i].first][balls[i].second + 1] == false) {

                    isBall.erase(balls[i]);
                    isBall.insert (make_pair(balls[i].first, balls[i].second + 1));

                    balls[i].second++;
                    cnt++;
                }
            }
        }

        SDL_Delay (25);

    } while (cnt > 0);
}

void gamePresenter :: compressData (gameState &gameState) {
    gameState.balls.clear ();
    gameState.blocks.clear ();
    gameState.destinations.clear ();
    for (auto ball: balls) {
        gameState.balls.push_back (ball);
    }
    for (auto block: blocks) {
        gameState.blocks.push_back (block);
    }
    for (auto destination: destinations) {
        gameState.destinations.push_back (destination);
    }
}

void gamePresenter :: extractData (gameState &gameState) {
    balls.clear ();
    blocks.clear ();
    destinations.clear ();
    for (auto ball: gameState.balls) {
        balls.push_back (ball);
    }
    for (auto block: gameState.blocks) {
        blocks.push_back (block);
    }
    for (auto destination: gameState.destinations) {
        destinations.push_back (destination);
    }
}

void gamePresenter :: pushUndo() {
    struct gameState newGameState;
    compressData (newGameState);
    undoQueue.push_back (newGameState);
    while (int(undoQueue.size()) > MaxUndo) {
        undoQueue.pop_front ();
    }
}
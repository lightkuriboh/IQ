#include "gameEngine.h"

using namespace myNamespace;

namespace myNamespace {
    SDL_Window *window;
    SDL_Surface *image_buttonStart;
    SDL_Surface *image_background;
    SDL_Surface *image_rotateLeft;
    SDL_Surface *image_rotateRight;
    SDL_Surface *image_completeLevel;
    SDL_Surface *image_bgFrame;
    SDL_Surface *image_iframe;
    SDL_Surface *image_ball;
    SDL_Surface *image_destination;
    SDL_Surface *image_block;
    SDL_Surface *image_back;
    SDL_Surface *image_endless;
    SDL_Surface *image_undo;
    SDL_Surface *image_restart;

    void processlevel (int &level, bool &stopGame, bool &levelUp, bool &backMenu) {

        gamePresenter newGame (level);
        newGame.update(0, level);

        while (!stopGame) {

            SDL_Event event;

            if (SDL_PollEvent(&event) != 0) {
                if (quit (event)) {
                    stopGame = true;
                    newGame.freeResource ();
                    return;
                }
                if (clickBackMenu (event) ) {
                    backMenu = true;
                    newGame.freeResource ();
                    return;
                }
                if (clickRotateLeft (event) ) {
                    newGame.RotateLeftAll (level);
                    newGame.update(0, level);
                }
                if (clickRotateRight (event)) {
                    newGame.RotateRightAll (level);
                    newGame.update(0, level);
                }
                if (clickRestart (event)) {
                    newGame.restart ();
                    newGame.update (0, level);
                }
                if (clickUndo (event)) {
                    newGame.undo ();
                    newGame.update (0, level);
                }
                if (!levelUp && newGame.completeLevel () ) {
                    levelUp = true;
                    SDL_Delay (200);
                    newGame.displayComplete ();
                    SDL_Delay (1000);
                    newGame.freeResource ();
                    return;
                }

            }
        }
    }

    void initGameMenu (UI &thisUI) {

        thisUI.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        thisUI.initBackground(background_link);

        StartButton myButtonStart;
        myButtonStart.init();
        myButtonStart.createButton(thisUI.renderer, image_buttonStart);
        SDL_RenderPresent(thisUI.renderer);
        SDL_DestroyRenderer(thisUI.renderer);
    }

    void StartOneThread (const int &height, const int &width) {

        bool stopGame = false;

        UI New;
        New._make_main_windows ("IQ", MainWindowsWidth, MainWindowsHeight);

        initGameData ();
        initGameMenu (New);

        bool started = false;
        bool inGame = false;
        int level = 1;
        bool levelUp = false;
        bool backMenu = false;

        while (!stopGame) {

            SDL_Event event;


            if (SDL_PollEvent(&event) != 0) {
                if (quit (event)) {
                    stopGame = true;
                }
                if (!inGame && clickStart(event)) {
                    started = true;
                    inGame = true;
                }
            }

            if (started == true || levelUp) {
                levelUp = false;
                processlevel (level, stopGame, levelUp, backMenu);
                started = false;
            }

            if (levelUp) {
                level++;
            }

            if (backMenu) {
                initGameMenu (New);
                inGame = false;
                backMenu = false;
            }
        }
        New.quitSDL();
    }

    void initOneImage (SDL_Surface *&surface, const string &link) {
        surface = SDL_LoadBMP(link.c_str());
    }

    void initGameData () {
        initOneImage (image_buttonStart, buttonStart_link);
        initOneImage (image_background, background_link);
        initOneImage (image_rotateLeft, RotateLeft_link);
        initOneImage (image_rotateRight, RotateRight_link);
        initOneImage (image_completeLevel, completeLevel_link);
        initOneImage (image_bgFrame, bgFrame_link);
        initOneImage (image_iframe, frame_link);
        initOneImage (image_ball, ball_link);
        initOneImage (image_destination, destination_link);
        initOneImage (image_block, block_link);
        initOneImage (image_back, back_link);
        initOneImage (image_endless, endless_link);
        initOneImage (image_undo, undo_link);
        initOneImage (image_restart, restart_link);
    }

}


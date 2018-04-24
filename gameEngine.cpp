#include "gameEngine.h"

using namespace myNamespace;

namespace myNamespace {
    SDL_Window *window;
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
        myButtonStart.createButton(thisUI.renderer);
        SDL_RenderPresent(thisUI.renderer);
        SDL_DestroyRenderer(thisUI.renderer);
    }

    void StartOneThread (const int &height, const int &width) {

        bool stopGame = false;

        UI New;
        New._make_main_windows ("IQ", MainWindowsWidth, MainWindowsHeight);
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
}


#include "gameEngine.h"

using namespace myNamespace;

namespace myNamespace {

    void processlevel (SDL_Window *&window, int &level, bool &stopGame, bool &levelUp, bool &backMenu) {

        gameInfo newGame (level, window);

        newGame.updateAllState (window);

        while (!stopGame) {

            SDL_Event event;

            if (SDL_PollEvent(&event) != 0) {
                if (quit (event)) {
                    stopGame = true;
                }
                if (clickRotateLeft (event) ) {
                    newGame.RotateLeftAll ();
                    newGame.updateAllState (window);
                }
                if (clickRotateRight (event)) {
                    newGame.RotateRightAll ();
                    newGame.updateAllState (window);
                }
                if (clickBackMenu (event) ) {
                    backMenu = true;
                    newGame.freeResource ();
                    return;
                }
                if (!levelUp && newGame.completeLevel () ) {
                    printf("Level %d Complete!\n", level);
                    levelUp = true;
                    newGame.displayComplete (window);
                    SDL_Delay (2000);
                    newGame.freeResource ();
                    return;
                }

            }
        }
    }

    void initGameMenu (UI &thisUI) {

        //thisUI._make_main_windows ("IQ", mainWindowsWidth, mainWindowsHeight);
        thisUI.initBackground(thisUI.window, background_link);

        StartButton myButtonStart;
        myButtonStart.init();
        myButtonStart.createButton(thisUI.window);

    }

    void StartOneThread (const int &height, const int &width) {

        bool stopGame = false;

        UI New;
        New._make_main_windows ("IQ", mainWindowsWidth, mainWindowsHeight);
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

                New.initBackground(New.window, background_link);

                RotateButton myRotateLeftButton;
                myRotateLeftButton.init ("left");
                myRotateLeftButton.createButton (New.window);

                RotateButton myRotateRightButton;
                myRotateRightButton.init ("right");
                myRotateRightButton.createButton (New.window);

                BackButton myBackButton;
                myBackButton.init ();
                myBackButton.createButton (New.window);

                levelUp = false;
                processlevel (New.window, level, stopGame, levelUp, backMenu);
                started = false;
            }

            if (levelUp) {
                if (level < maxLevel) {
                    level++;
                }
                else {
                    level = 1;
                    //break;
                }
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

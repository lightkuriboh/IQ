#include "gameEngine.h"

using namespace myNamespace;

namespace myNamespace {

    void processlevel (SDL_Window *&window, int &level, bool &stopGame, bool &levelUp) {

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
                if (!levelUp && newGame.completeLevel () ) {
                    printf("Level %d Complete!\n", level);
                    levelUp = true;
                    return;
                }
            }
        }
    }

    void StartOneThread (const int &height, const int &width) {

        bool stopGame = false;

        UI New;
        New._make_main_windows ("IQ", width, height);
        New.initBackground(New.window, background_link);

        StartButton myButtonStart;
        myButtonStart.init();
        myButtonStart.createButton(New.window);

        RotateButton myRotateRightButton;
        myRotateRightButton.init ("right");

        RotateButton myRotateLeftButton;
        myRotateLeftButton.init ("left");

        bool started = false;
        bool inGame = false;
        int level = 1;
        bool levelUp = false;

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

                myRotateLeftButton.createButton (New.window);

                myRotateRightButton.createButton (New.window);

                levelUp = false;
                processlevel (New.window, level, stopGame, levelUp);

                started = false;
            }
        }
        New.quitSDL();
    }

}

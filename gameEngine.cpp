#include "gameEngine.h"

using namespace myNamespace;

namespace myNamespace {
    SDL_Window *window;
    void processlevel (int &level, bool &stopGame, bool &levelUp, bool &backMenu) {

        gameInfo newGame (level);

        newGame.update(0, level);

        while (!stopGame) {

            SDL_Event event;

            if (SDL_PollEvent(&event) != 0) {
                if (quit (event)) {
                    stopGame = true;
                }
                if (clickRotateLeft (event) ) {
                    newGame.RotateLeftAll (level);
                    newGame.update(0, level);
                }
                if (clickRotateRight (event)) {
                    newGame.RotateRightAll (level);
                    newGame.update(0, level);
                }
                if (clickBackMenu (event) ) {
                    backMenu = true;
                    return;
                }
                if (!levelUp && newGame.completeLevel () ) {
                    levelUp = true;
                    newGame.displayComplete ();
                    SDL_Delay (2000);
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

                SDL_Renderer *renderer;
                renderer = SDL_CreateRenderer(window, -1, 0);
                New.initBackground(background_link);
                SDL_RenderPresent(renderer);
                SDL_DestroyRenderer(renderer);

                levelUp = false;
                processlevel (level, stopGame, levelUp, backMenu);
                started = false;
            }

            if (levelUp) {
                if (level < maxLevel) {
                    level++;
                }
                else {
                    level = 1;
                    break;
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

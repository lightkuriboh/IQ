#include "CreateWindows.h"
#include "EventHandler.h"
#include "config.h"
#include "gamePresenter.h"
#include "buttons.h"
#include <thread>

using namespace std;
using namespace myNamespace;

void  StartGame (const int &height, const int &width);
void  RunEventHandler ();
void StartOneThread (const int &height, const int &width);

int main ( int argc, char* args[] ) {

    //thread thread_game (StartGame, mainWindowsWidth, mainWindowsHeight);
    //thread thread_event (RunEventHandler);

    //thread_game.join();
    //thread_event.join();

    StartOneThread(mainWindowsHeight, mainWindowsWidth);

    return 0;
}

void StartOneThread (const int &height, const int &width) {

    bool stopGame = false;

    UI New;
    New._make_main_windows ("IQ", width, height);
    New.initBackground(New.window, background_link);

    button myButtonStart;
    myButtonStart.init();
    myButtonStart.createButton(New.window);

    bool started = false;
    bool inGame = false;

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
        if (started == true) {
            //SDL_ShowSimpleMessageBox(0, "You started the game!", SDL_GetError(), New.window);
            New.initBackground(New.window, background_link);
            gameInfo newGame (level, New.window);
            newGame.updateAllState(New.window);

            SDL_Delay(3000);

            newGame.RotateRightAll ();
            newGame.updateAllState(New.window);

            SDL_Delay(3000);

            newGame.RotateLeftAll ();
            newGame.updateAllState(New.window);

            SDL_Delay(3000);

            newGame.RotateLeftAll ();
            newGame.updateAllState(New.window);

            started = false;
        }
    }
    New.quitSDL();
}
/*
void StartGame (const int &width, const int &height) {
    try {

        UI New;
        New._make_main_windows ("IQ", width, height);
        while (!stopGame) {
            if (clickStartEvent) {
                SDL_ShowSimpleMessageBox(0, "You started the game!", SDL_GetError(), New.window);
                clickStartEvent = false;
            }
        }
        New.quitSDL();

    } catch (exception) {

    }
}

void  RunEventHandler () {
    while (true) {
        SDL_Event event;
        if (SDL_WaitEvent(&event) != 0) {

            if (clickStart(event)) {
                clickStartEvent = true;
            }
            else
            if (quit(event)) {
                stopGame = true;
                return;
            }
        }
    }
}
*/

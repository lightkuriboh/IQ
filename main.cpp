#include "CreateWindows.h"
#include "EventHandler.h"
#include "config.h"

using namespace std;
using namespace myNamespace;

void  StartGame (const int &height, const int &width);

int main ( int argc, char* args[] ) {

    StartGame (mainWindowsWidth, mainWindowsHeight);

    return 0;
}

void StartGame (const int &width, const int &height) {
    try {
        while (true) {
            UI New;
            New._make_main_windows ("Renewed Hang Man", width, height);

            while (true) {

                SDL_Event event;

                if (SDL_WaitEvent(&event) != 0) {

                    if (clickStart(event)) {
                        SDL_ShowSimpleMessageBox(0, "You started the game!", SDL_GetError(), New.window);
                    }
                    else
                    if (waitUntilMouseWheel(event)) {
                        New.quitSDL ();
                        return;
                    }
                }
            }
        }

    } catch (exception) {

    }
}



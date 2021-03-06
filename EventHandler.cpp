#include "EventHandler.h"

namespace myNamespace {
    pair <int, int> mouseClickLeft (const SDL_Event &event) {

        if ( event.type == SDL_MOUSEBUTTONDOWN ) {
            SDL_MouseButtonEvent but = event.button;
            if (but.button == SDL_BUTTON_LEFT) {
                return make_pair(event.motion.x, event.motion.y);
            }
        }
        return make_pair(-1, -1);
    }

    pair <int, int> mouseClickRight (const SDL_Event &event) {

        if ( event.type == SDL_MOUSEBUTTONDOWN ) {
            SDL_MouseButtonEvent but = event.button;
            if (but.button == SDL_BUTTON_RIGHT) {
                return make_pair(event.motion.x, event.motion.y);
            }
        }
        return make_pair(-1, -1);
    }

    bool inRect (const int &x, const int &y, const SDL_Rect &r) {
        return (x >= r.x && y >= r.y && x <= r.x + r.w && y <= r.y + r.h);
    }

    bool clickStart(const SDL_Event & event) {
        StartButton button;
        button.init ();
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, button.r);
    }

    bool clickRotateLeft (const SDL_Event & event) {
        RotateButton RotateLeft;
        RotateLeft.init ("left");
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, RotateLeft.r);
    }

    bool clickRotateRight (const SDL_Event & event) {
        RotateButton RotateRight;
        RotateRight.init ("Right");
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, RotateRight.r);
    }

    bool clickBackMenu (const SDL_Event & event) {
        BackButton backButton;
        backButton.init();
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, backButton.r);
    }

    bool clickUndo (const SDL_Event &event) {
        UndoButton myUndoButton;
        myUndoButton.init ();
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, myUndoButton.r);
    }

    bool clickRestart (const SDL_Event &event) {
        RestartButton myRestartButton;
        myRestartButton.init ();
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, myRestartButton.r);
    }

    bool quit (const SDL_Event &event) {

        if ( 0 || event.type == SDL_QUIT ) return true;
        return false;
    }
}

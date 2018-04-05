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
        buttonStart button;
        button.init ();
        pair <int, int> pos = mouseClickLeft(event);
        return inRect (pos.first, pos.second, button.r);
    }

    bool quit (const SDL_Event &event) {

        if ( 0 || event.type == SDL_QUIT ) return true;
        return false;
    }
}

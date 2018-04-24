#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

using namespace std;
#include <string>
#include <SDL2/SDL.h>

const int mainWindowsWidth  = 960;
const int mainWindowsHeight = 640;

const string buttonStart_link = "img/button_start.bmp";
const string background_link = "img/bg.bmp";
const string RotateLeft_link = "img/rotate_left.bmp";
const string RotateRight_link = "img/rotate_right.bmp";
const string completeLevel_link = "img/completeLevel.bmp";
const string bgFrame_link = "img/bg_frame.bmp";
const string frame_link = "img/frame.bmp";
const string ball_link = "img/ball.bmp";
const string destination_link = "img/destination.bmp";
const string block_link = "img/block.bmp";
const string back_link = "img/back.bmp";
const string endless_link = "img/endless.bmp";
const string undo_link = "img/undo.bmp";
const string restart_link = "img/restart.bmp";

const int MaxLevel = 10;
const int MaxUndo = 11;
const int Table_size = 12;

namespace myNamespace {
    extern SDL_Window *window;
}

#endif // CONFIG_H_INCLUDED

#include "gameEngine.h"
#include <iostream>

using namespace std;
using namespace myNamespace;

int main ( int argc, char* args[] ) {

    cout << "Have " << argc << " arguments:\n";
    for (int i = 0; i < argc; i++)
        cout << args[i] << "\n";

    StartOneThread (mainWindowsHeight, mainWindowsWidth);

    return 0;
}


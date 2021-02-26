#include <iostream>
#include <SDL2/SDL.h>
#include "Headers/Screen.h"

using namespace std;

int main() {

    char n;

    cout << "                         TIC TAC TOE                       " << endl;
    cout << "                Here is what you need to know              " << endl;

    cout << "# The game is played by two players one uses a not(O) as a symbol and one uses a cross(X)" << endl;
    cout << "# The first chance is played by the one who chooses a not " << endl;
    cout << "# The player who succeeds in placing three marks in a horizontal, vertical, or diagonal" << endl;
    cout << "  wins the game" << endl;
    cout << "# The symbol of the player who wins will be displayed on the screen after the game ends " << endl;
    cout << "# If it is a tie then a dash '-' will be displayed" << endl;

    cout << endl << "Do you want to continue (y/n) :" << flush;
    cin >> n;
    cout << endl;


    if (n == 'y') {
        Screen screen;
        if (screen.init() == 0) {
            //error encountered
            screen.close();
            return 1;
        }

        screen.setUp(0, 250, 250);
        screen.drawLines();


        while (true) {

            screen.update();

            if (!screen.processEvent()) {
                break;
            }

        }

        screen.close();
    } else if (n == 'n') {
        cout << "quitting ..................." << endl;
    } else {
        cout << "wrong input please try again, Thank You!" << endl;
    }

    SDL_Delay(500);

    return 0;
}
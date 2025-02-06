#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "CricketScoreboard.h"
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    CricketScoreboard scoreboard;

    scoreboard.startMatch();
    scoreboard.showMenu();

    return 0;
}




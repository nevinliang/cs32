//
//  main.cpp
//  CS32Project1
//
//  Created by Nevin Liang on 6/26/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

// zion_solution.cpp

#include "Game.h"

#include <cstdlib>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 80);

      // Play the game
    g.play();
}

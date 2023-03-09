//
//  Game.h
//  CS32Project1
//
//  Created by Nevin Liang on 6/27/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Arena;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};

#endif /* Game_h */

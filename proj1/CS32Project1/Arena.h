//
//  Arena.h
//  CS32Project1
//
//  Created by Nevin Liang on 6/27/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#ifndef Arena_h
#define Arena_h

#include "globals.h"
#include "Previous.h"
#include <string>

class Player;
class Robot;

class Arena
{
  public:
        // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(std::string msg) const;
    
    // accessor method for the new previous variable
    // Name: thePrevious
    // Input: nothing
    // Output: Previous reference
    Previous& thePrevious();

        // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
    Previous m_prev;
};

#endif /* Arena_h */

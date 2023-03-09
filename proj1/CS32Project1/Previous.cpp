//
//  Previous.cpp
//  CS32Project1
// 
//  Created by Nevin Liang on 6/27/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include "Previous.h"
#include <iostream>

using namespace std;

Previous::Previous(int nRows, int nCols) { 
    // initiate the number of rows and columns for the previous 2d array
    m_rows = nRows;
    m_cols = nCols;
    
    // set all the number of turns to 0 first
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_turns[i][j] = 0;
        }
    }
}

bool Previous::dropACrumb(int r, int c) {
    // r and c are (1,1) top right so -- each
    r--;
    c--;
    // check if in bounds
    if (r < 0 || c < 0 || r >= m_rows || c >= m_cols) {
        return false;
    }
    // update number of times it has been to that square
    m_turns[r][c]++;
    return true;
}

void Previous::showPreviousMoves() const {
    // call func to clear entire screen
    clearScreen();
    // loop through every value in the 2d array of # moves
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            
            // if the number of moves is 0 then output '.'
            // if its any number from 1-26, then output the correct letter
            // else output Z
            
            int x = m_turns[i][j];
            char c;
            if (x == 0) {
                c = '.';
            }
            else if (x <= 26){
                c = 'A' + (x - 1);
            }
            else {
                c = 'Z';
            }
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
    return;
}



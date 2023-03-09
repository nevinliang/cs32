//
//  Previous.h
//  CS32Project1
//
//  Created by Nevin Liang on 6/27/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#ifndef Previous_h
#define Previous_h

#include "globals.h"

class Previous
{
public:
    // Name: Previous
    // Input: number of rows and columns (integers)
    // Type: Constructor
    Previous(int nRows, int nCols);
    
    // Name: dropACrumb
    // Input: coordinates (two integers) r, c
    // Output: boolean (successful or not)
    bool dropACrumb(int r, int c);
    
    // Name: showPreviousMoves
    // Input: N/A
    // Output: N/A
    // Visual output: 2d array of all historic moves
    void showPreviousMoves() const;

private:
    int m_turns[MAXROWS][MAXCOLS];
    int m_rows;
    int m_cols;
    
};

#endif /* Previous_h */

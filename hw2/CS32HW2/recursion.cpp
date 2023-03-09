//
//  recursion.cpp
//  CS32HW2
//
//  Created by Nevin Liang on 7/20/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

// Name: product
// Input: unsigned integers m and n
// Output: integer product
// Description: Returns the product of two non-negative integers, m and n, // using only repeated addition.
int product(unsigned int m, unsigned int n)
{
    // when n reaches 0 or is already 0, return 0 because x * 0 = 0
    if (n == 0) return 0;
    // if its not, then add m to whatever is left making sure to decrement n
    else return m + product(m, n - 1);
}


// Name: digitCount
// Input: integers number and digit
// Output: integer number of occurences
// Description: Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
//      digitCount(18838, 8) =>3
//      digitCount(55555, 3) =>0
//      digitCount(0, 0) => 0 or 1 (either if fine)
//
int digitCount(int num, int digit)
{
    // when the number left is just 0, then return 0
    if (num == 0) return 0;
    // otherwise, if the number's units digit is digit then add 1 to the recursive sum
    // perpetuate the recursion by taking away the last digit
    else return (num % 10 == digit) + digitCount(num / 10, digit);
}

// Name: doubleDouble
// Input: a string n
// Output: a string that has been modified
// Description: Returns a string where the same characters next each other in
// string n are separated by "333"
//
// Pseudocode Example:
//      terribleTriplets("goodbye") => "go333odbye"
//      terribleTriplets ("yyuu") => "y333yu333u"
//      terribleTriplets ("aaaa") => "a333a333a333a" //
string doubleDouble(string n)
{
    // if the remaining length is just 0 or 1 then there can't be two characters next to each other
    if (n.length() <= 1) return n;
    // otherwise, insert a 333 in between the first character and the second if they match
    // recurse deeper
    else return n.substr(0, 1) + ((n[0] == n[1]) ? "333" : "") + doubleDouble(n.substr(1));
}

// Name: hipToBeSquare
// Input: string str
// Output: string modified
// Description: str contains a single pair of square brackets, return a new
// string made of only the square brackets and whatever those
// square brackets contain
//
// Pseudocode Example:
//      hipToBeSquare("abc[ghj]789") => "[ghj]"
//      hipToBeSquare("[x]7") => "[x]"
//      hipToBeSquare("4agh[y]") => "[y]"
//      hipToBeSquare("4agh[]") => "[]"
//
string hipToBeSquare(string str)
{
    // if the first char isn't a bracket then cut it off and go deeper
    if (str[0] != '[') return hipToBeSquare(str.substr(1));
    // if the last char isn't a bracket then cut it off and go deeper
    else if (str[str.length() - 1] != ']') return hipToBeSquare(str.substr(0, str.length() - 1));
    // here both first and last char of str will be [ and ] respectively
    return str;
}

// Name: summerSolstice
// Input: array of integers, size of array, and target value for sum
// Output: is it possible to make the target sum
// Description: Return true if the total of any combination of elements in
// the array a equals the value of the target.
//
// Pseudocode Example:
//      summerSolstice([2, 4, 8], 3, 10) => true
//      summerSolstice([2, 4, 8], 3, 6) => true
//      summerSolstice([2, 4, 8], 3, 11) => false
//      summerSolstice([2, 4, 8], 3, 0) => true
//      summerSolstice([], 0, 0) => true
bool summerSolstice(const int a[], int size, int target)
{
    // if the size isnt 0, then recurse two cases if target isnt 0, otherwise return 0
    // either the last element in the existing array is included or it isnt
    // return the OR of either case because both are likely and possible
    return (!size) ? (!target) : (summerSolstice(a, size - 1, target) || summerSolstice(a, size - 1, target - a[size - 1]));
}

// Name: isThisTheEnd
// Input: maze array, number of rows and columns, source row and column, and ending row and column
// Output: is the maze solvable
// Description: returns whether the maze is solvable
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool isThisTheEnd(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    // if reached end return true
    if (sr == er && sc == ec) return true;
    // mark as visited
    maze[sr][sc] = '0';
    // direction array
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    // loop each direction
    for (int i = 0; i < 4; i++) {
        // new coordinates
        int nr = sr + dir[i][0], nc = sc + dir[i][1];
        // check if on map
        if (nr >= 0 && nc >= 0 && nr < nRows && nc < nCols)
            // check if allowed to move there
            if (maze[nr][nc] != 'X' && maze[nr][nc] != '@' && maze[nr][nc] != '0') {
                // check if new position can reach maze
                bool yes = isThisTheEnd(maze, nRows, nCols, nr, nc, er, ec);
                // if can then immediately return true
                if (yes) return true;
            }
    }
    // if no direction can, then return false
    return false;
}

int main() {
    return 0;
}

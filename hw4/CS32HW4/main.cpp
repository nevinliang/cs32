//
//  main.cpp
//  CS32HW4
//
//  Created by Nevin Liang on 8/16/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//
#include "WordTree.h"
#include <iostream>

using namespace std;

int main() {
    WordTree w;
    w.add("Harry");
    w.add("Niall");
    w.add("Niall");
    w.add("Liam");
    w.add("Louis");
    w.add("Harry");
    w.add("Niall");
    w.add("Zayn");

    WordTree z = w;

    WordTree f(z);

    cout << f;
    cout << f.distinctWords() << endl;
    cout << f.totalWords() << endl;
}

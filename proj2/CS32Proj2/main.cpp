//
//  main.cpp
//  CS32Proj2
//
//  Created by Nevin Liang on 7/14/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
#include "BirthdayParty.h"

using namespace std;

//void t1() {
//    BirthdayParty theLastDance;
//    theLastDance.addInvitee ("Michael", "Jordan", 23);
//    theLastDance.addInvitee ("Scottie", "Pippen", 33);
//    theLastDance.addInvitee ("Dennis", "Rodman", 91);
//    theLastDance.addInvitee ("Luc", "Longley", 13);
//    theLastDance.addInvitee ("Ron", "Harper", 9);
//    for (int n = 0; n < theLastDance.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        theLastDance.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t2() {
//    BirthdayParty dodgers;
//    dodgers.addInvitee("Clayton", "Kershaw", 31.0);
//    dodgers.addInvitee("Cody", "Bellinger", 11.5);
//    assert(!dodgers.personOnGuestList ("",""));
//
//    dodgers.addInvitee("Mookie", "Betts", 27.0);
//    dodgers.addInvitee("", "", 0.57);
//    dodgers.addInvitee("Justin", "Turner", 20.0);
//    assert(dodgers.personOnGuestList ("", ""));
//
//    dodgers.dropFromGuestList("Mookie", "Betts");
//    assert(dodgers.whosOnTheGuestList() == 4 && dodgers.personOnGuestList("Clayton", "Kershaw")
//           && dodgers.personOnGuestList ("Cody", "Bellinger") && dodgers.personOnGuestList ("Justin", "Turner")
//           && dodgers.personOnGuestList ("", ""));
//}
//
//void t3() {
//    BirthdayParty bpOne;
//    bpOne.addInvitee("Kobe", "Bryant", 8);
//    bpOne.addInvitee("AC", "Green", 45);
//    bpOne.addInvitee("Shaquille", "Oneal", 34);
//
//    BirthdayParty bpTwo;
//    bpTwo.addInvitee("Kobe", "Bryant", 8);
//    bpTwo.addInvitee("Horace", "Grant", 54);
//
//    BirthdayParty bpJoined;
//    cout << combineGuestLists(bpOne, bpTwo, bpJoined) << endl;
//
//    for (int n = 0; n < bpJoined.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        bpJoined.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t4() {
//    BirthdayParty bpOne;
//    bpOne.addInvitee("Kobe", "Bryant", 8);
//    bpOne.addInvitee("AC", "Green", 45);
//    bpOne.addInvitee("Shaquille", "Oneal", 34);
//
//    BirthdayParty bpTwo;
//    bpTwo.addInvitee("Kobe", "Bryant", 24);
//    bpOne.addInvitee("Pau", "Gasol", 16);
//
//    BirthdayParty bpJoined;
//    cout << combineGuestLists(bpOne, bpTwo, bpJoined) << endl;
//
//    for (int n = 0; n < bpJoined.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        bpJoined.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t5() {
//    BirthdayParty memories;
//    memories.addInvitee("Gianna", "Bryant", 13);
//    memories.addInvitee("Kobe", "Bryant", 41);
//    memories.addInvitee("Little", "Richard", 87);
//    memories.addInvitee("Jerry", "Stiller", 92);
//
//    BirthdayParty bpResult;
//    verifyGuestList("*", "Bryant", memories, bpResult);
//
//    for (int n = 0; n < bpResult.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        bpResult.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t6() {
//    BirthdayParty moreMemories;
//    moreMemories.addInvitee("Kirk", "Douglas", 103);
//    moreMemories.addInvitee("Fred", "Neal", 77);
//    moreMemories.addInvitee("Pop", "Smoke", 20);
//    moreMemories.addInvitee("Fred", "Willard", 86);
//
//    BirthdayParty result;
//    verifyGuestList("Fred", "*", moreMemories, result);
//
//    for (int n = 0; n < result.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        result.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//
//    verifyGuestList("*", "*", moreMemories, result);
//
//    for (int n = 0; n < result.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        result.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//
//    BirthdayParty result2;
//    result2.addInvitee("Bob", "Joe", 103);
//
//    verifyGuestList("ASDF", "ASDF", moreMemories, result2);
//
//    for (int n = 0; n < result2.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        result2.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t7() {
//    BirthdayParty moreMemories;
//    moreMemories.addInvitee("Kirk", "Douglas", 103);
//    moreMemories.addInvitee("Fred", "Neal", 77);
//    moreMemories.addInvitee("Pop", "Smoke", 20);
//    moreMemories.addInvitee("Fred", "Willard", 86);
//
//    BirthdayParty result;
//    verifyGuestList("Fred", "*", moreMemories, moreMemories);
//    for (int n = 0; n < moreMemories.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        moreMemories.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t8() {
//    BirthdayParty bpOne;
//    bpOne.addInvitee("Kobe", "Bryant", 8);
//    bpOne.addInvitee("AC", "Green", 45);
//    bpOne.addInvitee("Shaquille", "Oneal", 34);
//
//    BirthdayParty bpTwo;
//    bpTwo.addInvitee("Kobe", "Bryant", 24);
//    bpOne.addInvitee("Pau", "Gasol", 16);
//
//    BirthdayParty bpJoined;
//    cout << combineGuestLists(bpOne, bpTwo, bpTwo) << endl;
//
//    for (int n = 0; n < bpTwo.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        bpTwo.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}
//
//void t9() {
//    BirthdayParty bpOne;
//    bpOne.addInvitee("Kobe", "Bryant", 8);
//    bpOne.addInvitee("AC", "Green", 45);
//    bpOne.addInvitee("Shaquille", "Oneal", 34);
//
//    bpOne.modifyInvitee("AC", "Green", 100);
//    bpOne.dropFromGuestList("Shaquille", "Oneal");
//    bpOne.dropFromGuestList("Kobe", "Bryant");
//
//    int test;
//    cout << bpOne.noInvitees() << endl;
//    cout << bpOne.checkGuestList("Kobe", "Bryant", test) << endl;;
//
//    for (int n = 0; n < bpOne.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        bpOne.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//
//    cout << bpOne.dropFromGuestList("AC", "Green") << endl;
//
//    for (int n = 0; n < bpOne.whosOnTheGuestList(); n++) {
//        string first;
//        string last;
//        int val;
//        bpOne.selectInvitee (n, first, last, val);
//        cout << first << " " << last << " " << val << endl;
//    }
//}

int main() {
//    t1();
//    cout << "-------" << endl;
//    t2();
//    cout << "-------" << endl;
//    t3();
//    cout << "-------" << endl;
//    t4();
//    cout << "-------" << endl;
//    t5();
//    cout << "-------" << endl;
//    t6();
//    cout << "-------" << endl;
//    t7();
//    cout << "-------" << endl;
//    t8();
//    cout << "-------" << endl;
//    t9();
}


//
//  BirthdayParty.h
//  CS32Proj2
//
//  Created by Nevin Liang on 7/14/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#ifndef BirthdayParty_h
#define BirthdayParty_h

#include <string>

typedef std::string BirthdayType;

class BirthdayParty
{
public:
    // Name: BirthdayParty
    // Input: ----
    // Output: ----
    // Description: Create an empty BirthdayParty list
    BirthdayParty();
    
    // Name: BirthdayParty
    // Input: const BirthdayParty& rhs
    // Output: ----
    // Description: Copy Constructor for Birthday Party
    BirthdayParty(const BirthdayParty& rhs);
    
    // Name: operator=
    // Input: const BirthdayParty& rhs
    // Output: const BirthdayParty&
    // Description: Assignment operator for Birthday Party
    const BirthdayParty& operator=(const BirthdayParty& rhs);
    
    // Name: ~BirthdayParty
    // Input: --
    // Output: --
    // Description: Destructor
    ~BirthdayParty();
    
    // Name: noInvitees
    // Input: --
    // Output: boolean
    // Description: Return true if the BirthdayParty list is empty, otherwise false.
    bool noInvitees() const;
    
    // Name: whosOnTheGuestList
    // Input: --
    // Output: int num players
    // Description: Return the number of players in the BirthdayParty list.
    int whosOnTheGuestList() const;
    
    // Name: addInvitee
    // Input: const std::string& firstName, const std::string& lastName,
    // const BirthdayType& value
    // Output: bool successfulness in adding invitee
    // Description: If the full name (both the first and last name) is not equal
    // to any full name currently in the list then add it and return
    // true. Elements should be added according to their last name.
    // Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and
    // return false (indicating that the name is already in the
    // list).
    bool addInvitee(const std::string& firstName, const std::string& lastName,
                    const BirthdayType& value);
    
    // Name: modifyInvitee
    // Input: const std::string& firstName, const std::string& lastName,
    // const BirthdayType& value
    // Output: bool successfulness in modifying invitee
    // Description: If the full name is equal to a full name currently in the
    // list, then make that full name no longer map to the value it
    // currently maps to, but instead map to the value of the third
    // parameter; return true in this case. Otherwise, make no
    // change to the list and return false.
    bool modifyInvitee(const std::string& firstName, const std::string& lastName,
                       const BirthdayType& value);

    // Name: addOrModify
    // Input: const std::string& firstName, const std::string& lastName,
    // const BirthdayType& value
    // Output: bool value of succeessfulness of adding/modifying (always true)
    // Description: If full name is equal to a name currently in the list, then
    // make that full name no longer map to the value it currently
    // maps to, but instead map to the value of the third parameter;
    // return true in this case. If the full name is not equal to
    // any full name currently in the list then add it and return
    // true. In fact, this function always returns true.
    bool addOrModify(const std::string& firstName, const std::string& lastName,
                     const BirthdayType& value);
    
    // Name: dropFromGuestList
    // Input: const std::string& firstName, const std::string& lastName
    // Output: bool value of successfulness of dropping person
    // Description: If the full name is equal to a full name currently in the
    // list, remove the full name and value from the list and return
    // true. Otherwise, make no change to the list and return
    // false.
    bool dropFromGuestList(const std::string& firstName, const std::string& lastName);
    
    // Name: personOnGuestList
    // Input: const std::string& firstName, const std::string& lastName
    // Output: boolean, whether the person is on the guest list
    // Description: Return true if the full name is equal to a full name
    // currently in the list, otherwise false.
    bool personOnGuestList(const std::string& firstName, const std::string& lastName) const;
    
    // Name: checkGuestList
    // Input: const std::string& firstName, const std::string& lastName,
    // BirthdayType& value
    // Output: bool of whether the person exists
    // Description: If the full name is equal to a full name currently in the
    // list, set value to the value in the list that that full name
    // maps to, and return true. Otherwise, make no change to the
    // value parameter of this function and return false.
    bool checkGuestList(const std::string& firstName, const std::string& lastName,
                        BirthdayType& value) const;

    // Name: selectInvitee
    // Input: int i, std::string& firstName, std::string& lastName,
    // BirthdayType& value
    // Output: bool if person exists
    // Description: If 0 <= i < size(), copy into firstName, lastName and value
    // parameters the corresponding information of the element at
    // position i in the list and return true. Otherwise, leave the
    // parameters unchanged and return false. (See below for details
    // about this function.)
    bool selectInvitee(int i, std::string& firstName, std::string& lastName,
                       BirthdayType& value) const;

    // Name: changeGuestList
    // Input: BirthdayParty& other
    // Output: ----
    // Description: Exchange the contents of this list with the other one.
    void changeGuestList(BirthdayParty& other);

private:
    // Doubly linked list Node structure
    struct Node {
        // has to contain a val, and prev AND next pointers
        BirthdayType value;
        std::string firstName;
        std::string lastName;
        
        Node* next;
        Node* prev;
        
        // constructor for easy node creation :))
        Node(std::string f = "", std::string l = "", BirthdayType v = BirthdayType()) {
            
            next = nullptr;
            prev = nullptr;
            firstName = f;
            lastName = l;
            value = v;
        }
    };
    // head node of doubly linked list
    Node* head;
    
    // size of linked list to expedite a few functions
    int size;
};

// Name: combineGuestLists
// Input: const BirthdayParty & bpOne, const BirthdayParty & bpTwo,
// BirthdayParty & bpJoined
// Output: boolean telling whether any conflicting info
// Description: If a full name appears in exactly one of bpOne and bpTwo, then bpJoined
// must contain an element consisting of that full name and its corresponding value.
// If a full name appears in both bpOne and bpTwo, with the same corresponding value in both,
// then bpJoined must contain an element with that full name and value.
// When this function returns, bpJoined must contain no elements other than those required by these rules.
bool combineGuestLists(const BirthdayParty & bpOne, const BirthdayParty & bpTwo,
                       BirthdayParty & bpJoined);

// Name: verifyGuestList
// Input: const std::string& fsearch, const std::string& lsearch,
// const BirthdayParty& bpOne, BirthdayParty& bpResult
// Output: ----
// Description: bpResult will contain a copy of all the elements in bpOne that match the search terms;
// a * means a wildcard that can be used in place of either fsearch or lsearch which means anything
// puts everything matching search criteria into bpResult
void verifyGuestList (const std::string& fsearch, const std::string& lsearch,
                      const BirthdayParty& bpOne, BirthdayParty& bpResult);

#endif /* BirthdayParty_h */

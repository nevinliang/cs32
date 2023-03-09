//
//  BirthdayParty.cpp
//  CS32Proj2
//
//  Created by Nevin Liang on 7/14/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include "BirthdayParty.h"

BirthdayParty::BirthdayParty() {
    head = nullptr;
}

BirthdayParty::BirthdayParty(const BirthdayParty& rhs) {
    // if rhs is empty just initialize an empty linkedlist
    if (rhs.head == nullptr) {
        head = nullptr;
    }
    // otherwise, make the head node and copy all the remaining vals
    else {
        // make the head node
        head = new Node(rhs.head->firstName, rhs.head->lastName, rhs.head->value);
        
        // initialize both list's iterators
        Node* iter = head;
        Node* riter = rhs.head->next;
        
        // loop through and add all the remaining elements
        while (riter != nullptr) {
            // add node riter points to to this linkedlist
            iter->next = new Node(riter->firstName, riter->lastName, riter->value);
            // make sure to attach it backwards as well!!
            iter->next->prev = iter;
            // no need to attach it forwards because default is nullptr for next
            
            // increment iterators
            iter = iter->next;
            riter = riter->next;
        }
    }
}

const BirthdayParty &BirthdayParty::operator=(const BirthdayParty &rhs) {
    // as written in HW 1 solution by Professor Ambrosio
    
    // make sure no aliasing errors
    if (this == &rhs) {
        return *this;
    }
    // copy and swap idioom
    BirthdayParty temp = rhs;
    changeGuestList(temp);
    return *this;
}

BirthdayParty::~BirthdayParty() {
    // as written in HW 1 soultion by Professor Ambrosio
    
    // loop through every iter and delete head nodes while incrementing them
    Node *iter;
    while (head != nullptr) {
        iter = head;
        head = head->next;
        // deep delete
        delete iter;
    }
}

bool BirthdayParty::noInvitees() const {
    return head == nullptr;
}

int BirthdayParty::whosOnTheGuestList() const {
    // loop through every guest in the list and increment size counter
    int size = 0;
    Node* iter = head;
    while (iter != nullptr) {
        size++;
        iter = iter->next;
    }
    // return that value
    return size;
}

bool BirthdayParty::addInvitee(const std::string &firstName,
                               const std::string &lastName, const BirthdayType &value) {
    
    // make a new node with those values
    Node* n = new Node(firstName, lastName, value);
    
    if (head == nullptr) {
        // set new Node with parameter characteristics as head
        head = n;
        return true;
    }
    
    else {
        // there exists a head node
        Node* iter = head;
        // temporary tail node
        Node* tail = nullptr;
        while (iter != nullptr) {
            if (lastName < iter->lastName || (lastName == iter->lastName
                                              && firstName < iter->firstName)) {
                // insert the Node before the current one
                n->next = iter;
                // inserting before head and not have different algos
                if (iter == head) {
                    // only have to adjust iter's prev and n
                    iter->prev = n;
                    n->next = iter;
                    // but also head node
                    head = n;
                }
                else {
                    // adjust the two arrows that change endpoints
                    n->next = iter;
                    n->prev = iter->prev;
                    // and also connect n
                    iter->prev->next = n;
                    iter->prev = n;
                }
                return true;
            }
            // here, iter and node n have identical names
            else if (lastName == iter->lastName && firstName == iter->firstName) {
                // so the person already exists
                return false;
            }
            // if we are at the last node
            if (iter->next == nullptr) {
                // insert the node element after this node
                tail = iter;
            }
            iter = iter->next;
        }
        // if reached here, then insert after tail pointer
        tail->next = n;
        n->prev = tail;
        return true;
    }
}

bool BirthdayParty::modifyInvitee(const std::string &firstName,
                                  const std::string &lastName, const BirthdayType &value) {
    // loop through every element in linkedlist test if firstName, lastName exists
    Node* iter = head;
    while (iter != nullptr) {
        // if it does, edit the value to match the passed in value
        if (iter->firstName == firstName && iter->lastName == lastName) {
            iter->value = value;
            return true;
        }
        // increment pointer
        iter = iter->next;
    }
    // reaches here -> no value of (firstname, lastname)
    return false;
}

bool BirthdayParty::addOrModify(const std::string &firstName,
                                const std::string &lastName, const BirthdayType &value) {
    // function is twice as slow but much shorter and easier to undestand code
    // if addInvitee returns true, exit method. else, make sure to modifyInvitee
    if (!addInvitee(firstName, lastName, value)) {
        modifyInvitee(firstName, lastName, value);
    }
    // function always returns true
    return true;
}

bool BirthdayParty::dropFromGuestList(const std::string &firstName,
                                      const std::string &lastName) {
    // loop through the entire linkedlist to find the person with that name
    Node* iter = head;
    while (iter != nullptr) {
        if (iter->firstName == firstName && iter->lastName == lastName) {
            // remove the person
            // case 1: iter is head
            if (iter == head) {
                // set pointer next to head
                head = iter->next;
                // delete pointer
                delete iter;
                // pointer next's prev to null
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            }
            else if (iter->next == nullptr) {
                // the iter is the tail of the list
                iter->prev->next = nullptr;
                delete iter;
            }
            else {
                // the iter is somewhere in the middle
                // adjust neighboring pointers
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                delete iter;
            }
            return true;
        }
        iter = iter->next;
    }
    // if reached here, cant find a person with that name
    return false;
}

bool BirthdayParty::personOnGuestList(const std::string &firstName,
                                      const std::string &lastName) const {
    // loop through every name
    Node* iter = head;
    while (iter != nullptr) {
        // if name matches return true
        if (iter->firstName == firstName && iter->lastName == lastName) {
            return true;
        }
        iter = iter->next;
    }
    // no name matches here
    return false;
}

bool BirthdayParty::checkGuestList(const std::string &firstName,
                                   const std::string &lastName, BirthdayType &value) const {
    // loop through every name
    Node* iter = head;
    while (iter != nullptr) {
        // if name matches then update value in parameter
        if (iter->firstName == firstName && iter->lastName == lastName) {
            value = iter->value;
            return true;
        }
        iter = iter->next;
    }
    // no name matches here
    return false;
}

bool BirthdayParty::selectInvitee(int i, std::string &firstName,
                                  std::string &lastName, BirthdayType &value) const {
    // check if i is in bounds first
    if (i < 0 || i >= whosOnTheGuestList()) {
        return false;
    }
    // loop through counter and iter to find the correct pointer iter
    Node* iter = head;
    int counter = 0;
    while (iter != nullptr) {
        if (counter == i) {
            break;
        }
        iter = iter->next;
        counter++;
    }
    // here, iter will be pointing to the correct index (hopefully)
    // copy over values yay
    firstName = iter->firstName;
    lastName = iter->lastName;
    value = iter->value;
    return true;
}

void BirthdayParty::changeGuestList(BirthdayParty &other) {
    // swap head pointers
    Node* temp = other.head;
    other.head = head;
    head = temp;
    
    // automatically destructs other after this exits
    return;
}

bool combineGuestLists(const BirthdayParty & bpOne, const BirthdayParty & bpTwo,
                       BirthdayParty & bpJoined) {
    BirthdayParty temp;
    // set bpJoined to any linkedlist (we use bpOne)
    temp = bpOne;
    // flag to check if there is any conflicting info
    bool flag = true;
    
    for (int i = 0; i < bpTwo.whosOnTheGuestList(); i++) {
        std::string first;
        std::string last;
        BirthdayType val;
        bpTwo.selectInvitee(i, first, last, val);
        
        BirthdayType og_val;
        // check if this person exists in bpJoined
        if (temp.checkGuestList(first, last, og_val)) {
            // check if vals are different
            if (og_val != val) {
                // remove the person and set return value to false
                temp.dropFromGuestList(first, last);
                flag = false;
            }
            // otherwise do nothing. person is already in bpJoined and values match
        }
        else {
            // that person does not exist in bpJoined so add her
            temp.addInvitee(first, last, val);
        }
    }
    // to prevent aliasing
    bpJoined = temp;
    return flag;
    
}

void verifyGuestList (const std::string& fsearch, const std::string& lsearch,
                      const BirthdayParty& bpOne, BirthdayParty& bpResult) {
    // set a temp var to prevent aliasing
    BirthdayParty temp;
    
    // update tmpe
    for (int i = 0; i < bpOne.whosOnTheGuestList(); i++) {
        // get every person from bpOne
        std::string first;
        std::string last;
        BirthdayType val;
        bpOne.selectInvitee(i, first, last, val);
        
        // check if any person has to be added
        if ((fsearch == first || fsearch == "*") && (lsearch == last || lsearch == "*")) {
            temp.addInvitee(first, last, val);
        }
    }
    
    // set result to temp (prevents aliasing)
    // memory leak prevented by destructor in =operator->changeGuestList
    bpResult = temp;
    return;
}

//
//  WordTree.h
//  CS32HW4
//
//  Created by Nevin Liang on 8/16/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#ifndef WordTree_h
#define WordTree_h

#include <stdio.h>
#include <iostream>
#include <string>

typedef std::string WordType;
struct WordNode {
    // three data members in WordNode for a tree
    WordType m_data;
    WordNode *m_left;
    WordNode *m_right;
    // You may add additional data members and member functions
    // in WordNode
    // m_count describes number of occurences in that tree
    int m_count;
};

class WordTree {
    
private:
    // root node of tree
    WordNode *root;
    
    // helper function
    
    // Name: ccTrav
    // Input: root1 and root2 of type WordNode*
    // Output: --
    // Description: recursive helper for copy constructor
    void ccTrav(WordNode* root1, WordNode* root2);
    
    // Name: outTrav
    // Input: root WordNode pointer, and ostream out
    // Output: --
    // recursive helper for print overloaded op
    void outTrav(WordNode* root, std::ostream &out) const;
    
    // Name: insertTrav
    // Input: root WordNote pointer and val Type
    // Output: WordNode pointer
    // recursive helper for add
    WordNode* insertTrav(WordNode* root, WordType val);
    
    // Name: createNode
    // Input: val which is of WordType
    // Output: WordNode pointer
    // essentially a constructor for a WordNode
    WordNode* createNode(WordType val);
    
    // Name: distinctHelp
    // Input: root wordnode pointer
    // Output: integer number of distinct words
    // recursive helper function for distinctWords
    int distinctHelp(WordNode* root) const;
    
    // Name: totalHelp
    // Input: root is of wordnode pointer type
    // Output: integer number of total words
    // Description: helper function for totalWords
    int totalHelp(WordNode* root) const;
    
    // Name: delHelp
    // Input: root WordNode pointer
    // Output: --
    // Description: helper function for destructor
    void delHelp(WordNode* root);
    
    
public:
    // Name: WordTree
    // Input: --
    // Output: --
    // Description: default constructor
    WordTree() : root(nullptr) { };
    
    // Name: WordTree
    // Input: rhs WordTree reference
    // Output: --
    // copy constructor
    WordTree(const WordTree& rhs);
    
    // Name: =
    // Input: rhs WordTree reference
    // Output: WordTree reference
    // Description: assignment operator
    const WordTree& operator=(const WordTree& rhs);
    
    // Name: add
    // Input: WordType v
    // Output: --
    // Descrition: Inserts v into the WordTree
    void add(WordType v);
    
    // Name: distinctWords
    // Input: --
    // Output: int number of distinct words
    // Description: Returns the number of distinct words / nodes
    int distinctWords() const;
    
    // Name: totalWords
    // Input: --
    // Output: integer number of total words
    // Descripton: total number of words including duplicate values
    int totalWords() const;
    
    // Name: <<
    // Input: ostream type and WordTree reference
    // Output: overloaded operator
    // Description: Prints the LinkedList
    friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);
    
    // Name: ~WordTree
    // Input: --
    // Output: --
    // Description: Destroys all the dynamically allocated memory in the // tree
    ~WordTree();
};

#endif /* WordTree_h */

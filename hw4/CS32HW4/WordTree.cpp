//
//  WordTree.cpp
//  CS32HW4
//
//  Created by Nevin Liang on 8/16/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include "WordTree.h"

WordNode* WordTree::createNode(WordType val) {
    // essentially what a constructor of WordNode would do
    WordNode* node = new WordNode;
    node->m_data = val;
    node->m_count = 1;
    
    // has to init to nullptr bc c++ doesnt auto init
    node->m_left = node->m_right = nullptr;
    // returns address of WordNode aka pointer
    return node;
}

WordTree::WordTree(const WordTree &rhs) {
    // check for nullptr
    if (rhs.root == nullptr) {
        root = nullptr;
    }
    // if not, recursively create the tree
    else {
        // pass in root's data to create it
        root = createNode(rhs.root->m_data);
        // with count
        root->m_count = rhs.root->m_count;
        // then recursively create the tree
        ccTrav(root, rhs.root);
    }
}

void WordTree::ccTrav(WordNode *root1, WordNode *root2) {
    // go left if able to
    if (root2->m_left != nullptr) {
        // copy the node from rhs
        root1->m_left = createNode(root2->m_left->m_data);
        root1->m_left->m_count = root2->m_left->m_count;
        // keep going left
        ccTrav(root1->m_left, root2->m_left);
    }
    // go right if able to
    if (root2->m_right != nullptr) {
        // copy node from rhs
        root1->m_right = createNode(root2->m_right->m_data);
        root1->m_right->m_count = root2->m_right->m_count;
        // keep going right
        ccTrav(root1->m_right, root2->m_right);
    }
}

const WordTree &WordTree::operator=(const WordTree &rhs) {
    // if not an alias
    if (&rhs != this) {
        // destruct then copy construct
        delHelp(root);
        ccTrav(root, rhs.root);
    }
    return *this;
}

void WordTree::add(WordType v) {
    // immediately call recursive version
    root = insertTrav(root, v);
}

WordNode* WordTree::insertTrav(WordNode *root, WordType val) {
    // if root is null then just create a node with that value here and leave
    if (root == nullptr) {
        return createNode(val);
    }
    // otherwise go left increment or right
    if (val < root->m_data) {
        // insert to left branch
        root->m_left = insertTrav(root->m_left, val);
    }
    else if (val == root->m_data) {
        // found it! increment and just leave
        root->m_count++;
    }
    else {
        // insert to right branch
        root->m_right = insertTrav(root->m_right, val);
    }
    return root;
}

int WordTree::distinctWords() const {
    // immediately call recursive version
    return distinctHelp(root);
}

int WordTree::distinctHelp(WordNode *root) const {
    // same as print function except instead of print we increment total
    int total = 0;
    if (root != nullptr) {
        total += distinctHelp(root->m_left);
        // increment total for itself right here
        total += 1;
        total += distinctHelp(root->m_right);
    }
    return total;
}

int WordTree::totalWords() const {
    // immediately call recursive version
    return totalHelp(root);
}

int WordTree::totalHelp(WordNode *root) const {
    // same as print function except instead of printing we increment total
    int total = 0;
    if (root != nullptr) {
        total += totalHelp(root->m_left);
        // increment total for current right here
        total += root->m_count;
        total += totalHelp(root->m_right);
    }
    return total;
}

WordTree::~WordTree() {
    // immediately call recursive counterpart :)
    delHelp(root);
}

void WordTree::delHelp(WordNode *root) {
    // if root is null then immediately return
    if (root == nullptr) {
        return;
    }
    // otherwise delete left branch and right (postorder)
    delHelp(root->m_left);
    delHelp(root->m_right);
    delete root;
}

std::ostream& operator<<(std::ostream &out, const WordTree& rhs) {
    // immediately call recursive counterpart. is there a pattern?
    rhs.outTrav(rhs.root, out);
    return out;
}

void WordTree::outTrav(WordNode* root, std::ostream &out) const {
    // loop through in inorder and print out in the middle if root isnt null
    if (root != nullptr) {
        outTrav(root->m_left, out);
        // print out data for the root right here
        out << root->m_data << " " << root->m_count << std::endl;
        outTrav(root->m_right, out);
    }
}



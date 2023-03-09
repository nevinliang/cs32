//
//  main.cpp
//  CS32Proj3
//
//  Created by Nevin Liang on 7/28/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <cassert>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

// Name: createDictCounter
// Input: dictionary file istream value, dictionary array reference, elements #
// Output: final number of elements in the dictionary array
// Description: recurses thru the entire dictionary and adds things to dict[]
int createDictCounter(istream &dictfile, string dict[], int elements) {
    // while the number of elements is less than the maximum allowed
    if (elements < MAXDICTWORDS) {
        // read in the line and input it into dict
        string line;
        if (getline(dictfile, line)) {
            dict[elements++] = line;
            // update counter of number of elements
            return 1 + createDictCounter(dictfile, dict, elements);
        }
    }
    return 0;
}

// Name: createDict
// Input: istream dictionary file, and dict array reference
// Output: final number of elements in the dictionary array
// Description: see description for createDictCounter
int createDict(istream &dictfile, string dict[]) {
    // used a counter to create dictionary so called that recursive function
    // createDictCounter returns the number of elements in dict at the end
    return createDictCounter(dictfile, dict, 0);
}

// function definition so that loop can call it
int getPermutations(const string dict[], string prefix, string rest, int count, int dictsize, string results[]);

// Name: loop
// Input: wow ok get ready...integer i counter for loop, max integer for loop boundary, string rest for
// recursive call back to getPermutation, prefix as well, count for number of elements in results so far
// dict const string which was initialized in createDict function as well as resulting string array
// Output: integer updated count
// Description: is the loop that appears in getPermutation to loop from characters 0 thru rest.length
int loop(int i, int max, string prefix, string rest, int count, const string dict[], int dictsize, string results[]) {
    // does the main loop inside the getPermutation function
    // loop details taken from FAQ from Professor Ambrosio
    // end of loop reached
    if (i >= max)
        return count;
    // changed strings
    string nprefix = prefix, nrest = rest;
    // change the new prefix value
    nprefix += rest[i];
    // 3 cases for removing the ith character
    if (i == 0)
        nrest = rest.substr(1);
    else if (i == rest.length() - 1)
        nrest = rest.substr(0, rest.length() - 1);
    else
        nrest = rest.substr(0, i) + rest.substr(i + 1);
    // call get Permutations for these new values
    count = getPermutations(dict, nprefix, nrest, count, dictsize, results);
    // loop recursive statement
    return loop(i + 1, max, prefix, rest, count, dict, dictsize, results);
}

// Name: notIn
// Input: string s, array reference, and size value for array
// Output: boolean
// Description: whether s is in the array or not
bool notIn(string s, const string dict[], int size) {
    // if size is less than 0, then the string s is definitely not in dict
    if (size < 0)
        return true;
    // otherwise, check if s is equal to the last element
    if (s == dict[size - 1])
        return false;
    // if it doesn't, then decrease the size of the dictionary by 1
    return notIn(s, dict, size - 1);
}

// Name: getPermutations
// Input: constant reference to dictionary, prefix, rest, and count of results, results array
// and dictionarysize integer
// Output: integer count of number of results found
// Description: runs through permutations of all words (input prefix) and check if matches in dictionary
// if yes, then store in results and update count which is later returned
int getPermutations(const string dict[], string prefix, string rest,
                    int count, int dictsize, string results[]) {
    // gist taken from psuedocode given in Project 3 FAQ from Professor Ambrosio
    if (rest == "") {
        // if the remaining string is empty then we have reached the end of the recursion
        // check if the prefix is inside the dictionary as well if it's a repeat in the results array
        if (!notIn(prefix, dict, dictsize) && notIn(prefix, results, count))
            if (count < MAXRESULTS)
                results[count++] = prefix;
        // incrememt count, which holds #1 the place to put it as well as #2 how many there are
    }
    // otherwise, loop from the 0th to length - 1th character of rest with the current parameters
    else count = loop(0, (int)rest.length(), prefix, rest, count, dict, dictsize, results);
    // loop should return a count which is the updated count of all deeper recursions
    return count;
}

// Name: characterMixer
// Input: special word string, dictionary, size of dictionary, and results array of all anagrams in dict
// Output: number of anagrams of word found in dictionary
// Description: takes a word, finds all anagrams, then finds all anagrams that are real words in the
// dictionary, then stores the values in results and returns the total number of words in results
int characterMixer(string word, const string dict[], int size, string results[]) {
    // getPermutations returns the number of good dictionary anagrams and also modifies results
    return getPermutations(dict, "", word, 0, size, results);
}

// Name: viewLoop
// Input: integer i and max for loop boundaries, as well as results array reference
// Output: ----
// Description: loops through all values in results and prints them out using recursion :)
void viewLoop(int i, int max, const string results[]) {
    // standard for loop taken from Professor Ambrosio's FAQ page
    // recurse until i reaches the maximum limit then return
    if (i >= max) return;
    // body of the "loop" printing out results
    cout << "Matching word " << results[i] << endl;
    // the "increment counter" part of the loop
    viewLoop(i + 1, max, results);
}

// Name: viewAnswers
// Input: results array string
// Output: ----
// Description: "loops" through entire results array and prints everything out
void viewAnswers(const string results[], int size) {
    // loop from 0 to size printing out everything in results
    viewLoop(0, size, results);
}

int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return 0;
    }
    
    nwords = createDict(dictfile, dict);

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = characterMixer(word, dict, nwords, results);
    
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        viewAnswers(results, numMatches);

    return 0;
}

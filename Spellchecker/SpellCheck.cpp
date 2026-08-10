/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: Spell Checker
** File: 	SpellCheck.cpp
** Description: Checks spelling of all words in a file against a dictionary.
**
** Author: 	Clayton LaChance
** Date: 	8/10/2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool isInDictionary(const vector<string>& words, const string& word)
{
    return find(words.begin(), words.end(), word) != words.end();
}

int main()
{
    vector<string> words;
    string word;
    string filename;

    // Open the dictionary file.
    ifstream dictFile("Spellchecker/words");
    if (!dictFile)
    {
        cout << "Error: Could not open dictionary file 'words'." << endl;
        return 1;
    }

    // For each word in the dictionary file, append the word to the words vector.
    while (dictFile >> word)
    {
        words.push_back(word);
    }
    dictFile.close();

    cout << "Loaded " << words.size() << " dictionary words." << endl;
    cout << "Enter the name of the file to check: ";
    cin >> filename;

    // Open the file to be checked.
    ifstream checkFile(filename);
    if (!checkFile)
    {
        cout << "Error: Could not open file '" << filename << "'." << endl;
        return 1;
    }

    cout << "Misspelled words:" << endl;

    // For each word in that file, if not in words vector, print the word.
    while (checkFile >> word)
    {
        if (!isInDictionary(words, word))
        {
            cout << word << endl;
        }
    }

    checkFile.close();
    return 0;
}

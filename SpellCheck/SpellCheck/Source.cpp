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
#include <windows.h>
#include <commdlg.h>

using namespace std;

bool isInDictionary(const vector<string>& words, const string& word)
{
    return find(words.begin(), words.end(), word) != words.end();
}
//Create string to open file explorer and input path
string openFileDialog()
{
    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = L"Text Files\0*.txt\0All Files\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = L"txt";

    if (GetOpenFileNameW(&ofn))
    {
        // Convert wchar_t* to string
        wstring ws(fileName);
        return std::string(ws.begin(), ws.end());
    }
    else
    {
        return "";
    }
}
int main()
{
    vector<string> words;
    string word;
    string filename;

    // Open the dictionary file.
    ifstream dictFile("words");
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

    int decision;
    cout << "Loaded " << words.size() << " dictionary words." << endl;
    cout << "Enter 1 to input file path manually\nEnter 2 to open file explorer (windows only)\nEnter: ";
    cin >> decision ;
    
    //Enter File name Option
    if (decision == 1) {
        cout << "Enter full path to file, can copy path\nThis program will clean it up\nEnter:";
        cin >> filename;
        //Trying to make it so you can copy and paste path
        // Remove surrounding quotes if present
        if (!filename.empty() && filename.front() == '"' && filename.back() == '"') {
            filename = filename.substr(1, filename.size() - 2);
        }

        // Replace backslashes with forward slashes, depending on OS etc, forward slashes just work best
        for (char& c : filename) {
            if (c == '\\') c = '/';
        }

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
    

    //File Explorer Option
    else if (decision == 2) {
        //Opens file explorer
        string filename = openFileDialog();
        //opens file
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
    return 0;
}

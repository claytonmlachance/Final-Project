/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: Final Project
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

//Adding punctuation and capitalization stripping
string removePunctuation(const string& s) //punctuation
{
    string cleaned;
    for (char c : s)
    {
        if (isalnum(c))          // keep letters and numbers
            cleaned += c;
    }
    return cleaned;
}
string toLower(const string& s) //lowercase
{
    string lowered;
    for (char c : s)
        lowered += tolower(c);
    return lowered;
}
string normalize(const string& s) //one function to "normalize", combine both strings
{
    return toLower(removePunctuation(s));
}
//Normalize Dictionary
vector<string> loadDictionary(const string& filename)
{
    vector<string> words;
    ifstream dict(filename);

    string w;
    while (dict >> w)
        words.push_back(normalize(w));

    return words;
}
//Set up for searching the word file, if it returns true the word was found, if false its not found
//This is my 6th different version of this, hopefully it normalizes and runs
//Seems to run now

bool isInDictionary(const vector<string>& words, const string& word)
{
    string normalizedWord = normalize(word);
    return find(words.begin(), words.end(), normalizedWord) != words.end();
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
 //Intro
    cout << "Auto SpellChecker\nVersion 1.0\nCreated by: Clayton, James, and Samantha\n...\nThis program will spellcheck a selected PLAIN TEXT file against an included dictionary file.\n";
    cout << "It will normalize for capitalization and punctuation.\n...\n";
 //vars
    vector<string> words;
    string word;
    string filename;

 // Open the dictionary file.
    ifstream dictFile("words");
    //Error if can not find it
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
    
 //Prompt for choosing file explorer or input
    int decision;
    cout << "Loaded " << words.size() << " dictionary words.\n..." << endl;
    cout << "Enter 1 to input file path manually\nEnter 2 to open file explorer (windows only)\n...\nEnter: ";
    cin >> decision ;
    cout << "\n...";

 //Below are 2 different options the user is prompted to choose from.  1 requires entering Path 2 opens the file explorer.
    
    //Enter File name Option
    if (decision == 1) {
        cout << "Copy-Paste full file path\nThis program will clean it up\n...\nEnter:";
        cin >> filename ;
        //Trying to make it so you can copy and paste path, Remove surrounding quotes if present
        if (!filename.empty() && filename.front() == '"' && filename.back() == '"') {
            filename = filename.substr(1, filename.size() - 2);
        }

        // Replace backslashes with forward slashes, depending on OS etc, forward slashes just work best
        for (char& c : filename) {
            if (c == '\\') c = '/';
        }
        //Error for file not opening
        ifstream checkFile(filename);
        if (!checkFile)
        {
            cout << "Error: Could not open file '" << filename << "'." << endl;
            return 1;
        }
        // For each word in that file, if not in words vector, print the word.
        cout << "Misspelled words:" << endl;
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
        // For each word in that file, if not in words vector, print the word. 
        cout << "Misspelled words:" << endl;
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
}

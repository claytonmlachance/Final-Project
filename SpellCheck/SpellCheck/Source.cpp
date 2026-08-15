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

// adding punctuation and capitalization stripping
string removePunctuation(const string& s) // punctuation
{
    string cleaned;
    for (char c : s)
    {
        if (isalnum(c))          // keep letters and numbers
            cleaned += c;
    }
    return cleaned;
}
string toLower(const string& s) // lowercase
{
    string lowered;
    for (char c : s)
        lowered += tolower(c);
    return lowered;
}
string normalize(const string& s) // one function to "normalize", combine both strings
{
    return toLower(removePunctuation(s));
}
// normalize dictionary
vector<string> loadDictionary(const string& filename)
{
    vector<string> words;
    ifstream dict(filename);

    string w;
    while (dict >> w)
        words.push_back(normalize(w));

    return words;
}
// set up for searching the word file, if it returns true, the word was found, if false it was not found
// this is my 6th different version of this, hopefully it normalizes and runs
// seems to run now

bool isInDictionary(const vector<string>& words, const string& word)
{
    string normalizedWord = normalize(word);
    return find(words.begin(), words.end(), normalizedWord) != words.end();
}

// create string to open file explorer and input path
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
        // convert wchar_t* to string
        wstring ws(fileName);
        return string(ws.begin(), ws.end()); // removed std:: from std::string..., you can put it back if you want
    }
    else
    {
        return "";
    }
}

int main()
{
 // intro
    cout << "Auto SpellChecker\nVersion 1.0\nCreated by: Clayton, James, and Samantha\n...\nThis program will spellcheck a selected PLAIN TEXT file against an included dictionary file.\n";
    cout << "It will normalize for capitalization and punctuation.\n...\n";
 // vars
    vector<string> words;
    string word;
    string filename;

 // open the dictionary file.
    ifstream dictFile("words");
    // error if can not find it
    if (!dictFile)
    {
        cout << "Error: Could not open dictionary file 'words'." << endl;
        return 1;
    }

 // for each word in the dictionary file, append the word to the words vector.
    while (dictFile >> word)
    {
        words.push_back(word);
    }
    dictFile.close();
    
 // prompt for choosing file explorer or input
    int decision;
    cout << "Loaded " << words.size() << " dictionary words.\n..." << endl;
    cout << "Enter 1 to input file path manually\nEnter 2 to open file explorer (windows only)\n...\nEnter: ";
    cin >> decision ;
    cout << "\n...";

 // below are 2 different options the user is prompted to choose from.  1 requires entering Path 2 opens the file explorer.
    
    // enter file name option
    if (decision == 1) {
        cout << "Copy-Paste full file path\nThis program will clean it up\n...\nEnter:";
        cin >> filename ;
        // trying to make it so you can copy and paste path, remove surrounding quotes if present
        if (!filename.empty() && filename.front() == '"' && filename.back() == '"') {
            filename = filename.substr(1, filename.size() - 2);
        }

        // replace backslashes with forward slashes, depending on OS etc, forward slashes just work best
        for (char& c : filename) {
            if (c == '\\') c = '/';
        }
        // error for file not opening
        ifstream checkFile(filename);
        if (!checkFile)
        {
            cout << "Error: Could not open file '" << filename << "'." << endl;
            return 1;
        }
        // for each word in that file, if not in words vector, print the word.
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
    

    // file explorer option
    else if (decision == 2) {
        // opens file explorer
        string filename = openFileDialog();
        // opens file
        ifstream checkFile(filename);
        if (!checkFile)
        {
            cout << "Error: Could not open file '" << filename << "'." << endl;
            return 1;
        }
        // for each word in that file, if not in words vector, print the word. 
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

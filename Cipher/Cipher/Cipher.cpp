/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #5 P8.7
** File: 	crypt.cpp
** Description: Random monoalphabet cipher. The Caesar cipher, which shifts 
** all letters by a fixed amount, is far too easy to crack. Here is a better 
** idea. As the key, don’t use numbers but words. Suppose the key word is FEATHER. 
** Then first remove duplicate letters, yielding FEATHR, and append the other letters 
** of the alphabet in reverse order
**
** Author: 	James Domkus/Samantha Blissett/Clayton LaChance
** Date: 	8/14/2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>


using namespace std;

void buildCipher(string key, char cipher[]) {
    int cipherindex = 0; // reverse alphabet array
    char backwardAlph[] = { 'z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a' };

    for (int i = 0; i < key.length(); i++) { // step through each letter 
        if (!isalpha(key[i])) { // skip non-alphabetic characters 
            continue;
        }

        bool duplicate = false; // reset duplicate flag for each new letter 
        for (int j = 0; j < cipherindex; j++) { // then check if it is the same letter anywhere else in the word 
            if (tolower(key[i]) == cipher[j]) { 
                duplicate = true; // set duplicate flag 
                break;
                }
            }
        
                if (!duplicate && cipherindex < 26) { // build letter into cipher if not a duplicate letter 
                cipher[cipherindex] = tolower(key[i]);
                cipherindex++;
            }
                else {
                    duplicate = false; // reset duplicate flag before checking the next letter 
            }
         // fill the rest of the array with a backwards alphabet
        }    
    // fill the remaining slots using the backwards alphabet
    for (int alphacount = 0; alphacount < 26; alphacount++) {
        if (cipherindex >= 26) {
            break;
        }

        bool duplicate = false;
        for (int c = 0; c < cipherindex; c++) {
            if (backwardAlph[alphacount] == cipher[c]) {
                duplicate = true; 
                break;  // move on to the next letter
            }
        }

        if (!duplicate) {
            cipher[cipherindex] = backwardAlph[alphacount];
            cipherindex++;
        }
    }
}

void Encrypt(char alphabet[], char cipher[], ifstream& in, ofstream& out) {
    char ch;
    while (in.get(ch)) {
        bool foundit = false;
        bool upper = false;

        if (isupper(ch)) { // check if incoming char is an upper case letter 
            upper = true; // remember this should be an upper case letter 
            ch = tolower(ch); // set it to be lower case so it will match the arrays
        }

        for (int i = 0; i < 26; i++) {
            if (ch == alphabet[i]) { // look for match in the alphabet array
                // letter from input file matched in alphabet array
                if (upper) {
                    out.put(toupper(cipher[i])); // write the corresponding cipher letter to the output file as upper case 
                    upper = false; // reset upper case flag 
                }
                else {
                    out.put(cipher[i]); //write the corresponding cipher letter to the output file 
                }
                foundit = true;
                break; // leave the for loop and move on to the next char from the input file 
            }
        }

        if (!foundit) {
            out.put(ch); // if after searching the entire alphbet there was no match, right write that char to output file
        }

		else {
			foundit = false; // reset foundit flag for next char from the input file
		}
    }
}

void Decrypt(char alphabet[], char cipher[], ifstream& in, ofstream& out) {
    char ch;
    while (in.get(ch)) { // read a char from the input file
        bool foundit = false;
        bool upper = false;

        if (isupper(ch)) { // check if incoming char is an upper case letter
            upper = true; // remember this should be an upper case letter
            ch = tolower(ch); // set it to be lower case so it will match the arrays
        }

        for (int i = 0; i < 26; i++) {
            if (ch == cipher[i]) { // look for match in the cipher array
                if (upper) { // write the corresponding alphabet letter to the output file as upper case
                    out.put(toupper(alphabet[i])); // write the corresponding alphabet letter to the output file as upper case
                    upper = false; // reset upper case flag
                }
                else {
                    out.put(alphabet[i]); // write the corresponding alphabet letter to the output file
                }
                foundit = true;
                break; // leave the for loop and move on to the next char from the input file
            }
        }

        if (!foundit) { // if after searching the entire cipher there was no match, write that char to output file
            out.put(ch);
        }

        else {
            foundit = false; // reset foundit flag for next char from the input file
        }
    }
}

    int main(int argc, char* argv[]) {
    char cipher[26];
    char alphabet[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
    string keyword;
    ifstream in_file;
    ofstream out_file;
	bool encrypting = true; // default to encrypting
	int file_count = 0; // count of input and output files provided

    cout << "Ready to encrypt/decrypt your file.\n\n";

    for (int i = 1; i < argc; i++) { // process the command line arguments
        string arg = argv[i]; // argument being processed
        if (arg == "-d") { // decryption was selected
            encrypting = false;
        }
		else if (arg == "-e") { // encryption was selected
            encrypting = true;
        }
		else if (arg.substr(0, 2) == "-k") { // keyword from command line
            keyword = arg.substr(2);
        }
        else { // it is a file name
            file_count++;
            if (file_count == 1) { // the first file name
                in_file.open(arg);
				if (in_file.fail()) { // exit the program if opening failed
                    cout << "Error opening input file " << arg << endl;
                    return 1;
                }
            }
			else if (file_count == 2) { // the second file name
                out_file.open(arg);
                if (out_file.fail()) {
                    cout << "Error opening output file " << arg << endl;
                    return 1;
                }
            }
        }
    }

	if (file_count != 2) { // exit if the user didn’t specify two files
        cout << "Usage: " << argv[0] << " [-d] or [-e] -k[keyword] infile outfile" << endl;
        return 1;
    }

    if (keyword == "") { // make sure they entered a keyword to use
        cout << "Be sure to enter a keyword using -k" << endl;
        return 1;
    }

	buildCipher(keyword, cipher); // build the cipher with the supplied keyword
    cout << "Keyword selected: " << keyword << endl;

    if (encrypting) {
        cout << "Encrypting file\n\n";
		Encrypt(alphabet, cipher, in_file, out_file); // encrypt the input file to the output file
    }
    else {
        cout << "Decrypting file\n\n";
		Decrypt(alphabet, cipher, in_file, out_file); // decrypt the input file to the output file
    }

    cout << "Process Complete.\n";
    return 0;
}
/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #5 P8.7
** File: 	crypt.cpp
** Description: Ask for user to input a full phone number as a string,
				then concatenate parts of that string to output that same phone number properly formatted
**
** Author: 	James Domkus
** Date: 	8/10/2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <string>

using namespace std;

void buildCipher(string key, char cipher[]) {
	
	int cipherindex = 0;
	bool duplicate = false;
	char backwardAlph[] =
	{ 'z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a' };

	for (int i = 0;i < key.length();i++) { //step through each letter
		for (int j = 0;j < i;j++) { //then check if it is the same letter anywhere else in the word
			if (key[i] == key[j]) {
				if (i != j) { //make sure we didn't find the same letter
					//duplicate letter, don't add to cipher
					duplicate = true; //set duplicate flag 
				}
			}
		}

		if (!duplicate) {
			//build letter into cipher if not a duplicate letter
			cipher[cipherindex] = key[i];
			cipherindex++;

		}
		else {
			duplicate = false; //reset duplicate flag before checking the next letter
		}

	}

	//fill the rest of the array with a backwards alphabet
	int remainingletters = 26 - cipherindex;
	for (int k=0;k < remainingletters;k++) {
		cipher[cipherindex] = backwardAlph[k];
		cipherindex++;
	}
		
}

int main() {

	char cipher[26];
	char alphabet[] =
	{ 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string keyword;

	cin >> keyword;//replace with command line arguments

	buildCipher(keyword, cipher);

	//for (int g=0;g < 26;g++) {
	//	cout << cipher[g];
	//}


}


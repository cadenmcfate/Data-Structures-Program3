//program3cosc2_McFate.cpp
//Spellchecks the contents of book.txt against the
//contents of dict.txt using a hash data structure
//Caden McFate
//Programming assignment 3
//COSC 2030
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "timer.h"
#include "hash.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

string cleanWord(string word);

int main(void) {
    Timer timer;
    int currentCompares;
	int validCompares = 0, invalidCompares = 0, uncheckedCount = 0, invalidWords = 0, validWords = 0;
    ifstream inFile;
    ofstream oFile;
    string buffer;
    myHash<string> hash;
    vector<string> mispelledVec;
    //storing the dictionary in a binary search tree
    inFile.open("dict.txt");
    while (inFile >> buffer) {
        buffer = cleanWord(buffer);
        if (buffer.length() == 0) { continue; }
        //cout << "attempting insert: " << buffer << endl;
        hash.insert(buffer);
    }
    inFile.close();
    timer.Start();
    inFile.open("book.txt");
    while (inFile >> buffer) {
        buffer = cleanWord(buffer);
        if (buffer.length()==0) {continue;}
        else if (!isalpha(buffer[0])) {uncheckedCount++; continue;}
        currentCompares = hash.find(buffer);
        if (currentCompares > 0) { validWords++; validCompares += currentCompares; }
        else { invalidWords++; invalidCompares += currentCompares; mispelledVec.push_back(buffer); }
    }
    invalidCompares *= -1;
    timer.Stop();
    oFile.open("mispelled.txt");
    for (int i = 0; i < mispelledVec.size(); i++) {
        oFile << mispelledVec[i] << endl;
    }
    oFile.close();
    cout << "dictionary size " << hash.getSize() << endl;
    cout << "Done checking and these are the results" << endl;
	cout << "finished in time: " << timer.Time() << endl;
    cout << "finished in Milliseconds Time: " << timer.Time()*1000 << endl;
	cout << "There are " << validWords << " words found in the dictionary" << endl;
	cout << "\t " << validCompares << " compares. Average: " << validCompares/validWords << endl;
	cout << "There are " << invalidWords << " words NOT found in the dictionary" << endl;
	cout << "\t " << invalidCompares << " compares. Average: " << invalidCompares/invalidWords << endl;
	cout << "There are " << uncheckedCount << " words not checked." << endl;
	return 0;
}

string cleanWord(string word) {
	for (int i = 0; i < word.size(); i++) {
		if (isdigit(word[i]) || int(word[i]) == int('\'') || ((int(word[i]) >= int('a')) && (int(word[i]) <= int('z')))) {
			continue; //acceptable characters. digits, apostrophes, and lowercase letters.
		}
		else if (isupper(word[i])) {
			word[i] = tolower(word[i]); //uppercase to lowercase
			continue;
		}
		else {
			word.erase(i, 1); //remove the invalid character 
			i--;
		}
	}
	return word;
}
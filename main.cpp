// Playfair cipher decoder by Jacob Weber
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

string promptInput() {
    string inputData;
    cout<<"Type the Playfair cipher or provide the cipher's filename: ";
    getline(std::cin,inputData);
    namespace fs = filesystem;
    string path = ".";
    for (const auto & entry : fs::directory_iterator(path)) {
        string filePath = entry.path();
        if (filePath.compare("./"+inputData) == 0) {
            cout << "Found file: " << inputData << endl;
            inputData = "";
            ifstream inputFile (filePath);
            string line;
            while (getline(inputFile,line)) {
                inputData += line;
            }
            inputFile.close();
        }
    }

    return inputData;
}

//Step 1 for playfair cipher:
//Remove all spaces
//Separate string into pairs of two (possibly put each pair in an array)
//Ask for key
//Construct table (how to represent in data for appropriate purposes? 2D array?)//

string promptKeyWord() {
    string keyWord;
    cout << "Enter the keyword of the cipher: ";
    getline(std::cin,keyWord);
    return keyWord;
}

string removeSpaces(string rawCipher) {
    // string removedChars = remove(rawCipher.begin(), rawCipher.end(), ' '), rawCipher.end().c_str();
    string cleansedCipher;
    int pos = 0;
    while (pos < rawCipher.size()) {
        if (rawCipher[pos] == ' ') {
            rawCipher[pos] = rawCipher[pos+1];
        } else {
            cleansedCipher += rawCipher[pos];
        }
        pos += 1;
    }
    return cleansedCipher;
}

vector<string> divideIntoTwos(string rawCipher) {
   vector<string> cipherPairs;
   int pos = 0;
   while (pos < rawCipher.length()) {
    cipherPairs.push_back(rawCipher.substr(pos, 2));
    pos+=2;
   }
   string cipherString = " ";
   for (const string& pair : cipherPairs) {
    cipherString += pair + " ";
   }
   return cipherPairs;
}

char generateMatrix(string cipherKey) {
    const int row = 5;
    const int col = 5;
    
    char matrix[row][col];
    
}

string decipherWithPlayFair(string cipher) {
    string cipherKey = promptKeyWord();
    cipher = removeSpaces(cipher);
    vector<string> cipherPairs = divideIntoTwos(cipher);
    


    return "";
}

//bonus: save original spacing to reapply at the end

int main() {
    string cipher = promptInput();
    string decryptedCipher = decipherWithPlayFair(cipher);
    // cout << cipher << endl;
    return 0;
}



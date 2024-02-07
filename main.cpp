// Playfair cipher decoder by Jacob Weber
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

enum PairData {
    SAMEROW = 0,
    SAMECOL = 1,
    NOTSHARED = -1
};

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

vector<string> divideIntoPairs(string rawCipher) {
    for (auto & c: rawCipher) c = toupper(c);
    if (rawCipher.length() % 2 == 1) {
        rawCipher += "Z";
    }
    vector<string> cipherPairs;
    int pos = 0;
    while (pos < rawCipher.length()) {
        cipherPairs.push_back(rawCipher.substr(pos, 2));
        pos+=2;
    }
    return cipherPairs;
}

void printPairs(string rawCipher) {
    for (auto & c: rawCipher) c = toupper(c);
    if (rawCipher.length() % 2 == 1) {
        rawCipher += 'Z';
    }
    string cipherString;
    int pos = 0;
    while (pos < rawCipher.length()) {
        cipherString += (rawCipher.substr(pos,2) + " ");
        pos+=2;
    }
    cout << cipherString << endl;
}

char** generateMatrix(string cipherKey) {
    for (auto & c: cipherKey) c = toupper(c);
    char alphabet = 'A';
    char** matrix = new char*[5];

    for (int i = 0; i < 5; ++i) {
        matrix[i] = new char[5];
    }

    replace(cipherKey.begin(), cipherKey.end(), 'J', 'I');
    string alphabetString = cipherKey;
    while (alphabet <= 'Z') {
        if (alphabet != 'J') {
            alphabetString += alphabet;
        }
        alphabet++;
    }

    string matrixString;
    for_each(alphabetString.begin(), alphabetString.end(), [&](char uniqueChar) {
        if (matrixString.find(uniqueChar) == string::npos) {
            matrixString += uniqueChar;
        }
    });

    int pos = 0;
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            matrix[i][j] = matrixString[pos];
            pos++;
        }
    }
    return matrix;
}

void deleteMatrix(char** matrix) {
    for (int i=0;i<5;i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(char** matrix) {
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

PairData comparePairContents(string pair, char** matrix) {
    for (int i=0;i<5;i++) {
        if (pair[0] == *matrix[i] && pair[1] == *matrix[i]) {

        }
    }
    return SAMEROW;
}

string decipherWithPlayFair(string cipher) {
    string cipherKey = promptKeyWord();
    cipher = removeSpaces(cipher);
    vector<string> cipherPairs = divideIntoPairs(cipher);
    char** keyMatrix = generateMatrix(cipherKey);
    
    
    for (int i=0;i<cipherPairs.size();i++) {
        if (comparePairContents(cipherPairs[i], keyMatrix) == SAMEROW) {

        }
    }

    printMatrix(keyMatrix);
    deleteMatrix(keyMatrix);
    printPairs(cipher);


    return "";
}

//bonus: save original spacing to reapply at the end

int main() {
    string cipher = promptInput();
    string decryptedCipher = decipherWithPlayFair(cipher);
    // cout << decryptedCipher << endl;
    return 0;
}



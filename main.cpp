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

string decryptPairContents(string pair, char** matrix) {
    

    //separate matrix into string arrays containing each row and column

    string colData[5];
    string rowData[5];
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            colData[i] += matrix[j][i];
            rowData[i] += matrix[i][j];
        }
    }

    /*
    check if: 
    1. any column contains the pair
    2. any row contains the pair
    3. neither contain the pair
    If pair is in a column or row, change char to neighbor above or left of it 
    If pair is in neither, find horizontal corner char in relation to pair pos
    Note:'pairPos'-1 won't work; inverted with +4 modulus 5  
    */
    int pair0Pos;
    int pair1Pos;



    for (int i=0;i<5;i++) {
       pair0Pos = colData[i].find(pair[0]);
       pair1Pos = colData[i].find(pair[1]);
       if (pair0Pos != string::npos && pair1Pos != string::npos) {
            pair[0] = colData[i][(pair0Pos+4)%5];
            pair[1] = colData[i][(pair1Pos+4)%5];
            return pair;
       }
    }



    for (int i=0;i<5;i++) {   
       pair0Pos = rowData[i].find(pair[0]);
       pair1Pos = rowData[i].find(pair[1]);
       if (pair0Pos != string::npos && pair1Pos != string::npos) {
            pair[0] = rowData[i][(pair0Pos+4)%5];
            pair[1] = rowData[i][(pair1Pos+4)%5];
            return pair;
       }
    }

    int pair0Col;
    int pair0Row;
    int pair1Col;
    int pair1Row;
    for (int i=0;i<5;i++) {   
        int pos = colData[i].find(pair[0]);
        if (pos != string::npos) {
            pair0Col = i;
            pair0Row = pos;
        }
        pos = colData[i].find(pair[1]);
        if (pos != string::npos) {
            pair1Col = i;
            pair1Row = pos;
        }
    }
    pair[0] = matrix[pair0Row][pair1Col];
    pair[1] = matrix[pair1Row][pair0Col];
    
    return pair;
}

string decipherWithPlayFair(string cipher) {
    string cipherKey = promptKeyWord();
    cipher = removeSpaces(cipher);
    vector<string> cipherPairs = divideIntoPairs(cipher);
    char** keyMatrix = generateMatrix(cipherKey);
    
    string plaintext;
    for (int i=0;i<cipherPairs.size();i++) {
            plaintext += decryptPairContents(cipherPairs[i], keyMatrix);
        }
    cout << plaintext << endl;
    printMatrix(keyMatrix);
    deleteMatrix(keyMatrix);
    // printPairs(cipher);


    return "";
}

//bonus: save original spacing to reapply at the end

int main() {
    string cipher = promptInput();
    string decryptedCipher = decipherWithPlayFair(cipher);
    // cout << decryptedCipher << endl;
    return 0;
}
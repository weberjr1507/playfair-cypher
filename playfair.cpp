// Playfair Cipher Decryptor written by Jacob Weber
// Works Consulted: https://github.com/Abhiramborige/Crypto-systems/blob/master/playfair_decryption.py
// Github: https://github.com/weberjr1507/playfair-cypher
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;


// promptInput(): Returns the playfair ciphertext provided by the user; ciphertext can
//be provided by typing the text itself or the name of a file in the user's directory.
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


//promptKeyWord(): Returns key provided by the user.
string promptKeyWord() {
    string keyWord;
    cout << "Enter the keyword of the cipher: ";
    getline(std::cin,keyWord);
    return keyWord;
}


//formatCipher(string): Returns a formatted version of the user's ciphertext; removes
//spaces and formats all characters to uppercase.
string formatCipher(string rawCipher) {
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
    for (auto & c: cleansedCipher) c = toupper(c);
    return cleansedCipher;
}


//divideIntoPairs(string): Returns a string array containing the ciphertext; puts every
//two characters into an index of the array.
vector<string> divideIntoPairs(string rawCipher) {
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


//printPairs(string): Prints the pair sequence of the ciphertext; used primarily
//for debug purposes.
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


//generateMatrix(string): Returns 2D char array containing the polybius square made
//from the users key.
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


//deleteMatrix(char**): Deletes the matrix to ensure no memory leaking.
void deleteMatrix(char** matrix) {
    for (int i=0;i<5;i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


//printMatrix(char**): Prints the matrix for debug purposes.
void printMatrix(char** matrix) {
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


//decryptPairContents(string, char**): Returns the inputted pair as its decrypted
//equivalent; utilizes the Polybius square and Playfair's three transposition rules.
string decryptPairContents(string pair, char** matrix) {

    string colData[5];
    string rowData[5];
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
            colData[i] += matrix[j][i];
            rowData[i] += matrix[i][j];
        }
    }

    int pair0Pos;
    int pair1Pos;
    
    //Rule 1: If the pair share a column, shift each letter up by one in the
    //square (-1 is not functional for indexes of 0; inverted to +4 mod 5).
    for (int i=0;i<5;i++) {
       pair0Pos = colData[i].find(pair[0]);
       pair1Pos = colData[i].find(pair[1]);
       if (pair0Pos != string::npos && pair1Pos != string::npos) {
            pair[0] = colData[i][(pair0Pos+4)%5];
            pair[1] = colData[i][(pair1Pos+4)%5];
            return pair;
       }
    }

    //Rule 2: If the pair share a row, shift each letter left by one in the
    //square (-1 is not functional for indexes of 0; inverted to +4 mod 5).
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
    
    //Rule 3: If the pair do not share a row or column, change each character
    //to the one that share's its row but its *pairing's* column. 
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


//decipherWithPlayfair(string): Returns plaintext calculated using the Playfair cipher; acts
//as the Playfair master function.
string decipherWithPlayFair(string cipher) {
    string cipherKey = promptKeyWord();
    string parsedCipher = formatCipher(cipher);
    vector<string> cipherPairs = divideIntoPairs(parsedCipher);
    char** keyMatrix = generateMatrix(cipherKey);
    
    string plaintext;
    for (int i=0;i<cipherPairs.size();i++) {
            plaintext += decryptPairContents(cipherPairs[i], keyMatrix);
        }
    deleteMatrix(keyMatrix);

    return plaintext;
}


//printPlainText(string): prints the plaintext from a decrypted message.
void printPlaintext(string plaintext) {
    cout << "Decrypted Message: " << plaintext << endl;
}

int main() {
    string cipher = promptInput();
    string decryptedCipher = decipherWithPlayFair(cipher);
    printPlaintext(decryptedCipher);
    return 0;
}
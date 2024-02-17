#ifndef PLAYFAIR_H
#define PLAYFAIR_H


#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

string formatCipher(string rawCipher);
vector<string> divideIntoPairs(string rawCipher);
void printPairs(string rawCipher);
char** generateMatrix(string cipherKey);
void deleteMatrix(char** matrix);
void printMatrix(char** matrix);
string decryptPairContents(string pair, char** matrix);

#endif
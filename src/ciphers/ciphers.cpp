#include "../prompts/prompts.hpp"
#include "playfair/playfair.hpp"
#include "ciphers.hpp"

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
    printMatrix(keyMatrix);
    deleteMatrix(keyMatrix);

    return plaintext;
}
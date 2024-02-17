#include "../prompts/prompts.hpp"
#include "../ciphers/playfair/playfair.hpp"
#include "../ciphers/ciphers.hpp"
#include <iostream>
using namespace std;


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
#include "prompts.hpp"


// promptInput(): Returns the playfair ciphertext provided by the user; ciphertext can
//be provided by typing the text itself or the name of a file in the user's directory.
string promptInput() {
    string inputData;
    cout<<"Type the cipher or provide the cipher's filename: ";
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
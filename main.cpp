// Playfair cipher decoder by Jacob Weber
#include <filesystem>
#include <fstream>
#include <iostream>
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
//Construct table (how to represent in data for appropriate purposes? 2D array?)
//


//bonus: save original spacing to reapply at the end

int main() {
    string cipher = promptInput();
    cout << cipher << endl; 
    return 0;
}



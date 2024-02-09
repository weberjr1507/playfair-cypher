# Playfair Cipher Decryptor 
Written by Jacob Weber
## Github: https://github.com/weberjr1507/playfair-cypher
## Works Consulted: 
- https://github.com/Abhiramborige/Crypto-systems/blob/master/playfair_decryption.py
- https://www.geeksforgeeks.org/playfair-cipher-with-examples/

# How To Run:

Compiled binaries are provided in the `bin/` directory.

- Windows: Run `bin/decipher.exe` or run `decipher.exe` from File Explorer
- Linux: Run `bin/decipher`

## Compiling

The source code, `src/playfair.cpp`, requires the GNU C++ Compiler to create a binary file.

- Windows: Download [MinGW](https://nuwen.net/mingw.html). Ensure it contains GCC 13+. Extract file and add `MinGW/bin` path to **Control Panel > Advanced System Setting > Environment Variable > Edit path from System variable**. Go to repository directory and run: 
```
g++ -o decipher.exe src/playfair-win.cpp
```

- Linux: Most often GCC comes preinstalled. If you don't have it, you can install GCC using your distro's respective package manager (apt,dnf,snap,flatpak,pacman,etc.). Otherwise, install from source: https://gcc.gnu.org/install/. Go to repository directory and run:
```
g++ -o decipher src/playfair.cpp
```
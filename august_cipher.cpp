#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to generate the August tableau
vector<vector<char>> generateTableau() {
    vector<vector<char>> tableau(26, vector<char>(26));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            tableau[i][j] = 'A' + ((j + i * i) % 26);
        }
    }
    return tableau;
}

string encrypt(string text, string key) {
    vector<vector<char>> tableau = generateTableau();
    string result = "";
    int keyLen = key.length();
    
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]);
            char k = toupper(key[i % keyLen]);
            int row = k - 'A';
            int col = c - 'A';
    
            char encrypted = tableau[row][col];
            
            result += (isupper(text[i])) ? encrypted : tolower(encrypted);
        } else {
            result += text[i];
        }
    }
    return result;
}

string decrypt(string text, string key) {
    vector<vector<char>> tableau = generateTableau();
    string result = "";
    int keyLen = key.length();
    
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]);
            char k = toupper(key[i % keyLen]);
            int row = k - 'A';

            int col = 0;
            for (int j = 0; j < 26; j++) {
                if (tableau[row][j] == c) {
                    col = j;
                    break;
                }
            }
            
            char decrypted = 'A' + col;

            result += (isupper(text[i])) ? decrypted : tolower(decrypted);
        } else {
            result += text[i];
        }
    }
    return result;
}

int main() {
    string text, key;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter key: ";
    getline(cin, key);
    
    string encrypted = encrypt(text, key);
    string decrypted = decrypt(encrypted, key);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}

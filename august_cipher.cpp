#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to generate the August tableau (similar to Vigenère but with shift based on position)
vector<vector<char>> generateTableau() {
    vector<vector<char>> tableau(26, vector<char>(26));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            // Each row is shifted by position value
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
            
            // Use the tableau for encryption
            char encrypted = tableau[row][col];
            
            // Preserve original case
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
            
            // Find the column in the tableau that gives us our encrypted character
            int col = 0;
            for (int j = 0; j < 26; j++) {
                if (tableau[row][j] == c) {
                    col = j;
                    break;
                }
            }
            
            // Convert column back to original character
            char decrypted = 'A' + col;
            
            // Preserve original case
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
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encrypt(string text, int rails) {
    vector<string> fence(rails);
    int rail = 0;
    bool down = true;
    
    // Build the rail fence pattern
    for (char c : text) {
        fence[rail] += c;
        
        if (down) {
            rail++;
            if (rail == rails) {
                rail = rails - 2;
                down = false;
            }
        }
        else {
            rail--;
            if (rail == -1) {
                rail = 1;
                down = true;
            }
        }
    }
    
    // Combine all rails
    string result;
    for (const string& s : fence) {
        result += s;
    }
    
    return result;
}

string decrypt(string text, int rails) {
    vector<vector<char>> fence(rails, vector<char>(text.length(), ' '));
    vector<int> counts(rails, 0);
    int rail = 0;
    bool down = true;
    
    // Mark positions in the fence
    for (int i = 0; i < text.length(); i++) {
        counts[rail]++;
        
        if (down) {
            rail++;
            if (rail == rails) {
                rail = rails - 2;
                down = false;
            }
        }
        else {
            rail--;
            if (rail == -1) {
                rail = 1;
                down = true;
            }
        }
    }
    
    // Fill the fence with text
    int pos = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < counts[i]; j++) {
            fence[i][j] = text[pos++];
        }
    }
    
    // Read off the fence pattern
    string result;
    rail = 0;
    down = true;
    vector<int> indices(rails, 0);
    
    for (int i = 0; i < text.length(); i++) {
        result += fence[rail][indices[rail]++];
        
        if (down) {
            rail++;
            if (rail == rails) {
                rail = rails - 2;
                down = false;
            }
        }
        else {
            rail--;
            if (rail == -1) {
                rail = 1;
                down = true;
            }
        }
    }
    
    return result;
}

int main() {
    string text;
    int rails;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter number of rails: ";
    cin >> rails;
    
    string encrypted = encrypt(text, rails);
    string decrypted = decrypt(encrypted, rails);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}
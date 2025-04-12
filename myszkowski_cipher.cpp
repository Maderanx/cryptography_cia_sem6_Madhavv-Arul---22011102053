#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <stdexcept>
using namespace std;

string preprocessText(const string& text) {
    string cleaned;
    for (char c : text) {
        if (isalpha(c)) {
            cleaned += toupper(c);
        }
    }
    if (cleaned.empty()) {
        throw runtime_error("Text must contain at least one letter!");
    }
    return cleaned;
}

string preprocessKey(const string& key) {
    string cleaned;
    for (char c : key) {
        if (isalpha(c)) {
            cleaned += toupper(c);
        }
    }
    if (cleaned.empty()) {
        throw runtime_error("Key must contain at least one letter!");
    }
    return cleaned;
}

vector<vector<char>> createGrid(const string& text, const string& key) {
    int cols = key.length();
    int rows = (text.length() + cols - 1) / cols;
    vector<vector<char>> grid(rows, vector<char>(cols, ' '));
    
    int k = 0;
    for (int i = 0; i < rows && k < text.length(); i++) {
        for (int j = 0; j < cols && k < text.length(); j++) {
            grid[i][j] = text[k++];
        }
    }
    return grid;
}

void printGrid(const vector<vector<char>>& grid, const string& key) {
    cout << "\nEncryption Grid:\n";
    cout << "  ";
    for (char k : key) {
        cout << k << " ";
    }
    cout << "\n  ";
    for (size_t i = 0; i < key.length(); i++) {
        cout << "- ";
    }
    cout << endl;
    
    for (size_t i = 0; i < grid.size(); i++) {
        cout << "| ";
        for (size_t j = 0; j < grid[i].size(); j++) {
            cout << (grid[i][j] == ' ' ? '_' : grid[i][j]) << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

string encrypt(string text, string key) {
    text = preprocessText(text);
    key = preprocessKey(key);
    
    vector<vector<char>> grid = createGrid(text, key);
    printGrid(grid, key); 
    
    int rows = grid.size();
    int cols = key.length();
    string result;
    
    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < key.length(); i++) {
        keyOrder.push_back({key[i], i});
    }
    sort(keyOrder.begin(), keyOrder.end());
    
    cout << "Reading order: ";
    for (const auto& k : keyOrder) {
        cout << k.first << " ";
        for (int row = 0; row < rows; row++) {
            if (grid[row][k.second] != ' ') {
                result += grid[row][k.second];
            }
        }
    }
    cout << endl;
    
    return result;
}

string decrypt(string text, string key) {
    text = preprocessText(text);
    key = preprocessKey(key);
    
    int cols = key.length();
    int rows = (text.length() + cols - 1) / cols;

    vector<pair<char, int>> keyOrder;
    for (int i = 0; i < key.length(); i++) {
        keyOrder.push_back({key[i], i});
    }
    sort(keyOrder.begin(), keyOrder.end());

    vector<int> colLengths(cols);
    int fullRows = text.length() / cols;
    int remainingChars = text.length() % cols;
    
    for (int i = 0; i < cols; i++) {
        colLengths[i] = fullRows;
        if (i < remainingChars) colLengths[i]++;
    }
    
    
    vector<int> positionMap(cols);
    for (int i = 0; i < cols; i++) {
        positionMap[keyOrder[i].second] = i;
    }
    
    vector<vector<char>> columns(cols);
    int pos = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < colLengths[i]; j++) {
            columns[keyOrder[i].second].push_back(text[pos++]);
        }
    }
    
    string result;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row < columns[col].size()) {
                result += columns[col][row];
            }
        }
    }
    
    return result;
}

int main() {
    string text, key;
    
    cout << "Enter text to encrypt (letters only): ";
    getline(cin, text);
    
    cout << "Enter key (letters only): ";
    getline(cin, key);
    
    try {
        string encrypted = encrypt(text, key);
        string decrypted = decrypt(encrypted, key);
        
        cout << "\nOriginal text:  " << text << endl;
        cout << "Preprocessed:   " << preprocessText(text) << endl;
        cout << "Key:           " << key << endl;
        cout << "Preprocessed:   " << preprocessKey(key) << endl;
        cout << "Encrypted text: " << encrypted << endl;
        cout << "Decrypted text: " << decrypted << endl;
    }
    catch (const runtime_error& e) {
        cout << "\nError: " << e.what() << endl;
        cout << "Please try again with valid input." << endl;
        return 1;
    }
    
    return 0;
}

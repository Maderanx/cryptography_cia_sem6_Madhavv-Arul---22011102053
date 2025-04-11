#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// Function to calculate determinant of 2x2 matrix
int determinant(const vector<vector<int>>& key) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    return det < 0 ? det + 26 : det;
}

// Function to calculate GCD
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular multiplicative inverse
int modInverse(int a, int m = 26) {
    a = ((a % m) + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;  // Return -1 if inverse doesn't exist
}

// Function to validate key matrix
bool isValidKey(const vector<vector<int>>& key) {
    // Check if all elements are within valid range
    for (const auto& row : key) {
        for (int val : row) {
            if (val < 0 || val >= 26) return false;
        }
    }
    
    // Check if determinant is valid (coprime with 26)
    int det = determinant(key);
    return gcd(det, 26) == 1;
}

// Function to get adjugate matrix
vector<vector<int>> adjugate(const vector<vector<int>>& key) {
    vector<vector<int>> adj(2, vector<int>(2));
    adj[0][0] = key[1][1];
    adj[1][1] = key[0][0];
    adj[0][1] = (-key[0][1] % 26 + 26) % 26;
    adj[1][0] = (-key[1][0] % 26 + 26) % 26;
    return adj;
}

string encrypt(string text, const vector<vector<int>>& key) {
    if (!isValidKey(key)) {
        throw runtime_error("Invalid key matrix! Determinant must be coprime with 26.");
    }
    
    // Remove non-alphabetic characters and convert to uppercase
    string cleaned;
    for (char c : text) {
        if (isalpha(c)) {
            cleaned += toupper(c);
        }
    }
    
    // Pad with 'X' if necessary
    if (cleaned.length() % 2 != 0) {
        cleaned += 'X';
    }
    
    string result;
    for (size_t i = 0; i < cleaned.length(); i += 2) {
        int p1 = cleaned[i] - 'A';
        int p2 = cleaned[i + 1] - 'A';
        
        int e1 = ((key[0][0] * p1 + key[0][1] * p2) % 26 + 26) % 26;
        int e2 = ((key[1][0] * p1 + key[1][1] * p2) % 26 + 26) % 26;
        
        result += char(e1 + 'A');
        result += char(e2 + 'A');
    }
    
    return result;
}

string decrypt(string text, const vector<vector<int>>& key) {
    if (!isValidKey(key)) {
        throw runtime_error("Invalid key matrix! Determinant must be coprime with 26.");
    }
    
    int det = determinant(key);
    int detInv = modInverse(det);
    
    if (detInv == -1) {
        throw runtime_error("Invalid key matrix! No modular multiplicative inverse exists.");
    }
    
    vector<vector<int>> adj = adjugate(key);
    vector<vector<int>> invKey(2, vector<int>(2));
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invKey[i][j] = (adj[i][j] * detInv % 26 + 26) % 26;
        }
    }
    
    return encrypt(text, invKey);
}

int main() {
    string text;
    vector<vector<int>> key(2, vector<int>(2));
    
    cout << "Enter text to encrypt (letters only): ";
    getline(cin, text);
    
    cout << "Enter 2x2 key matrix (4 numbers between 0-25):\n";
    cout << "Note: Determinant must be coprime with 26\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            while (true) {
                cin >> key[i][j];
                if (key[i][j] >= 0 && key[i][j] < 26) break;
                cout << "Please enter a number between 0 and 25: ";
            }
        }
    }
    
    try {
        string encrypted = encrypt(text, key);
        string decrypted = decrypt(encrypted, key);
        
        cout << "\nOriginal text:  " << text << endl;
        cout << "Encrypted text: " << encrypted << endl;
        cout << "Decrypted text: " << decrypted << endl;
    }
    catch (const runtime_error& e) {
        cout << "\nError: " << e.what() << endl;
        cout << "Please try again with a different key matrix." << endl;
    }
    
    return 0;
}
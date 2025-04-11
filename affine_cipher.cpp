#include <iostream>
#include <string>
using namespace std;

// Function to calculate modular multiplicative inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return 1;
}

string encrypt(string text, int a, int b) {
    string result = "";
    for (char c : text) {
        if (isupper(c)) {
            result += char(((a * (c - 'A') + b) % 26) + 'A');
        }
        else if (islower(c)) {
            result += char(((a * (c - 'a') + b) % 26) + 'a');
        }
        else {
            result += c;
        }
    }
    return result;
}

string decrypt(string text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26);
    
    for (char c : text) {
        if (isupper(c)) {
            result += char((a_inv * (c - 'A' - b + 26) % 26) + 'A');
        }
        else if (islower(c)) {
            result += char((a_inv * (c - 'a' - b + 26) % 26) + 'a');
        }
        else {
            result += c;
        }
    }
    return result;
}

int main() {
    string text;
    int a, b;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter first key (a) [must be coprime with 26]: ";
    cin >> a;
    cout << "Enter second key (b): ";
    cin >> b;
    
    string encrypted = encrypt(text, a, b);
    string decrypted = decrypt(encrypted, a, b);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}
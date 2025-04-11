#include <iostream>
#include <string>
using namespace std;

string encrypt(string text) {
    string result = "";
    for (char c : text) {
        if (isupper(c)) {
            result += char('Z' - (c - 'A'));
        }
        else if (islower(c)) {
            result += char('z' - (c - 'a'));
        }
        else {
            result += c;
        }
    }
    return result;
}

// For Atbash cipher, encryption and decryption are the same
string decrypt(string text) {
    return encrypt(text);  // Atbash is its own inverse
}

int main() {
    string text;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    string encrypted = encrypt(text);
    string decrypted = decrypt(encrypted);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}
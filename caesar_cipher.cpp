#include <iostream>
#include <string>
using namespace std;

// Function to encrypt text using Caesar cipher
string encrypt(string text, int shift) {
    string result = "";
    
    // Traverse text
    for (int i = 0; i < text.length(); i++) {
        // For uppercase letters
        if (isupper(text[i])) {
            result += char(int(text[i] + shift - 65) % 26 + 65);
        }
        // For lowercase letters
        else if (islower(text[i])) {
            result += char(int(text[i] + shift - 97) % 26 + 97);
        }
        // Keep spaces and other characters unchanged
        else {
            result += text[i];
        }
    }
    return result;
}

// Function to decrypt text using Caesar cipher
string decrypt(string text, int shift) {
    // Use the encrypt function with negative shift
    return encrypt(text, 26 - shift);
}

int main() {
    string text;
    int shift;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter shift value (1-25): ";
    cin >> shift;
    
    // Ensure shift is within valid range
    shift = shift % 26;
    
    string encrypted = encrypt(text, shift);
    string decrypted = decrypt(encrypted, shift);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

string encrypt(string text, int shift) {
    string result = "";
    
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char(int(text[i] + shift - 65) % 26 + 65);
        }
        else if (islower(text[i])) {
            result += char(int(text[i] + shift - 97) % 26 + 97);
        }
        else {
            result += text[i];
        }
    }
    return result;
}

string decrypt(string text, int shift) {
    return encrypt(text, 26 - shift);
}

int main() {
    string text;
    int shift;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter shift value (1-25): ";
    cin >> shift;
    
    shift = shift % 26;
    
    string encrypted = encrypt(text, shift);
    string decrypted = decrypt(encrypted, shift);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

string generateKey(string text, string key) {
    string repeatedKey = key;
    while (repeatedKey.length() < text.length()) {
        repeatedKey += key;
    }
    return repeatedKey.substr(0, text.length());
}

string encrypt(string text, string key) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            // Beaufort formula: Ei = (Yi - Pi + 26) % 26
            result += char(('Z' - (text[i] - key[i]) % 26));
        }
        else if (islower(text[i])) {
            result += char(('z' - (text[i] - tolower(key[i])) % 26));
        }
        else {
            result += text[i];
        }
    }
    return result;
}

// In Beaufort cipher, encryption and decryption are the same operation
string decrypt(string text, string key) {
    return encrypt(text, key);
}

int main() {
    string text, key;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter key: ";
    getline(cin, key);
    
    string repeatedKey = generateKey(text, key);
    string encrypted = encrypt(text, repeatedKey);
    string decrypted = decrypt(encrypted, repeatedKey);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}
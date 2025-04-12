#include <iostream>
#include <string>
using namespace std;

string generateAutokey(string text, string key) {
    string autokey = key;
    for (int i = 0; i < text.length() - key.length(); i++) {
        autokey += text[i];
    }
    return autokey;
}

string encrypt(string text, string key) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char((text[i] + toupper(key[i]) - 2 * 'A') % 26 + 'A');
        }
        else if (islower(text[i])) {
            result += char((text[i] + tolower(key[i]) - 2 * 'a') % 26 + 'a');
        }
        else {
            result += text[i];
        }
    }
    return result;
}

string decrypt(string text, string initialKey) {
    string result = "";
    string key = initialKey;
    
    for (int i = 0; i < text.length(); i++) {
        char decrypted;
        if (isupper(text[i])) {
            decrypted = char((text[i] - toupper(key[i]) + 26) % 26 + 'A');
            if (i >= initialKey.length()) {
                key += decrypted;
            }
        }
        else if (islower(text[i])) {
            decrypted = char((text[i] - tolower(key[i]) + 26) % 26 + 'a');
            if (i >= initialKey.length()) {
                key += decrypted;
            }
        }
        else {
            decrypted = text[i];
        }
        result += decrypted;
    }
    return result;
}

int main() {
    string text, initialKey;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter initial key: ";
    getline(cin, initialKey);
    
    string autokey = generateAutokey(text, initialKey);
    string encrypted = encrypt(text, autokey);
    string decrypted = decrypt(encrypted, initialKey);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Initial key: " << initialKey << endl;
    cout << "Full autokey: " << autokey << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}

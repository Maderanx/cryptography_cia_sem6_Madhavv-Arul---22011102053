#include <iostream>
#include <string>
using namespace std;

string generateKey(string text, string key) {
    string repeatedKey = key;
    int x = text.length();
    
    while (repeatedKey.length() < text.length()) {
        repeatedKey += key;
    }
    repeatedKey = repeatedKey.substr(0, text.length());
    
    return repeatedKey;
}

string encrypt(string text, string key) {
    string result = "";
    
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char((text[i] + key[i] - 2 * 'A') % 26 + 'A');
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

string decrypt(string text, string key) {
    string result = "";
    
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char((text[i] - key[i] + 26) % 26 + 'A');
        }
        else if (islower(text[i])) {
            result += char((text[i] - tolower(key[i]) + 26) % 26 + 'a');
        }
        else {
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
    
    string repeatedKey = generateKey(text, key);
    string encrypted = encrypt(text, repeatedKey);
    string decrypted = decrypt(encrypted, repeatedKey);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> processKey(string keyStr, int textLength) {
    vector<int> key;
    for (char c : keyStr) {
        if (isdigit(c)) {
            key.push_back(c - '0');
        }
    }

    vector<int> repeatedKey;
    for (int i = 0; i < textLength; i++) {
        repeatedKey.push_back(key[i % key.size()]);
    }
    return repeatedKey;
}

string encrypt(string text, vector<int>& key) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char((text[i] - 'A' + key[i]) % 26 + 'A');
        }
        else if (islower(text[i])) {
            result += char((text[i] - 'a' + key[i]) % 26 + 'a');
        }
        else {
            result += text[i];
        }
    }
    return result;
}

string decrypt(string text, vector<int>& key) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (isupper(text[i])) {
            result += char((text[i] - 'A' - key[i] + 26) % 26 + 'A');
        }
        else if (islower(text[i])) {
            result += char((text[i] - 'a' - key[i] + 26) % 26 + 'a');
        }
        else {
            result += text[i];
        }
    }
    return result;
}

int main() {
    string text, keyStr;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter numerical key (e.g., 31415): ";
    getline(cin, keyStr);
    
    vector<int> key = processKey(keyStr, text.length());
    string encrypted = encrypt(text, key);
    string decrypted = decrypt(encrypted, key);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Key: " << keyStr << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}

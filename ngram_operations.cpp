#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class NgramOperations {
private:
    // Store frequency analysis results
    map<string, int> ngramFreq;
    int totalNgrams;
    
    string preprocessText(string text) {
        string result;
        for (char c : text) {
            if (isalpha(c)) {
                result += toupper(c);
            }
        }
        return result;
    }

public:
    // Generate all n-grams from text
    vector<string> generateNgrams(string text, int n) {
        vector<string> ngrams;
        text = preprocessText(text);
        
        for (int i = 0; i <= text.length() - n; i++) {
            ngrams.push_back(text.substr(i, n));
        }
        return ngrams;
    }
    
    // Analyze frequency of n-grams
    void analyzeFrequency(string text, int n) {
        ngramFreq.clear();
        totalNgrams = 0;
        text = preprocessText(text);
        
        for (int i = 0; i <= text.length() - n; i++) {
            string ngram = text.substr(i, n);
            ngramFreq[ngram]++;
            totalNgrams++;
        }
    }
    
    // Get frequency analysis results
    void printFrequencyAnalysis() {
        vector<pair<string, int>> freq(ngramFreq.begin(), ngramFreq.end());
        sort(freq.begin(), freq.end(),
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 return a.second > b.second;
             });
        
        cout << "\nN-gram Frequency Analysis:" << endl;
        cout << setw(10) << "N-gram" << setw(10) << "Count" << setw(15) << "Percentage" << endl;
        cout << string(35, '-') << endl;
        
        for (const auto& p : freq) {
            double percentage = (100.0 * p.second) / totalNgrams;
            cout << setw(10) << p.first << setw(10) << p.second 
                 << setw(15) << fixed << setprecision(2) << percentage << "%" << endl;
        }
    }
    
    // Find repeating sequences
    vector<pair<string, vector<int>>> findRepeatingSequences(string text, int n) {
        text = preprocessText(text);
        map<string, vector<int>> positions;
        vector<pair<string, vector<int>>> results;
        
        for (int i = 0; i <= text.length() - n; i++) {
            string ngram = text.substr(i, n);
            positions[ngram].push_back(i);
        }
        
        for (const auto& p : positions) {
            if (p.second.size() > 1) {
                results.push_back(p);
            }
        }
        
        sort(results.begin(), results.end(),
             [](const auto& a, const auto& b) {
                 return a.second.size() > b.second.size();
             });
        
        return results;
    }
    
    // Calculate Index of Coincidence (IoC)
    double calculateIoC(string text) {
        text = preprocessText(text);
        vector<int> freqs(26, 0);
        int n = text.length();
        
        for (char c : text) {
            freqs[c - 'A']++;
        }
        
        double ioc = 0;
        for (int f : freqs) {
            ioc += (f * (f - 1.0)) / (n * (n - 1.0));
        }
        
        return ioc;
    }
};

// Simple substitution encryption using n-gram analysis for key generation
string encrypt(string text, string key) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += key[toupper(c) - 'A'];
            if (islower(c)) {
                result.back() = tolower(result.back());
            }
        } else {
            result += c;
        }
    }
    return result;
}

string decrypt(string text, string key) {
    string inverse_key(26, ' ');
    for (int i = 0; i < 26; i++) {
        inverse_key[key[i] - 'A'] = 'A' + i;
    }
    return encrypt(text, inverse_key);
}

int main() {
    NgramOperations ngram;
    string text, operation;
    int n;
    
    cout << "Enter text for analysis: ";
    getline(cin, text);
    
    cout << "\nAvailable operations:" << endl;
    cout << "1. Generate n-grams" << endl;
    cout << "2. Frequency analysis" << endl;
    cout << "3. Find repeating sequences" << endl;
    cout << "4. Calculate Index of Coincidence" << endl;
    cout << "5. Simple substitution cipher" << endl;
    cout << "\nEnter operation number: ";
    getline(cin, operation);
    
    if (operation == "1" || operation == "2" || operation == "3") {
        cout << "Enter n (length of n-grams): ";
        cin >> n;
        
        if (operation == "1") {
            vector<string> ngrams = ngram.generateNgrams(text, n);
            cout << "\nGenerated " << n << "-grams:" << endl;
            for (const string& ng : ngrams) {
                cout << ng << " ";
            }
            cout << endl;
        }
        else if (operation == "2") {
            ngram.analyzeFrequency(text, n);
            ngram.printFrequencyAnalysis();
        }
        else if (operation == "3") {
            auto sequences = ngram.findRepeatingSequences(text, n);
            cout << "\nRepeating " << n << "-gram sequences:" << endl;
            for (const auto& seq : sequences) {
                cout << seq.first << " appears at positions: ";
                for (int pos : seq.second) {
                    cout << pos << " ";
                }
                cout << endl;
            }
        }
    }
    else if (operation == "4") {
        double ioc = ngram.calculateIoC(text);
        cout << "\nIndex of Coincidence: " << fixed << setprecision(4) << ioc << endl;
        cout << "(English text typically has IoC around 0.067)" << endl;
    }
    else if (operation == "5") {
        string key;
        cout << "Enter 26-letter key (A-Z): ";
        cin >> key;
        transform(key.begin(), key.end(), key.begin(), ::toupper);
        
        if (key.length() != 26) {
            cout << "Error: Key must be exactly 26 letters" << endl;
            return 1;
        }
        
        string encrypted = encrypt(text, key);
        string decrypted = decrypt(encrypted, key);
        
        cout << "\nOriginal text: " << text << endl;
        cout << "Encrypted text: " << encrypted << endl;
        cout << "Decrypted text: " << decrypted << endl;
    }
    
    return 0;
}
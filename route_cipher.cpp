#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<char>> createGrid(string text, int rows, int cols) {
    vector<vector<char>> grid(rows, vector<char>(cols, ' '));
    int k = 0;

    for (int i = 0; i < rows && k < text.length(); i++) {
        for (int j = 0; j < cols && k < text.length(); j++) {
            grid[i][j] = text[k++];
        }
    }
    return grid;
}

string encrypt(string text, int rows, int cols, int route) {
    while (text.length() < rows * cols) {
        text += ' ';
    }
    
    vector<vector<char>> grid = createGrid(text, rows, cols);
    string result = "";
    
    switch (route) {
        case 1: 
            {
                int top = 0, bottom = rows - 1;
                int left = 0, right = cols - 1;
                
                while (top <= bottom && left <= right) {
                    for (int i = left; i <= right; i++)
                        result += grid[top][i];
                    top++;
 
                    for (int i = top; i <= bottom; i++)
                        result += grid[i][right];
                    right--;
                    
                    if (top <= bottom) {
                        for (int i = right; i >= left; i--)
                            result += grid[bottom][i];
                        bottom--;
                    }
                    
                    if (left <= right) {
                        for (int i = bottom; i >= top; i--)
                            result += grid[i][left];
                        left++;
                    }
                }
            }
            break;
            
        case 2: 
            for (int i = 0; i < rows; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < cols; j++)
                        result += grid[i][j];
                } else {
                    for (int j = cols - 1; j >= 0; j--)
                        result += grid[i][j];
                }
            }
            break;
            
        case 3: 
            for (int sum = 0; sum < rows + cols - 1; sum++) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (i + j == sum)
                            result += grid[i][j];
                    }
                }
            }
            break;
    }

    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    return result;
}

string decrypt(string text, int rows, int cols, int route) {
    vector<vector<char>> grid(rows, vector<char>(cols, ' '));
    int k = 0;

    switch (route) {
        case 1: 
            {
                int top = 0, bottom = rows - 1;
                int left = 0, right = cols - 1;
                
                while (top <= bottom && left <= right && k < text.length()) {
                    for (int i = left; i <= right && k < text.length(); i++)
                        grid[top][i] = text[k++];
                    top++;
                    
                    for (int i = top; i <= bottom && k < text.length(); i++)
                        grid[i][right] = text[k++];
                    right--;
                    
                    if (top <= bottom) {
                        for (int i = right; i >= left && k < text.length(); i--)
                            grid[bottom][i] = text[k++];
                        bottom--;
                    }
                    
                    if (left <= right) {
                        for (int i = bottom; i >= top && k < text.length(); i--)
                            grid[i][left] = text[k++];
                        left++;
                    }
                }
            }
            break;
            
        case 2: 
            for (int i = 0; i < rows; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < cols && k < text.length(); j++)
                        grid[i][j] = text[k++];
                } else {
                    for (int j = cols - 1; j >= 0 && k < text.length(); j--)
                        grid[i][j] = text[k++];
                }
            }
            break;
            
        case 3: 
            for (int sum = 0; sum < rows + cols - 1 && k < text.length(); sum++) {
                for (int i = 0; i < rows && k < text.length(); i++) {
                    for (int j = 0; j < cols && k < text.length(); j++) {
                        if (i + j == sum)
                            grid[i][j] = text[k++];
                    }
                }
            }
            break;
    }

    string result = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != ' ') {
                result += grid[i][j];
            }
        }
    }
    
    return result;
}

int main() {
    string text;
    int rows, cols, route;
    
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    
    cout << "Enter grid dimensions (rows cols): ";
    cin >> rows >> cols;
    
    cout << "Enter route type (1: Spiral, 2: Snake, 3: Diagonal): ";
    cin >> route;
    
    string encrypted = encrypt(text, rows, cols, route);
    string decrypted = decrypt(encrypted, rows, cols, route);
    
    cout << "\nOriginal text: " << text << endl;
    cout << "Encrypted text: " << encrypted << endl;
    cout << "Decrypted text: " << decrypted << endl;
    
    return 0;
}

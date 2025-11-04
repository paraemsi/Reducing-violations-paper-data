#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

namespace crypto_square {

cipher::cipher(const string& text) {
    // Normalize the input text
    for (char c : text) {
        if (isalnum(c)) {
            normalized_text += tolower(c);
        }
    }
}

string cipher::normalize_plain_text() const {
    return normalized_text;
}

string cipher::cipher_text() const {
    // For the basic cipher text, it's the same as normalized_cipher_text but without spaces
    string normalized_cipher = normalized_cipher_text();
    string result;
    for (char c : normalized_cipher) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

string cipher::normalized_cipher_text() const {
    int length = normalized_text.size();
    if (length == 0) return "";
    
    // Find the number of columns (c) and rows (r) that satisfy:
    // r * c >= length
    // c >= r
    // c - r <= 1
    int c = static_cast<int>(ceil(sqrt(length)));
    int r = static_cast<int>(ceil(static_cast<double>(length) / c));
    
    // Adjust to meet conditions
    while (true) {
        if (c >= r && (c - r) <= 1 && r * c >= length) {
            break;
        }
        // If conditions are not met, increase c and recalculate r
        c++;
        r = static_cast<int>(ceil(static_cast<double>(length) / c));
    }
    
    // Build the grid with padding
    vector<string> grid(r, string(c, ' '));
    for (int i = 0; i < length; i++) {
        int row = i / c;
        int col = i % c;
        grid[row][col] = normalized_text[i];
    }
    
    // Read down the columns to form the cipher text
    string result;
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            result += grid[row][col];
        }
        if (col < c - 1) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

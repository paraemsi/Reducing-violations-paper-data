#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

namespace crypto_square {

cipher::cipher(const string& text) {
    // Normalize the input text
    for (char c : text) {
        if (isalnum(c)) {
            normalized += tolower(c);
        }
    }
}

string cipher::normalize_plain_text() const {
    return normalized;
}

size_t cipher::size() const {
    if (normalized.empty()) return 0;
    size_t length = normalized.size();
    
    // Start from the ceiling of the square root
    size_t c = static_cast<size_t>(ceil(sqrt(length)));
    while (true) {
        size_t r = (length + c - 1) / c; // Ceiling division
        if (c >= r && c - r <= 1) {
            break;
        }
        c++;
    }
    return c;
}

vector<string> cipher::plain_text_segments() const {
    vector<string> segments;
    size_t c = size();
    if (c == 0) return segments;
    
    for (size_t i = 0; i < normalized.size(); i += c) {
        segments.push_back(normalized.substr(i, c));
    }
    return segments;
}

string cipher::cipher_text() const {
    size_t c = size();
    if (c == 0) return "";
    size_t length = normalized.size();
    size_t r = (length + c - 1) / c; // Ceiling division
    
    // Create a grid with padding
    vector<string> grid(r, string(c, ' '));
    for (size_t i = 0; i < length; i++) {
        grid[i / c][i % c] = normalized[i];
    }
    
    // Read down the columns
    string result;
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            result += grid[row][col];
        }
    }
    return result;
}

string cipher::normalized_cipher_text() const {
    string ct = cipher_text();
    if (ct.empty()) return "";
    
    size_t c = size();
    size_t length = normalized.size();
    size_t r = (length + c - 1) / c;
    
    // Split into c chunks of r length each, separated by spaces
    string result;
    for (size_t i = 0; i < c; i++) {
        if (i > 0) {
            result += ' ';
        }
        // Add the current chunk
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

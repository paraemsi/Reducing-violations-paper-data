#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cmath>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the text upon construction
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized_text += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::string cipher::cipher_text() const {
    std::string normalized_cipher = normalized_cipher_text();
    if (normalized_cipher.empty()) return "";
    
    // The number of rows is the number of characters in each chunk
    int length = normalized_text.size();
    // Find c and r
    int c = 0;
    int r = 0;
    // Find the smallest c such that c >= r and c - r <= 1 and c * r >= length
    // Start by finding potential c and r values
    for (int i = 1; i <= length; i++) {
        int potential_c = i;
        int potential_r = (length + potential_c - 1) / potential_c; // Ceiling division
        if (potential_c >= potential_r && potential_c - potential_r <= 1) {
            c = potential_c;
            r = potential_r;
            break;
        }
    }
    if (c == 0) {
        c = 1;
        r = 1;
    }
    
    // Split into chunks of size r and join with spaces
    std::string result;
    for (int i = 0; i < normalized_cipher.size(); i++) {
        if (i != 0 && i % r == 0) {
            result += ' ';
        }
        result += normalized_cipher[i];
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) return "";
    
    int length = normalized_text.size();
    // Determine number of columns and rows that meet the conditions
    int c = 0;
    int r = 0;
    for (int i = 1; i <= length; i++) {
        int potential_c = i;
        int potential_r = (length + potential_c - 1) / potential_c; // Ceiling division
        if (potential_c >= potential_r && potential_c - potential_r <= 1) {
            c = potential_c;
            r = potential_r;
            break;
        }
    }
    if (c == 0) {
        c = 1;
        r = 1;
    }
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r);
    for (int i = 0; i < r; i++) {
        int start = i * c;
        int end = std::min(start + c, length);
        grid[i] = normalized_text.substr(start, end - start);
        // Pad with spaces if necessary
        grid[i].resize(c, ' ');
    }
    
    // Read down the columns to form the encoded text without spaces
    std::string encoded;
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            encoded += grid[row][col];
        }
    }
    return encoded;
}

}  // namespace crypto_square

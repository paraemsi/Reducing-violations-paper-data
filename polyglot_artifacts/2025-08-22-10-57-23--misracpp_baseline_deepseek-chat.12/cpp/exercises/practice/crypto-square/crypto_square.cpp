#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::string cipher::cipher_text() const {
    if (normalized.empty()) return "";
    
    int length = normalized.size();
    // Determine number of columns and rows
    int c = static_cast<int>(std::ceil(std::sqrt(length)));
    int r;
    // Adjust to meet conditions
    while (true) {
        r = (length + c - 1) / c; // Ceiling division
        if (c >= r && c - r <= 1) {
            break;
        }
        c++;
    }
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    int index = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (index < length) {
                grid[i][j] = normalized[index++];
            }
        }
    }
    
    // Read down the columns
    std::string result;
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            result += grid[i][j];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    if (ct.empty()) return "";
    
    int length = normalized.size();
    // Determine c and r
    int c = static_cast<int>(std::ceil(std::sqrt(length)));
    int r;
    while (true) {
        r = (length + c - 1) / c;
        if (c >= r && c - r <= 1) {
            break;
        }
        c++;
    }
    
    // Split into c chunks of r characters each
    std::string result;
    for (int i = 0; i < c; i++) {
        if (i != 0) {
            result += ' ';
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

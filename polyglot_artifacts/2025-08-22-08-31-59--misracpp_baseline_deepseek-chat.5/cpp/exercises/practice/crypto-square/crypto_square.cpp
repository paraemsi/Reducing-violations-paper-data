#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the text by removing non-alphanumeric characters and converting to lowercase
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized_text += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) return "";
    
    int length = normalized_text.size();
    // Determine number of columns and rows
    int c = 0;
    int r = 0;
    
    // Find the smallest c that satisfies the conditions
    // c >= r, c - r <= 1, r * c >= length
    // Start from the square root
    int root = static_cast<int>(std::ceil(std::sqrt(length)));
    for (c = root; c <= length; c++) {
        r = (length + c - 1) / c; // Ceiling of length/c
        if (c >= r && (c - r) <= 1) {
            break;
        }
    }
    
    // Pad the normalized text with spaces to reach r*c length
    std::string padded = normalized_text;
    padded.resize(r * c, ' ');
    
    // Build the encoded text by reading down the columns
    std::string result;
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            result += padded[j * c + i];
        }
    }
    return result;
}

std::string cipher::cipher_text() const {
    std::string encoded = this->normalized_cipher_text();
    if (encoded.empty()) return "";
    
    // Determine number of rows
    int length = normalized_text.size();
    int c = 0;
    int r = 0;
    
    int root = static_cast<int>(std::ceil(std::sqrt(length)));
    for (c = root; c <= length; c++) {
        r = (length + c - 1) / c;
        if (c >= r && (c - r) <= 1) {
            break;
        }
    }
    
    // Split into c chunks of r length each, separated by spaces
    std::string result;
    for (int i = 0; i < encoded.size(); i++) {
        if (i != 0 && i % r == 0) {
            result += ' ';
        }
        result += encoded[i];
    }
    return result;
}

}  // namespace crypto_square

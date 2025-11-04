#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
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
    std::string norm = normalize_plain_text();
    if (norm.empty()) return "";
    
    size_t length = norm.size();
    // Determine number of columns and rows
    size_t c = 0;
    size_t r = 0;
    
    // Find the smallest c such that:
    // c >= r
    // c - r <= 1
    // r * c >= length
    // Since c and r are integers, and c >= r, and c - r <= 1, then r is either equal to c or c-1
    // So we can find the smallest c where r = ceil(length/c) satisfies the conditions
    // Let's find c by checking values around the square root
    for (c = static_cast<size_t>(std::ceil(std::sqrt(length))); ; c++) {
        r = (length + c - 1) / c; // This is ceiling(length/c)
        if (c >= r && (c - r) <= 1) {
            break;
        }
    }
    
    // Pad the string to fill the rectangle
    std::string padded = norm;
    padded.append(r * c - length, ' ');
    
    // Read down the columns to get the cipher text
    std::string result;
    for (size_t i = 0; i < c; i++) {
        for (size_t j = 0; j < r; j++) {
            result += padded[j * c + i];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    if (ct.empty()) return "";
    
    size_t length = normalized.size();
    // Determine number of columns and rows (same as in cipher_text)
    size_t c = 0;
    size_t r = 0;
    
    // Find c and r using the same approach as in cipher_text()
    for (c = static_cast<size_t>(std::ceil(std::sqrt(length))); ; c++) {
        r = (length + c - 1) / c;
        if (c >= r && (c - r) <= 1) {
            break;
        }
    }
    
    // Split the cipher text into chunks of size r, separated by spaces
    std::string result;
    for (size_t i = 0; i < ct.size(); i++) {
        if (i != 0 && i % r == 0) {
            result += ' ';
        }
        result += ct[i];
    }
    return result;
}

}  // namespace crypto_square

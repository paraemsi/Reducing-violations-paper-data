#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
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

std::string cipher::normalized_cipher_text() const {
    int length = normalized.size();
    if (length == 0) return "";
    
    // Determine number of columns and rows
    int c = static_cast<int>(std::ceil(std::sqrt(length)));
    int r = (length + c - 1) / c; // Ceiling division
    
    // Adjust to meet conditions: c >= r and c - r <= 1
    // We need to find the smallest c where these conditions are true and r*c >= length
    // Let's find proper values
    // Since c is at least ceil(sqrt(n)), and r is ceil(n/c), we can find the right values
    while (true) {
        if (c >= r && (c - r) <= 1 && c * r >= length) {
            break;
        }
        // If conditions aren't met, increase c and recalculate r
        c++;
        r = (length + c - 1) / c;
    }
    
    // Pad the normalized text
    std::string padded = normalized;
    padded.append(r * c - length, ' ');
    
    // Read down the columns to form the encoded text
    std::vector<std::string> chunks(c);
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            chunks[i] += padded[j * c + i];
        }
    }
    
    // Join the chunks with spaces
    std::string result;
    for (int i = 0; i < chunks.size(); i++) {
        if (i != 0) {
            result += " ";
        }
        result += chunks[i];
    }
    return result;
}

}  // namespace crypto_square

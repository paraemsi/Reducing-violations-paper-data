#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) return 0;
    std::size_t length = normalized.size();
    
    // Find the smallest c that satisfies the conditions
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    while (true) {
        std::size_t r = (length + c - 1) / c; // Ceiling division
        // Check conditions
        if ((c >= r) && ((c - r) <= 1)) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    std::size_t length = normalized.size();
    std::size_t c = size();
    std::size_t r = (length + c - 1) / c; // Ceiling division to get number of rows
    
    // Pad the string
    std::string padded = normalized;
    padded.append(r * c - length, ' ');
    
    // Read down the columns to build the encoded text
    std::string encoded;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            encoded += padded[row * c + col];
        }
    }
    
    // Split into chunks of 'r' characters separated by spaces
    std::string result;
    for (std::size_t i = 0; i < encoded.size(); i++) {
        if (i > 0 && (i % r) == 0) {
            result += ' ';
        }
        result += encoded[i];
    }
    return result;
}

}  // namespace crypto_square

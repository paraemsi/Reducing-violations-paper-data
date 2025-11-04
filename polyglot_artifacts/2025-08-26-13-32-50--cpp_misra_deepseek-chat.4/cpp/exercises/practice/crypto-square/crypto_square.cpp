#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized += std::tolower(static_cast<unsigned char>(ch));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) {
        return 0;
    }
    std::size_t length = normalized.size();
    // Find the number of columns (c)
    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(length)));
    std::size_t c = r;
    
    while ((r * c) < length) {
        c++;
        if ((c - r) > 1) {
            r++;
            c = r;
        }
    }
    return c;
}

std::string cipher::cipher_text() const {
    // Return the raw encoded text without spaces
    if (normalized.empty()) {
        return "";
    }
    std::size_t length = normalized.size();
    // Determine number of rows (r) and columns (c)
    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(length)));
    std::size_t c = r;
    
    while ((r * c) < length) {
        c++;
        if ((c - r) > 1) {
            r++;
            c = r;
        }
    }
    
    // Pad the normalized string to fill the grid
    std::string padded = normalized;
    padded.resize(r * c, ' ');
    
    // Build the encoded text by reading down the columns
    std::string result;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            result += padded[row * c + col];
        }
    }
    
    return result;
}

std::string cipher::normalized_cipher_text() const {
    // Return the encoded text with spaces between chunks
    std::string raw_cipher = cipher_text();
    if (raw_cipher.empty()) {
        return "";
    }
    
    // Determine number of rows (r)
    std::size_t length = normalized.size();
    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(length)));
    std::size_t c = r;
    
    while ((r * c) < length) {
        c++;
        if ((c - r) > 1) {
            r++;
            c = r;
        }
    }
    
    // Insert spaces every r characters
    std::string result;
    for (std::size_t i = 0; i < raw_cipher.size(); i++) {
        result += raw_cipher[i];
        if (((i + 1) % r) == 0 && (i + 1) < raw_cipher.size()) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

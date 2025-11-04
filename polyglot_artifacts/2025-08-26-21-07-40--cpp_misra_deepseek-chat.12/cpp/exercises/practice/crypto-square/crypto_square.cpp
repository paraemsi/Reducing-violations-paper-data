#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
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
    if (normalized.empty()) {
        return 0;
    }
    const std::size_t length = normalized.size();
    // Find the smallest c such that c >= r and c - r <= 1 where r * c >= length
    // Start with the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r;
    
    // Adjust to meet all conditions
    while (true) {
        // Calculate number of rows
        r = (length + c - 1) / c; // Ceiling division
        // Check if conditions are satisfied
        if (c >= r && (c - r) <= 1) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) {
        return "";
    }
    const std::size_t length = normalized.size();
    const std::size_t c = size();
    // Calculate number of rows
    const std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Read down the columns to form the encoded text directly
    std::string result;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            const std::size_t index = row * c + col;
            if (index < length) {
                result += normalized[index];
            } else {
                result += ' ';
            }
        }
        // Add space between chunks, but not after the last one
        if (col < (c - 1)) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

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
            normalized_text += std::tolower(static_cast<unsigned char>(c));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    if (normalized_text.empty()) {
        return 0;
    }
    std::size_t length = normalized_text.size();
    // Find the smallest c where c >= r and c - r <= 1
    // Start with c = ceil(sqrt(length)), and adjust if necessary
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Check if conditions are satisfied
    if ((c >= r) && ((c - r) <= 1)) {
        return c;
    } else {
        // Adjust to find the correct dimensions
        // Since c must be >= r and c - r <= 1, r is essentially floor(sqrt(length)) or ceil(sqrt(length))
        // Let's find c such that c is the smallest integer where c >= ceil(sqrt(length)) and c*(c-1) >= length may not always work
        // The correct approach is to find c where c is the ceiling of the square root, and r is floor of length/c (rounded up)
        // But to satisfy c >= r and c - r <= 1, we may need to try different values
        // For efficiency, we can start from the ceiling of the square root and find the first c where r = ceil(length/c) satisfies conditions
        while (true) {
            r = (length + c - 1) / c;
            if ((c >= r) && ((c - r) <= 1)) {
                return c;
            }
            c++;
        }
    }
}

std::string cipher::plain_text_segments() const {
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < normalized_text.size(); i += c) {
        if (i != 0) {
            result += " ";
        }
        result += normalized_text.substr(i, c);
    }
    return result;
}

std::string cipher::cipher_text() const {
    std::string encoded;
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t r = (normalized_text.size() + c - 1) / c; // Ceiling division
    
    // Read down the columns
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            std::size_t index = row * c + col;
            if (index < normalized_text.size()) {
                encoded += normalized_text[index];
            } else {
                encoded += ' ';
            }
        }
    }
    return encoded;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t r = (normalized_text.size() + c - 1) / c;
    
    // Split into c chunks of r length each, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < c; i++) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

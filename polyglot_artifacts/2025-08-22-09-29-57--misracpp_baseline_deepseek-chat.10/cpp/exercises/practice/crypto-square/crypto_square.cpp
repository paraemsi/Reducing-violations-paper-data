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
            normalized_text += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    if (normalized_text.empty()) return 0;
    // Find the number of columns which is the smallest integer c where c >= ceil(sqrt(length))
    // and satisfies the conditions with r = ceil(length / c)
    std::size_t length = normalized_text.length();
    // Start from the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    while (true) {
        std::size_t r = (length + c - 1) / c; // Ceiling division for number of rows
        if (c >= r && c - r <= 1) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::cipher_text() const {
    // This seems to be a placeholder, but we need to implement it
    // Let's reuse the implementation from normalized_cipher_text
    return normalized_cipher_text();
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) return "";
    
    std::size_t length = normalized_text.length();
    std::size_t c = size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Organize into a grid, padding with spaces
    // We can build the result by reading down the columns directly
    std::string result;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t index = row * c + col;
            if (index < length) {
                result += normalized_text[index];
            } else {
                result += ' ';
            }
        }
        // Add space between chunks, but not after the last one
        if (col < c - 1) {
            result += ' ';
        }
    }
    return result;
}

}  // namespace crypto_square

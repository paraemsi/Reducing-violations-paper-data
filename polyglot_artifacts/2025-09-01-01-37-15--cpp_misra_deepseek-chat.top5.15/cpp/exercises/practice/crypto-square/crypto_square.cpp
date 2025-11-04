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
            normalized += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
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
    // Find the smallest c that satisfies the conditions
    std::size_t c = 0;
    for (std::size_t potential_c = 1; potential_c <= length; ++potential_c) {
        std::size_t r = (length + potential_c - 1) / potential_c; // Ceiling division
        if ((potential_c >= r) && ((potential_c - r) <= 1)) {
            c = potential_c;
            break;
        }
    }
    return c;
}

std::string cipher::cipher_text() const {
    // This seems to be used for something else, but we need to implement normalized_cipher_text
    // Let's implement it to return the same as normalized_cipher_text for now
    return normalized_cipher_text();
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) {
        return "";
    }
    
    std::size_t c = size();
    std::size_t length = normalized.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    for (std::size_t i = 0; i < length; ++i) {
        std::size_t row = i / c;
        std::size_t col = i % c;
        grid[row][col] = normalized[i];
    }
    
    // Read down the columns to build the result
    std::string result;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            result += grid[row][col];
        }
        // Add space between chunks, but not after the last one
        if (col < c - 1) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

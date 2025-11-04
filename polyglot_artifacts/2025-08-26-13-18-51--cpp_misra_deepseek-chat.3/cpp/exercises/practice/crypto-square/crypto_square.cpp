#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
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
    if (normalized.empty()) return 0;
    std::size_t length = normalized.size();
    
    // Find the smallest c such that:
    // c >= ceil(sqrt(length)) and c - floor(sqrt(length)) <= 1
    // Since c >= r and c - r <= 1, and r * c >= length
    // We can find r first
    std::size_t r = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    std::size_t c = r;
    
    // Check if r * c >= length
    // If not, we need to adjust
    if (r * c < length) {
        c = r + 1;
        // Now check if c - r <= 1, which it always will be since c = r + 1
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    
    std::size_t length = normalized.size();
    std::size_t c = size();
    // Calculate number of rows
    std::size_t r = (length + c - 1) / c; // This is ceiling(length / c)
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    for (std::size_t i = 0; i < r; i++) {
        for (std::size_t j = 0; j < c; j++) {
            std::size_t index = i * c + j;
            if (index < length) {
                grid[i][j] = normalized[index];
            }
        }
    }
    
    // Read down the columns to form the encoded text
    std::string encoded;
    for (std::size_t j = 0; j < c; j++) {
        for (std::size_t i = 0; i < r; i++) {
            encoded += grid[i][j];
        }
        if (j < c - 1) {
            encoded += ' ';
        }
    }
    
    return encoded;
}

}  // namespace crypto_square

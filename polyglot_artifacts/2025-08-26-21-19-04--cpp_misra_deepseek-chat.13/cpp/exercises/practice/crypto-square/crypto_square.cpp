#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>

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
    if (normalized.empty()) return 0;
    
    const std::size_t length = normalized.size();
    // Start with c as the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    
    // Adjust c until we find the smallest c that satisfies all conditions
    while (true) {
        // Calculate number of rows needed
        std::size_t r = (length + c - 1) / c; // This is ceiling(length / c)
        
        // Check conditions
        if ((r <= c) && (c - r <= 1) && (r * c >= length)) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::cipher_text() const {
    if (normalized.empty()) return "";
    
    const std::size_t length = normalized.size();
    std::size_t c = size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    
    // Fill the grid row by row
    for (std::size_t i = 0; i < length; i++) {
        std::size_t row = i / c;
        std::size_t col = i % c;
        grid[row][col] = normalized[i];
    }
    
    // Read down the columns to form the encoded text
    std::string result;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            result += grid[row][col];
        }
        // Add space after each column's worth of characters, except the last one
        if (col < c - 1) {
            result += ' ';
        }
    }
    
    return result;
}

std::string cipher::normalized_cipher_text() const {
    return normalize_plain_text();
}

}  // namespace crypto_square

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
    if (normalized.empty()) return 0;
    
    std::size_t L = normalized.size();
    // Find the smallest c that satisfies the conditions
    // Start with c = ceil(sqrt(L)) and find r = ceil(L / c)
    // Check if c >= r and c - r <= 1
    // If not, adjust
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(L)));
    while (true) {
        std::size_t r = (L + c - 1) / c; // Ceiling division
        if (c >= r && (c - r) <= 1) {
            break;
        }
        ++c;
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    
    std::size_t L = normalized.size();
    // Determine c and r
    std::size_t c = size();
    std::size_t r = (L + c - 1) / c; // Ceiling division to get number of rows
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    for (std::size_t i = 0; i < L; ++i) {
        std::size_t row = i / c;
        std::size_t col = i % c;
        grid[row][col] = normalized[i];
    }
    
    // Read down the columns
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

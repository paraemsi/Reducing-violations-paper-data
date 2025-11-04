#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) return 0;
    std::size_t length = normalized.size();
    // Find the number of columns c that satisfies all conditions
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    // Calculate number of rows r
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Adjust to meet all conditions
    // We need to ensure c >= r and c - r <= 1
    // If not, we may need to adjust c and r
    while (c < r || (c - r) > 1) {
        c++;
        r = (length + c - 1) / c;
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    
    std::size_t length = normalized.size();
    // Determine c and r that satisfy all conditions
    std::size_t c = size();
    std::size_t r = (length + c - 1) / c;
    
    // Adjust to meet all conditions
    while (c < r || (c - r) > 1) {
        c++;
        r = (length + c - 1) / c;
    }
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> rows(r, std::string(c, ' '));
    // Fill the grid
    for (std::size_t i = 0; i < length; i++) {
        rows[i / c][i % c] = normalized[i];
    }
    
    // Build the encoded text by reading down the columns
    std::string encoded;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            encoded += rows[row][col];
        }
        // Add a space after each column chunk except the last one
        if (col != c - 1) {
            encoded += ' ';
        }
    }
    
    return encoded;
}

}  // namespace crypto_square

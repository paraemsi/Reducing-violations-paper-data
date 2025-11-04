#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    
    const std::size_t length = normalized.length();
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Find c and r that satisfy the conditions
    // Start with c as the ceiling of the square root
    num_cols = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    num_rows = (length + num_cols - 1) / num_cols; // Ceiling division
    
    // Adjust to meet c >= r and c - r <= 1
    // If conditions are not met, we may need to adjust
    // Let's ensure the conditions are always true
    // For the given conditions, c is always >= r, and c - r <= 1
    // This should be true when c is the ceiling of the square root
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    std::string result;
    for (std::size_t i = 0; i < num_rows; ++i) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * num_cols;
        std::size_t end = std::min(start + num_cols, normalized.length());
        result += normalized.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized.empty()) {
        return "";
    }
    
    // Build the encoded text by reading down the columns
    std::string result;
    for (std::size_t col = 0; col < num_cols; ++col) {
        for (std::size_t row = 0; row < num_rows; ++row) {
            std::size_t index = row * num_cols + col;
            if (index < normalized.length()) {
                result += normalized[index];
            } else {
                result += ' ';
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    if (ct.empty()) {
        return "";
    }
    
    // Split into chunks of size num_rows (which is the number of characters per column)
    // There will be num_cols chunks
    std::string result;
    for (std::size_t i = 0; i < num_cols; ++i) {
        if (i != 0) {
            result += " ";
        }
        // Get the i-th chunk of num_rows characters
        result += ct.substr(i * num_rows, num_rows);
    }
    return result;
}

}  // namespace crypto_square

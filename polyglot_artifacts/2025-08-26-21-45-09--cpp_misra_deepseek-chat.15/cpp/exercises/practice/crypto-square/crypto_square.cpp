#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
    
    // Determine number of columns (c) and rows (r)
    const std::size_t length = normalized.length();
    if (length == 0) {
        num_columns = 0;
        num_rows = 0;
        return;
    }
    
    // Find the smallest c such that c >= r, c - r <= 1, and c * r >= length
    // Start by finding the square root to get initial dimensions
    double root = std::sqrt(length);
    num_columns = static_cast<std::size_t>(std::ceil(root));
    num_rows = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / num_columns));
    
    // Adjust to meet conditions
    while (num_columns < num_rows || (num_columns - num_rows) > 1) {
        num_columns++;
        num_rows = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / num_columns));
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    return num_columns;
}

std::string cipher::plain_text_segments() const {
    if (normalized.empty()) return "";
    
    std::string result;
    for (std::size_t i = 0; i < num_rows; i++) {
        std::size_t start = i * num_columns;
        if (start < normalized.length()) {
            std::size_t end = std::min(start + num_columns, normalized.length());
            result += normalized.substr(start, end - start);
        }
        if (i < num_rows - 1) {
            result += ' ';
        }
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized.empty()) return "";
    
    // Create a grid with padding
    std::string padded = normalized;
    padded.resize(num_rows * num_columns, ' ');
    
    // Read down the columns to get the cipher text
    std::string result;
    for (std::size_t col = 0; col < num_columns; col++) {
        for (std::size_t row = 0; row < num_rows; row++) {
            result += padded[row * num_columns + col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    if (ct.empty()) return "";
    
    // Split into num_columns chunks, each of length num_rows, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < num_columns; i++) {
        if (i != 0) {
            result += ' ';
        }
        result += ct.substr(i * num_rows, num_rows);
    }
    return result;
}

}  // namespace crypto_square

#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized_text += std::tolower(static_cast<unsigned char>(c));
        }
    }
    
    const std::size_t length = normalized_text.size();
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Find the number of columns (c) that satisfies the conditions
    // Start with the ceiling of the square root
    num_cols = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    while (true) {
        // Calculate number of rows
        num_rows = (length + num_cols - 1) / num_cols; // This is integer ceiling division
        // Check conditions
        if ((num_cols >= num_rows) && ((num_cols - num_rows) <= 1) && (num_cols * num_rows >= length)) {
            break;
        }
        num_cols++;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    if (normalized_text.empty()) return "";
    
    std::string result;
    for (std::size_t i = 0; i < num_rows; i++) {
        if (i != 0) result += " ";
        std::size_t start = i * num_cols;
        std::size_t end = std::min(start + num_cols, normalized_text.size());
        result += normalized_text.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) return "";
    
    // The grid is num_rows x num_cols, fill it row-wise first
    // Then read column-wise
    std::string result;
    for (std::size_t col = 0; col < num_cols; col++) {
        for (std::size_t row = 0; row < num_rows; row++) {
            std::size_t index = row * num_cols + col;
            if (index < normalized_text.size()) {
                result += normalized_text[index];
            } else {
                result += ' '; // Pad with spaces
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) return "";
    
    // Read column-wise to get the cipher text
    // Then split into 'c' chunks of 'r' characters each
    std::string ct = cipher_text();
    
    // Split into num_cols chunks, each of length num_rows
    std::string result;
    for (std::size_t i = 0; i < num_cols; i++) {
        if (i != 0) {
            result += " ";
        }
        // Get the i-th chunk
        result += ct.substr(i * num_rows, num_rows);
    }
    return result;
}

}  // namespace crypto_square

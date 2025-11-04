#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    
    const std::size_t length = normalized_text.length();
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Find the number of columns and rows that satisfy the conditions
    // Start with c = ceil(sqrt(length)), and adjust if necessary
    num_cols = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    num_rows = (length + num_cols - 1) / num_cols; // Ceiling division
    
    // Check if conditions are met
    // We need to ensure c >= r and c - r <= 1
    // If not, adjust num_cols until they are
    while (true) {
        if ((num_cols >= num_rows) && ((num_cols - num_rows) <= 1)) {
            break;
        }
        // Adjust
        num_cols++;
        num_rows = (length + num_cols - 1) / num_cols;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < num_rows; ++i) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * num_cols;
        std::size_t end = std::min(start + num_cols, normalized_text.length());
        result += normalized_text.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::size_t col = 0; col < num_cols; ++col) {
        for (std::size_t row = 0; row < num_rows; ++row) {
            std::size_t index = row * num_cols + col;
            if (index < normalized_text.length()) {
                result += normalized_text[index];
            } else {
                // Add nothing per instructions
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    // First, we need to read down the columns to get the cipher text
    // Then split into chunks of 'num_rows' length, separated by spaces
    // But the example shows padding with spaces to fill the rectangle
    
    // Generate the cipher text by reading down the columns, padding with spaces where necessary
    std::vector<std::string> columns(num_cols);
    for (std::size_t col = 0; col < num_cols; ++col) {
        for (std::size_t row = 0; row < num_rows; ++row) {
            std::size_t index = row * num_cols + col;
            if (index < normalized_text.length()) {
                columns[col] += normalized_text[index];
            } else {
                columns[col] += ' ';
            }
        }
    }
    
    // Now join the columns with spaces
    std::string result;
    for (std::size_t i = 0; i < num_cols; ++i) {
        if (i != 0) {
            result += " ";
        }
        result += columns[i];
    }
    return result;
}

}  // namespace crypto_square

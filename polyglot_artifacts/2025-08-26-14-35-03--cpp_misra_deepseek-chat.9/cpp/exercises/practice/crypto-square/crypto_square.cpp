#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
    
    // Determine number of columns and rows
    const std::size_t length = normalized.length();
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Find c and r that satisfy the conditions
    // Start with r being the integer part of the square root
    num_rows = static_cast<std::size_t>(std::sqrt(length));
    num_cols = num_rows;
    // Adjust to meet conditions
    while (num_cols * num_rows < length) {
        // First try to increase columns
        if (num_cols == num_rows) {
            num_cols++;
        } else {
            num_rows++;
        }
    }
    // Ensure c >= r and c - r <= 1
    // The above loop should ensure this, but let's verify
    if (num_cols < num_rows) {
        std::swap(num_cols, num_rows);
    }
    // Make sure c - r <= 1
    if (num_cols - num_rows > 1) {
        num_rows++;
        num_cols = num_rows;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    if (normalized.empty()) return "";
    
    std::string result;
    for (std::size_t i = 0; i < num_rows; i++) {
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
    if (normalized.empty()) return "";
    
    std::string result;
    for (std::size_t col = 0; col < num_cols; col++) {
        for (std::size_t row = 0; row < num_rows; row++) {
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
    if (ct.empty()) return "";
    
    // Split into num_cols chunks of num_rows length, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < num_cols; i++) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * num_rows, num_rows);
    }
    return result;
}

}  // namespace crypto_square

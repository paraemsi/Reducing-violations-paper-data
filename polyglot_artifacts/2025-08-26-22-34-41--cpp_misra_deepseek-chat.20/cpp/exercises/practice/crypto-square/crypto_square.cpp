#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
    
    const std::size_t length = normalized.length();
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Determine the number of columns and rows
    // Start with the ceiling of the square root
    num_cols = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    num_rows = (length + num_cols - 1) / num_cols; // Ceiling division
    
    // Adjust to meet conditions: c >= r and c - r <= 1
    // If conditions are not met, we need to find the right values
    // Since c is the number of columns and r is the number of rows
    while (num_cols < num_rows || (num_cols - num_rows) > 1) {
        num_cols++;
        num_rows = (length + num_cols - 1) / num_cols;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    if (normalized.empty()) {
        return "";
    }
    
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
    if (normalized.empty()) {
        return "";
    }
    
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
    if (ct.empty()) {
        return "";
    }
    
    // Split into chunks of num_rows length
    std::string result;
    for (std::size_t i = 0; i < ct.length(); i += num_rows) {
        if (!result.empty()) {
            result += " ";
        }
        result += ct.substr(i, num_rows);
    }
    return result;
}

}  // namespace crypto_square

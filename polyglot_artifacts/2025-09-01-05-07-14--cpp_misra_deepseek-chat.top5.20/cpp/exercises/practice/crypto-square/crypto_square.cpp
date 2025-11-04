#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the text
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    
    // Calculate number of columns and rows
    std::uint32_t length = static_cast<std::uint32_t>(normalized_text.size());
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Start with c as the ceiling of the square root of the length
    num_cols = static_cast<std::uint32_t>(std::ceil(std::sqrt(length)));
    num_rows = static_cast<std::uint32_t>(std::ceil(static_cast<double>(length) / num_cols));
    
    // Adjust to meet all conditions
    while (true) {
        if ((num_cols >= num_rows) && 
            ((num_cols - num_rows) <= 1) && 
            ((num_cols * num_rows) >= length)) {
            break;
        }
        // If conditions are not met, increase columns and recalculate rows
        num_cols++;
        num_rows = static_cast<std::uint32_t>(std::ceil(static_cast<double>(length) / num_cols));
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::uint32_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::uint32_t i = 0; i < num_rows; i++) {
        std::uint32_t start = i * num_cols;
        std::uint32_t end = (start + num_cols) < normalized_text.size() ? (start + num_cols) : normalized_text.size();
        result += normalized_text.substr(start, end - start);
        if (i < (num_rows - 1)) {
            result += " ";
        }
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::uint32_t col = 0; col < num_cols; col++) {
        for (std::uint32_t row = 0; row < num_rows; row++) {
            std::uint32_t index = (row * num_cols) + col;
            if (index < normalized_text.size()) {
                result += normalized_text[index];
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
    
    std::string result;
    for (std::uint32_t i = 0; i < num_cols; i++) {
        result += ct.substr(i * num_rows, num_rows);
        if (i < (num_cols - 1)) {
            result += " ";
        }
    }
    return result;
}

}  // namespace crypto_square

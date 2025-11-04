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
    
    // Determine number of columns and rows
    std::size_t length = normalized_text.length();
    if (length == 0) {
        num_columns = 0;
        num_rows = 0;
        return;
    }
    
    // Find c and r that satisfy the conditions
    // Start with c as the ceiling of the square root
    num_columns = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    // Calculate number of rows needed
    num_rows = (length + num_columns - 1) / num_columns;
    
    // Adjust to meet c >= r and c - r <= 1
    // If num_rows > num_columns, we need to set num_columns to num_rows
    // and recalculate num_rows
    if (num_rows > num_columns) {
        num_columns = num_rows;
        num_rows = (length + num_columns - 1) / num_columns;
    }
    // Ensure c - r <= 1
    // If after adjustment, the difference is more than 1, we may need to increase num_columns
    // But according to the conditions, we need to find the smallest c where r * c >= length, c >= r, and c - r <= 1
    // So we can try to find the right values by incrementing c until conditions are satisfied
    // Let's find the smallest c where c >= ceil(sqrt(length)) and r = ceil(length/c) satisfies c >= r and c - r <= 1
    while (true) {
        num_rows = (length + num_columns - 1) / num_columns;
        if (num_columns >= num_rows && (num_columns - num_rows) <= 1) {
            break;
        }
        num_columns++;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    return num_columns;
}

std::string cipher::plain_text_segments() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < num_rows; i++) {
        std::size_t start = i * num_columns;
        std::size_t end = std::min(start + num_columns, normalized_text.length());
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
    for (std::size_t col = 0; col < num_columns; col++) {
        for (std::size_t row = 0; row < num_rows; row++) {
            std::size_t index = row * num_columns + col;
            if (index < normalized_text.length()) {
                result += normalized_text[index];
            } else {
                // Pad with space if necessary
                result += ' ';
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string raw_cipher = this->cipher_text();
    if (raw_cipher.empty()) {
        return "";
    }
    
    // Split into num_columns chunks, each of length num_rows, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < num_columns; i++) {
        result += raw_cipher.substr(i * num_rows, num_rows);
        if (i < (num_columns - 1)) {
            result += " ";
        }
    }
    return result;
}

}  // namespace crypto_square

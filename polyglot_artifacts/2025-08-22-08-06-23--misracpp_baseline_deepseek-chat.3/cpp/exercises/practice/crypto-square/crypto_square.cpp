#include "crypto_square.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>

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

size_t cipher::determine_columns() const {
    size_t length = normalized.length();
    if (length == 0) return 0;
    
    // Find the smallest c where c >= ceil(sqrt(length)), and c >= r, and c - r <= 1
    // where r = ceil(length / c)
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(length)));
    while (true) {
        size_t r = (length + c - 1) / c; // Ceiling division
        if (c >= r && c - r <= 1) {
            break;
        }
        c++;
    }
    return c;
}

std::vector<std::string> cipher::plain_text_segments() const {
    size_t c = determine_columns();
    if (c == 0) return {};
    
    size_t length = normalized.length();
    std::vector<std::string> segments;
    
    for (size_t i = 0; i < length; i += c) {
        segments.push_back(normalized.substr(i, c));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    // The encoded text is obtained by reading down the columns, without any spaces
    // So we need to read column-wise, and only add characters that exist
    size_t length = normalized.length();
    if (length == 0) return "";
    
    size_t c = determine_columns();
    size_t r = (length + c - 1) / c; // Ceiling division to get number of rows
    
    std::string result;
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            size_t index = row * c + col;
            if (index < length) {
                result += normalized[index];
            }
            // No padding for cipher_text
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    size_t length = normalized.length();
    if (length == 0) return "";
    
    size_t c = determine_columns();
    size_t r = (length + c - 1) / c; // Number of rows
    
    // Prepare each column as a string
    std::vector<std::string> columns(c);
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            size_t index = row * c + col;
            if (index < length) {
                columns[col] += normalized[index];
            } else {
                columns[col] += ' '; // Add padding
            }
        }
    }
    
    // Join the columns with spaces
    std::string result;
    for (size_t i = 0; i < columns.size(); i++) {
        if (i != 0) {
            result += " ";
        }
        result += columns[i];
    }
    return result;
}

}  // namespace crypto_square

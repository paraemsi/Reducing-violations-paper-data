#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    if (normalized_text.empty()) {
        return 0;
    }
    std::size_t length = normalized_text.size();
    // Start from the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    while (true) {
        std::size_t r = (length + c - 1) / c; // Ceiling division
        if (c >= r && (c - r) <= 1) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < normalized_text.size(); i += c) {
        if (i != 0) {
            result += " ";
        }
        result += normalized_text.substr(i, c);
    }
    return result;
}

std::string cipher::cipher_text() const {
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Build the encoded text by reading down the columns
    std::string encoded;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t index = (row * c) + col;
            if (index < length) {
                encoded += normalized_text[index];
            }
            // No padding for cipher_text()
        }
    }
    return encoded;
}

std::string cipher::normalized_cipher_text() const {
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Build the encoded text by reading down the columns, padding with spaces where necessary
    std::vector<std::string> columns(c);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t index = (row * c) + col;
            if (index < length) {
                columns[col] += normalized_text[index];
            } else {
                columns[col] += ' ';
            }
        }
    }
    
    // Join the columns with spaces
    std::string result;
    for (std::size_t i = 0; i < columns.size(); ++i) {
        if (i != 0) {
            result += " ";
        }
        result += columns[i];
    }
    return result;
}

}  // namespace crypto_square

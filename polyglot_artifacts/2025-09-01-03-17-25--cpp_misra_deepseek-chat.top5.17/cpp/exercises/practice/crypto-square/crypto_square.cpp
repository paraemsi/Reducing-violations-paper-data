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
    const std::size_t length = normalized_text.size();
    if (length == 0) {
        return 0;
    }
    
    // Find the smallest c that satisfies the conditions
    std::size_t c = 0;
    for (std::size_t potential_c = 1; potential_c <= length; potential_c++) {
        const std::size_t r = (length + potential_c - 1) / potential_c; // Ceiling division
        if (potential_c >= r && (potential_c - r) <= 1) {
            c = potential_c;
            break;
        }
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t length = normalized_text.size();
    // Number of rows
    const std::size_t r = (length + c - 1) / c; // Ceiling division
    
    std::string result;
    for (std::size_t i = 0; i < r; i++) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * c;
        std::size_t end = std::min((i + 1) * c, length);
        result += normalized_text.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t length = normalized_text.size();
    // Number of rows
    const std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Read down the columns, handling potential missing characters
    std::string result;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            const std::size_t index = row * c + col;
            if (index < length) {
                result += normalized_text[index];
            } else {
                // No padding for cipher_text()
                // According to the instructions, cipher_text() should not have spaces
                // But the example shows padding with spaces in the grid
                // The problem says to pad with spaces only in the last n chunks of normalized_cipher_text
                // So for cipher_text(), we don't add anything
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t length = normalized_text.size();
    // Number of rows
    const std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Read down the columns, padding with spaces where necessary
    std::vector<std::string> columns(c);
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            const std::size_t index = row * c + col;
            if (index < length) {
                columns[col] += normalized_text[index];
            } else {
                columns[col] += ' ';
            }
        }
    }
    
    // Join the columns with spaces
    std::string result;
    for (std::size_t i = 0; i < c; i++) {
        if (i != 0) {
            result += " ";
        }
        result += columns[i];
    }
    return result;
}

}  // namespace crypto_square

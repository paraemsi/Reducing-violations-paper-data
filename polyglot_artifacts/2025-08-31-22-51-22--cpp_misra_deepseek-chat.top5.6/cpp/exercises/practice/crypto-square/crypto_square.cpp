#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized.push_back(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) {
        return 0;
    }
    const std::size_t length = normalized.size();
    // Find the smallest c that satisfies the conditions
    std::size_t c = 0;
    std::size_t r = 0;
    for (std::size_t temp_c = 1; temp_c <= length; ++temp_c) {
        std::size_t temp_r = (length + temp_c - 1) / temp_c; // Ceiling division
        if (temp_c >= temp_r && (temp_c - temp_r) <= 1) {
            if (temp_c * temp_r >= length) {
                c = temp_c;
                r = temp_r;
                break;
            }
        }
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) {
        return "";
    }
    const std::size_t length = normalized.size();
    // Determine number of columns and rows
    std::size_t c = size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Pad the text with spaces
    std::string padded = normalized;
    padded.append(r * c - length, ' ');
    
    // Build the encoded text by reading down the columns
    std::vector<std::string> columns(c);
    for (std::size_t i = 0; i < c; ++i) {
        for (std::size_t j = 0; j < r; ++j) {
            columns[i].push_back(padded[j * c + i]);
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

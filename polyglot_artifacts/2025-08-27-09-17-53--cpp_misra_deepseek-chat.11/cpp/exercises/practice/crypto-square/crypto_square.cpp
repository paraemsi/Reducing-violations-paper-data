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
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) return 0;
    std::size_t n = normalized.size();
    // Start with the smallest possible c which is at least the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(n)));
    while (true) {
        // Calculate number of rows
        std::size_t r = (n + c - 1) / c; // This is ceiling(n/c)
        // Check conditions
        if (c >= r && (c - r) <= 1) {
            break;
        }
        ++c;
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    
    std::size_t n = normalized.size();
    std::size_t c = size();
    std::size_t r = (n + c - 1) / c; // Ceiling division
    
    // Build the encoded text by reading down the columns
    std::vector<std::string> chunks(c);
    for (std::size_t i = 0; i < c; ++i) {
        for (std::size_t j = 0; j < r; ++j) {
            std::size_t index = j * c + i;
            if (index < n) {
                chunks[i] += normalized[index];
            } else {
                chunks[i] += ' ';
            }
        }
    }
    
    // Join the chunks with spaces
    std::string result;
    for (std::size_t i = 0; i < c; ++i) {
        if (i != 0) {
            result += ' ';
        }
        result += chunks[i];
    }
    return result;
}

}  // namespace crypto_square

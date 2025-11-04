#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += std::tolower(static_cast<unsigned char>(ch));
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
    // Determine the number of columns (c)
    const std::size_t length = normalized_text.size();
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    // We need to find c where c >= r and c - r <= 1, and r * c >= length
    // Since r is ceiling(length / c), we can compute r and adjust if necessary
    std::size_t r = (length + c - 1) / c; // This is ceiling(length / c)
    // Check if conditions are satisfied
    if ((c >= r) && ((c - r) <= 1)) {
        return c;
    } else {
        // Adjust to find the correct c
        // Since c is the ceiling of sqrt(length), and we need to find the smallest c that satisfies the conditions
        // Let's find the next integer that satisfies the conditions
        // For now, we can use a simple approach to find c
        // This may need to be optimized
        for (c = static_cast<std::size_t>(std::ceil(std::sqrt(length))); ; ++c) {
            r = (length + c - 1) / c;
            if ((c >= r) && ((c - r) <= 1)) {
                break;
            }
        }
        return c;
    }
}

std::string cipher::plain_text_segments() const {
    const std::size_t c = size();
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
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t r = (normalized_text.size() + c - 1) / c; // ceiling(normalized_text.size() / c)
    
    // Build the encoded text by reading down the columns
    std::string encoded;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t index = (row * c) + col;
            if (index < normalized_text.size()) {
                encoded += normalized_text[index];
            } else {
                // Pad with space if necessary
                encoded += ' ';
            }
        }
    }
    return encoded;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t r = (normalized_text.size() + c - 1) / c;
    
    // Get the cipher text which is c * r characters long
    std::string ct = cipher_text();
    
    // Split into c chunks of length r, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < c; ++i) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

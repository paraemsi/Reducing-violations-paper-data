#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

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
    std::size_t length = normalized_text.size();
    // Find the smallest c where c >= r, c - r <= 1, and r * c >= length
    // Start with c as the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r = (length + c - 1) / c; // Ceiling of length / c
    
    // Adjust to meet conditions
    while (true) {
        if ((c >= r) && ((c - r) <= 1) && (c * r >= length)) {
            break;
        }
        // We need to find the right dimensions
        // Let's try increasing c until conditions are met
        c++;
        r = (length + c - 1) / c;
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    std::string normalized = normalize_plain_text();
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::string result;
    for (std::size_t i = 0; i < normalized.size(); i += c) {
        if (i != 0) {
            result += " ";
        }
        result += normalized.substr(i, c);
    }
    return result;
}

std::string cipher::cipher_text() const {
    std::string normalized = normalize_plain_text();
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t r = (normalized.size() + c - 1) / c; // Ceiling division
    
    // Build the encoded text by reading down the columns
    std::string encoded;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t index = row * c + col;
            if (index < normalized.size()) {
                encoded += normalized[index];
            }
            // No padding for cipher_text
        }
    }
    return encoded;
}

std::string cipher::normalized_cipher_text() const {
    std::string normalized = normalize_plain_text();
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t r = (normalized.size() + c - 1) / c; // Ceiling division
    
    // Build a grid with padding
    std::vector<std::string> grid(r);
    for (std::size_t i = 0; i < r; ++i) {
        std::size_t start = i * c;
        std::size_t end = std::min(start + c, normalized.size());
        grid[i] = normalized.substr(start, end - start);
        // Pad with spaces if necessary
        grid[i].resize(c, ' ');
    }
    
    // Read down the columns
    std::string result;
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) {
            result += " ";
        }
        for (std::size_t row = 0; row < r; ++row) {
            result += grid[row][col];
        }
    }
    return result;
}

}  // namespace crypto_square

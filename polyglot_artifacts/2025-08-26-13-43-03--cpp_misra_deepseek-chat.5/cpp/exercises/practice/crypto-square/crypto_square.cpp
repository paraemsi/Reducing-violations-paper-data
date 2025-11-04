#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized_text += std::tolower(static_cast<unsigned char>(c));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    if (normalized_text.empty()) return 0;
    
    std::size_t length = normalized_text.size();
    // Start with the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Adjust until conditions are met
    while (true) {
        if ((c >= r) && ((c - r) <= 1) && (c * r >= length)) {
            break;
        }
        c++;
        r = (length + c - 1) / c;
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    // This may not be needed, but let's implement it to organize into rows
    std::size_t c = size();
    if (c == 0) return "";
    
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    std::string result;
    for (std::size_t i = 0; i < r; i++) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * c;
        std::size_t end = std::min(start + c, length);
        result += normalized_text.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    // Read down the columns to get the encoded text without spaces
    std::size_t c = size();
    if (c == 0) return "";
    
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    std::string encoded;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            std::size_t index = row * c + col;
            if (index < length) {
                encoded += normalized_text[index];
            } else {
                encoded += ' '; // Padding
            }
        }
    }
    return encoded;
}

std::string cipher::normalized_cipher_text() const {
    // This should return the cipher text formatted with spaces between groups
    std::string ct = cipher_text();
    std::size_t c = size();
    if (c == 0) return "";
    
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Split into c chunks of r characters each
    std::string result;
    for (std::size_t i = 0; i < c; i++) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

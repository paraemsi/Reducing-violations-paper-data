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
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Adjust to make sure c >= r and c - r <= 1
    // Since c is the ceiling of the square root, and r is ceiling(length/c), we need to find the right values
    // Let's find the smallest c where c >= ceil(length/c) and c - ceil(length/c) <= 1
    while (true) {
        r = (length + c - 1) / c;
        if ((c >= r) && ((c - r) <= 1)) {
            break;
        }
        c++;
    }
    return c;
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
    const std::size_t length = normalized_text.size();
    // Calculate number of rows
    const std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Build the encoded text by reading down the columns
    std::string encoded;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t index = (row * c) + col;
            if (index < length) {
                encoded += normalized_text[index];
            } else {
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
    const std::size_t length = normalized_text.size();
    const std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // The encoded text from cipher_text() is c * r characters long
    // We need to split it into c chunks, each of length r
    const std::string encoded = cipher_text();
    
    // Split into c chunks of length r
    std::string result;
    for (std::size_t i = 0; i < c; ++i) {
        if (i != 0) {
            result += " ";
        }
        result += encoded.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

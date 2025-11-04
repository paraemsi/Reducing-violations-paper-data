#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
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
    // Find the smallest c where c >= r, c - r <= 1, and r * c >= length
    // Since r = ceil(length / c), we can find c by checking values
    std::size_t c = 0;
    while (true) {
        c++;
        std::size_t r = (length + c - 1) / c; // This is ceiling(length / c)
        if (c >= r && (c - r) <= 1) {
            break;
        }
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
    
    // Pad with spaces to fill the rectangle
    std::string padded = normalized_text;
    padded.append(r * c - length, ' ');
    
    // Read down the columns to get the cipher text
    std::string result;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            result += padded[row * c + col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    // The number of rows is the length of ct divided by c
    // Since we padded to make a perfect rectangle, ct.length() should be r * c
    std::size_t r = ct.size() / c;
    
    // Split into c chunks of r length each, separated by spaces
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

#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
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
    std::size_t n = normalized.size();
    // Start with c as the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    while (true) {
        std::size_t r = (n + c - 1) / c; // Ceiling division
        if (c >= r && (c - r) <= 1) {
            break;
        }
        ++c;
    }
    return c;
}

std::string cipher::plain_text_segments() const {
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
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t n = normalized.size();
    std::size_t r = (n + c - 1) / c; // Number of rows
    
    std::string result;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t index = row * c + col;
            if (index < n) {
                result += normalized[index];
            } else {
                result += ' ';
            }
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
    std::size_t n = normalized.size();
    std::size_t r = (n + c - 1) / c; // Number of rows
    
    // The cipher text is organized in c columns of r length each when read down the columns
    // So to format it, we need to split into c chunks of r length
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

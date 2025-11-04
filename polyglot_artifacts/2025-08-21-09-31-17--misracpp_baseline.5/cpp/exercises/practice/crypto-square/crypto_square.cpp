#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>

namespace crypto_square {

static std::string normalize(const std::string& text) {
    std::string result;
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)) {}

std::string cipher::normalized_cipher_text() const {
    size_t len = normalized_.size();
    if (len == 0) return "";

    // Find r and c
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (r * c < len) ++r;
    if (c < r) std::swap(c, r);

    // Pad the normalized text to fit the rectangle
    size_t padded_len = r * c;
    std::string padded = normalized_ + std::string(padded_len - len, ' ');

    // Read down the columns
    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            chunk += padded[row * c + col];
        }
        chunks.push_back(chunk);
    }

    // Join with spaces
    std::string result;
    for (size_t i = 0; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1 < chunks.size()) result += " ";
    }
    return result;
}

}  // namespace crypto_square

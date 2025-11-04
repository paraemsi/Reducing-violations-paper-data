#include "crypto_square.h"
#include <cctype>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

static std::string normalize(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            result += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return result;
}

cipher_result::cipher_result(const std::string& text) {
    normalized_ = normalize(text);

    size_t len = normalized_.size();
    if (len == 0) {
        encoded_ = "";
        return;
    }

    // Find r and c
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (r * c < len) ++r;
    if (c < r) std::swap(c, r);

    // Pad the normalized string to fit the rectangle
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
    encoded_.clear();
    for (size_t i = 0; i < chunks.size(); ++i) {
        encoded_ += chunks[i];
        if (i + 1 < chunks.size()) encoded_ += " ";
    }
}

std::string cipher_result::normalized_cipher_text() const {
    return normalized_;
}

std::string cipher_result::cipher_text() const {
    return encoded_;
}

cipher_result cipher(const std::string& text) {
    return cipher_result(text);
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {

static std::string normalize(const std::string& text) {
    std::string normalized;
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return normalized;
}

cipher_result::cipher_result(const std::string& text) {
    normalized_ = normalize(text);

    size_t len = normalized_.size();
    if (len == 0) {
        ciphered_ = "";
        return;
    }

    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::ceil(static_cast<double>(len) / c));

    std::string padded = normalized_;
    padded.resize(r * c, ' ');

    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            chunk += padded[row * c + col];
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    ciphered_.clear();
    for (size_t i = 0; i < chunks.size(); ++i) {
        ciphered_ += chunks[i];
        if (i + 1 < chunks.size()) ciphered_ += " ";
    }
}

std::string cipher_result::normalized_cipher_text() const {
    return normalized_;
}

std::string cipher_result::ciphertext() const {
    return ciphered_;
}

cipher_result cipher(const std::string& text) {
    return cipher_result(text);
}

}  // namespace crypto_square

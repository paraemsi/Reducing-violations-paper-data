#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize: remove non-alphanum, to lower
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized_ += std::tolower(static_cast<unsigned char>(c));
        }
    }
}

std::string cipher::normalized_cipher_text() const {
    size_t len = normalized_.size();
    if (len == 0) return "";

    // Determine rectangle size
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::ceil(static_cast<double>(len) / c));
    if (c < r) std::swap(c, r);

    // Pad normalized text to fit rectangle
    std::string padded = normalized_;
    size_t padded_len = r * c;
    padded.append(padded_len - len, ' ');

    // Read down columns to encode
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

#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize: remove non-alphanum, tolower
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_ += std::tolower(static_cast<unsigned char>(ch));
        }
    }

    size_t len = normalized_.size();
    if (len == 0) {
        rows_ = cols_ = 0;
        return;
    }

    cols_ = static_cast<size_t>(std::ceil(std::sqrt(len)));
    rows_ = cols_;
    if ((cols_ - 1) * cols_ >= len) {
        rows_ = cols_ - 1;
    }
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) return "";

    // Pad normalized text to fill rectangle
    std::string padded = normalized_;
    size_t padded_len = rows_ * cols_;
    padded.append(padded_len - normalized_.size(), ' ');

    // Read down columns, left to right, to form c chunks of r length
    std::vector<std::string> chunks;
    for (size_t col = 0; col < cols_; ++col) {
        std::string chunk;
        for (size_t row = 0; row < rows_; ++row) {
            chunk += padded[row * cols_ + col];
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    std::string result;
    for (size_t i = 0; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1 < chunks.size()) result += " ";
    }
    return result;
}

}  // namespace crypto_square

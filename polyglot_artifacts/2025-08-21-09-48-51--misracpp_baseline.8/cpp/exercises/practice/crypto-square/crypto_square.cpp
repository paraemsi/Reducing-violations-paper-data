#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize input: remove non-alphanum, to lower
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

    // Determine rectangle size: c >= r, c - r <= 1, r * c >= len
    cols_ = static_cast<size_t>(std::ceil(std::sqrt(len)));
    rows_ = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (rows_ * cols_ < len) ++rows_;
    if (cols_ < rows_) std::swap(cols_, rows_);
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) return "";

    // Pad normalized string to fit rectangle
    std::string padded = normalized_;
    size_t padded_len = rows_ * cols_;
    if (padded.size() < padded_len) {
        padded.append(padded_len - padded.size(), ' ');
    }

    // Read down the columns to encode
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

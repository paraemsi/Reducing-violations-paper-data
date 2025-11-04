#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>

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

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)) {
    build_rectangle();
}

void cipher::build_rectangle() {
    size_t len = normalized_.size();
    if (len == 0) {
        rows_ = cols_ = 0;
        return;
    }
    cols_ = static_cast<size_t>(std::ceil(std::sqrt(len)));
    rows_ = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (rows_ * cols_ < len) ++rows_;
    if (cols_ < rows_) std::swap(cols_, rows_);

    // Pad the normalized text to fit the rectangle
    size_t padded_len = rows_ * cols_;
    std::string padded = normalized_ + std::string(padded_len - len, ' ');

    rectangle_.clear();
    for (size_t row = 0; row < rows_; ++row) {
        rectangle_.push_back(padded.substr(row * cols_, cols_));
    }
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) return "";

    std::vector<std::string> chunks;
    for (size_t col = 0; col < cols_; ++col) {
        std::string chunk;
        for (size_t row = 0; row < rows_; ++row) {
            chunk += rectangle_[row][col];
        }
        chunks.push_back(chunk);
    }

    std::string result;
    for (size_t i = 0; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1 < chunks.size()) result += " ";
    }
    return result;
}

}  // namespace crypto_square

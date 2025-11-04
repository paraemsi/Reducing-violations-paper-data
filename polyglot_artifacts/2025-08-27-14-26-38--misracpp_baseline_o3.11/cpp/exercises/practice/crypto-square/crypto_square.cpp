#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>

namespace crypto_square {


cipher::cipher(const std::string& text) {
    // Normalize: keep alphanumeric characters and convert to lowercase.
    normalized_.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    const std::size_t len = normalized_.size();
    if (len == 0) {
        rows_ = cols_ = 0;
        return;
    }

    // Determine rectangle dimensions.
    rows_ = static_cast<std::size_t>(
        std::floor(std::sqrt(static_cast<double>(len))));
    cols_ = static_cast<std::size_t>(
        std::ceil(std::sqrt(static_cast<double>(len))));
    if (rows_ * cols_ < len) {
        ++rows_;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::string cipher::cipher_text() const {
    std::string result;
    const std::size_t len = normalized_.size();
    result.reserve(len);
    for (std::size_t col = 0; col < cols_; ++col) {
        for (std::size_t row = 0; row < rows_; ++row) {
            const std::size_t idx = row * cols_ + col;
            if (idx < len) {
                result.push_back(normalized_[idx]);
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) {
        return "";
    }

    std::string result;
    const std::size_t len = normalized_.size();
    result.reserve(len + cols_);  // account for spaces

    for (std::size_t col = 0; col < cols_; ++col) {
        if (col != 0) {
            result.push_back(' ');
        }
        for (std::size_t row = 0; row < rows_; ++row) {
            const std::size_t idx = row * cols_ + col;
            if (idx < len) {
                result.push_back(normalized_[idx]);
            } else {
                result.push_back(' ');
            }
        }
    }
    return result;
}

}  // namespace crypto_square

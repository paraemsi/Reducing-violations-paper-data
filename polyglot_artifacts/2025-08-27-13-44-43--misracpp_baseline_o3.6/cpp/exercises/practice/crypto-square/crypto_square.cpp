#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

static std::string normalize(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            result.push_back(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

/*----  crypto_square::cipher method definitions  ----*/

cipher::cipher(std::string text) : normalized_(normalize(text)) {
    const std::size_t len = normalized_.size();
    if (len == 0) {
        rows_ = cols_ = 0;
        return;
    }
    cols_ = static_cast<std::size_t>(std::ceil(std::sqrt(len)));
    rows_ = static_cast<std::size_t>(std::ceil(static_cast<double>(len) / cols_));
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    if (normalized_.empty()) {
        return segments;
    }
    segments.reserve(rows_);
    for (std::size_t i = 0; i < normalized_.size(); i += cols_) {
        segments.emplace_back(normalized_.substr(i, std::min(cols_, normalized_.size() - i)));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_.empty()) {
        return "";
    }
    std::string result;
    result.reserve(normalized_.size());
    for (std::size_t col = 0; col < cols_; ++col) {
        for (std::size_t row = 0; row < rows_; ++row) {
            const std::size_t idx = row * cols_ + col;
            if (idx < normalized_.size()) {
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
    // Build space-padded chunks column-wise. Each chunk contains `rows_`
    // characters, padding with spaces where the rectangle cell is empty.
    for (std::size_t col = 0; col < cols_; ++col) {
        if (col > 0) {
            result.push_back(' ');
        }
        for (std::size_t row = 0; row < rows_; ++row) {
            const std::size_t idx = row * cols_ + col;
            if (idx < normalized_.size()) {
                result.push_back(normalized_[idx]);
            } else {
                result.push_back(' ');
            }
        }
    }
    return result;
}

}  // namespace crypto_square

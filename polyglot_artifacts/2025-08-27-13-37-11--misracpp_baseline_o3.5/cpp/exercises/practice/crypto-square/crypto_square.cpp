#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

std::string normalize_text(std::string_view text) {
    std::string out;
    out.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            out.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

static std::size_t square_size(std::size_t text_length) {
    return static_cast<std::size_t>(
        std::ceil(std::sqrt(static_cast<double>(text_length))));
}

std::size_t square_size(std::string_view text) {
    return square_size(normalize_text(text).size());
}

std::vector<std::string> plain_text_segments(std::string_view text) {
    const std::string normalized = normalize_text(text);
    const std::size_t cols = square_size(text);

    std::vector<std::string> segments;
    for (std::size_t i = 0; i < normalized.size(); i += cols) {
        segments.push_back(normalized.substr(i, cols));
    }
    return segments;
}

std::string cipher_text(std::string_view text) {
    const std::string normalized = normalize_text(text);
    if (normalized.empty()) {
        return {};
    }

    const std::size_t cols = square_size(text);
    const std::size_t rows = (normalized.size() + cols - 1) / cols;

    // Build the grid (plain-text segments)
    std::vector<std::string> segments;
    segments.reserve(rows);
    for (std::size_t i = 0; i < normalized.size(); i += cols) {
        segments.push_back(normalized.substr(i, cols));
    }

    // Read column-wise producing the cipher text
    std::ostringstream oss;
    for (std::size_t c = 0; c < cols; ++c) {
        if (c != 0) {
            oss << ' ';
        }
        for (std::size_t r = 0; r < rows; ++r) {
            if (c < segments[r].size()) {
                oss << segments[r][c];
            } else {
                oss << ' ';
            }
        }
    }

    return oss.str();
}

// ------------------------------------------------------------------
//                 crypto_square::cipher implementation
// ------------------------------------------------------------------

cipher::cipher(std::string_view text)
    : normalized_{normalize_text(text)} {
    if (!normalized_.empty()) {
        columns_ = static_cast<std::size_t>(
            std::ceil(std::sqrt(static_cast<double>(normalized_.size()))));
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::size_t cipher::size() const {
    return columns_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    if (normalized_.empty()) {
        return {};
    }

    std::vector<std::string> segments;
    for (std::size_t i = 0; i < normalized_.size(); i += columns_) {
        segments.push_back(normalized_.substr(i, columns_));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_.empty()) {
        return {};
    }

    const std::size_t rows = (normalized_.size() + columns_ - 1) / columns_;
    std::ostringstream oss;

    for (std::size_t c = 0; c < columns_; ++c) {
        for (std::size_t r = 0; r < rows; ++r) {
            const std::size_t idx = r * columns_ + c;
            if (idx < normalized_.size()) {
                oss << normalized_[idx];
            }
        }
    }
    return oss.str();
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::cipher_text(normalized_);
}

}  // namespace crypto_square

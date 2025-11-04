#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>

namespace crypto_square {


cipher::cipher(const std::string& input) {
    // Normalize input: keep alphanumerics, convert to lowercase
    normalized_.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    const std::size_t n = normalized_.size();
    if (n == 0) {
        rows_ = cols_ = 0;
        return;
    }

    const double root = std::sqrt(static_cast<double>(n));
    rows_ = static_cast<std::size_t>(std::floor(root));
    cols_ = static_cast<std::size_t>(std::ceil(root));
    if (rows_ * cols_ < n) {
        ++rows_;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    if (normalized_.empty()) {
        return segments;
    }

    for (std::size_t pos = 0; pos < normalized_.size(); pos += cols_) {
        segments.emplace_back(
            normalized_.substr(pos, std::min(cols_, normalized_.size() - pos)));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_.empty()) {
        return "";
    }

    std::string result;
    result.reserve(normalized_.size());
    for (std::size_t c = 0; c < cols_; ++c) {
        for (std::size_t r = 0; r < rows_; ++r) {
            std::size_t idx = r * cols_ + c;
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

    std::ostringstream oss;
    for (std::size_t c = 0; c < cols_; ++c) {
        if (c != 0) {
            oss << ' ';
        }
        for (std::size_t r = 0; r < rows_; ++r) {
            std::size_t idx = r * cols_ + c;
            if (idx < normalized_.size()) {
                oss << normalized_[idx];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

std::string encode(const std::string& input) {
    return cipher(input).normalized_cipher_text();
}

}  // namespace crypto_square

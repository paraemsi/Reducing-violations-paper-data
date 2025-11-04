#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) : rows_(0), cols_(0) {
    normalized_.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            normalized_.push_back(static_cast<char>(std::tolower(ch)));
        }
    }

    const std::size_t n = normalized_.size();
    if (n == 0) {
        rows_ = cols_ = 0;
    } else {
        std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
        std::size_t r = (n + c - 1) / c; // ceil(n / c)
        cols_ = c;
        rows_ = r;
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
    for (std::size_t i = 0; i < normalized_.size(); i += cols_) {
        segments.push_back(normalized_.substr(i, std::min(cols_, normalized_.size() - i)));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_.empty()) {
        return {};
    }
    std::string out;
    out.reserve(normalized_.size());
    const std::size_t n = normalized_.size();

    for (std::size_t x = 0; x < cols_; ++x) {
        for (std::size_t y = 0; y < rows_; ++y) {
            const std::size_t idx = y * cols_ + x;
            if (idx < n) {
                out.push_back(normalized_[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) {
        return {};
    }
    std::ostringstream oss;
    const std::size_t n = normalized_.size();

    for (std::size_t x = 0; x < cols_; ++x) {
        if (x != 0) {
            oss << ' ';
        }
        for (std::size_t y = 0; y < rows_; ++y) {
            const std::size_t idx = y * cols_ + x;
            if (idx < n) {
                oss << normalized_[idx];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

}  // namespace crypto_square

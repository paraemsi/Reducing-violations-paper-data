#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    normalized_.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            normalized_.push_back(static_cast<char>(std::tolower(ch)));
        }
    }

    const std::size_t L = normalized_.size();
    if (L == 0) {
        rows_ = cols_ = 0;
        return;
    }

    const double root = std::sqrt(static_cast<double>(L));
    rows_ = static_cast<std::size_t>(std::floor(root));
    cols_ = static_cast<std::size_t>(std::ceil(root));
    if (rows_ * cols_ < L) {
        ++rows_;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plaintext_segments() const {
    std::vector<std::string> segments;
    if (normalized_.empty()) {
        return segments;
    }

    segments.reserve(rows_);
    for (std::size_t r = 0; r < rows_; ++r) {
        const std::size_t start = r * cols_;
        if (start >= normalized_.size()) {
            segments.emplace_back("");
        } else {
            const std::size_t len = std::min(cols_, normalized_.size() - start);
            segments.emplace_back(normalized_.substr(start, len));
        }
    }
    return segments;
}

std::string cipher::ciphertext() const {
    if (normalized_.empty()) {
        return {};
    }

    std::string out;
    out.reserve(normalized_.size());

    const std::size_t L = normalized_.size();
    for (std::size_t c = 0; c < cols_; ++c) {
        for (std::size_t r = 0; r < rows_; ++r) {
            const std::size_t idx = r * cols_ + c;
            if (idx < L) {
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
    const std::size_t L = normalized_.size();
    for (std::size_t c = 0; c < cols_; ++c) {
        if (c > 0) {
            oss.put(' ');
        }
        for (std::size_t r = 0; r < rows_; ++r) {
            const std::size_t idx = r * cols_ + c;
            if (idx < L) {
                oss.put(normalized_[idx]);
            } else {
                oss.put(' ');
            }
        }
    }
    return oss.str();
}

}  // namespace crypto_square

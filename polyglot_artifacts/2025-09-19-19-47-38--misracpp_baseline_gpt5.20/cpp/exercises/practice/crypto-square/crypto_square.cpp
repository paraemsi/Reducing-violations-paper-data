#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

// Normalize, segment, and encode per the "square code" cipher.
namespace crypto_square {

static std::string normalize(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (unsigned char ch : input) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

cipher::cipher(const std::string& text)
    : normalized_{normalize(text)} {
    const std::size_t L = normalized_.size();
    if (L == 0) {
        rows_ = cols_ = 0;
        return;
    }
    const double root = std::sqrt(static_cast<double>(L));
    cols_ = static_cast<std::size_t>(std::ceil(root));
    rows_ = (L + cols_ - 1) / cols_;
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    if (cols_ == 0) {
        return segments;
    }
    const std::size_t L = normalized_.size();
    segments.reserve((L + cols_ - 1) / cols_);
    for (std::size_t i = 0; i < L; i += cols_) {
        segments.emplace_back(normalized_.substr(i, std::min(cols_, L - i)));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const std::size_t L = normalized_.size();
    if (L == 0) return {};
    std::string out;
    out.reserve(L);
    for (std::size_t c = 0; c < cols_; ++c) {
        for (std::size_t r = 0; r < rows_; ++r) {
            std::size_t idx = r * cols_ + c;
            if (idx < L) {
                out.push_back(normalized_[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t L = normalized_.size();
    if (L == 0 || cols_ == 0) return {};
    std::string out;
    // Each chunk has length rows_, and there are cols_ chunks separated by spaces.
    // Precompute size: cols_ * rows_ + (cols_ - 1) spaces
    out.reserve(cols_ * rows_ + (cols_ - 1));
    for (std::size_t c = 0; c < cols_; ++c) {
        if (c != 0) out.push_back(' ');
        for (std::size_t r = 0; r < rows_; ++r) {
            std::size_t idx = r * cols_ + c;
            if (idx < L) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square

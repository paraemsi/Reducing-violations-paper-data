#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) : normalized_() {
    normalized_.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            normalized_.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::pair<std::size_t, std::size_t> cipher::dimensions() const {
    const std::size_t L = normalized_.size();
    if (L == 0) {
        return {0, 0};
    }
    const double root = std::sqrt(static_cast<double>(L));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < L) {
        r = c;
    }
    return {r, c};
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    auto [r, c] = dimensions();
    if (c == 0) {
        return segments;
    }
    segments.reserve(r);
    const std::size_t L = normalized_.size();
    for (std::size_t i = 0; i < r; ++i) {
        const std::size_t start = i * c;
        if (start >= L) {
            segments.emplace_back();
        } else {
            const std::size_t len = std::min(c, L - start);
            segments.push_back(normalized_.substr(start, len));
        }
    }
    return segments;
}

std::string cipher::cipher_text() const {
    auto [r, c] = dimensions();
    if (c == 0) {
        return {};
    }
    const std::size_t L = normalized_.size();
    std::string out;
    out.reserve(L);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < L) {
                out.push_back(normalized_[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    auto [r, c] = dimensions();
    if (c == 0) {
        return {};
    }
    const std::size_t L = normalized_.size();
    std::string out;
    out.reserve(c * r + (c - 1));
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) {
            out.push_back(' ');
        }
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
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

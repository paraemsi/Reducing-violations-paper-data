#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <string>
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

std::size_t cipher::size() const {
    const std::size_t L = normalized_.size();
    if (L == 0) {
        return 0;
    }
    return static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(L))));
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    const std::size_t L = normalized_.size();
    const std::size_t c = size();
    if (c == 0) {
        return segments;
    }
    segments.reserve((L + c - 1) / c);
    for (std::size_t i = 0; i < L; i += c) {
        segments.emplace_back(normalized_.substr(i, std::min(c, L - i)));
    }
    return segments;
}

std::string cipher::ciphertext() const {
    const std::size_t L = normalized_.size();
    const std::size_t c = size();
    if (c == 0) {
        return {};
    }
    const std::size_t r = (L + c - 1) / c;

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
    const std::size_t L = normalized_.size();
    const std::size_t c = size();
    if (c == 0) {
        return {};
    }
    const std::size_t r = (L + c - 1) / c;

    std::string out;
    // total length: c chunks of length r, plus (c - 1) spaces between chunks
    out.reserve(c * r + (c ? c - 1 : 0));

    for (std::size_t col = 0; col < c; ++col) {
        if (col > 0) {
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

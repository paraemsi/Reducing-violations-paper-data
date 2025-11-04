#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

static inline bool is_alnum(unsigned char ch) {
    return std::isalnum(ch) != 0;
}

cipher::cipher(const std::string& text) {
    normalized_.reserve(text.size());
    for (unsigned char ch : text) {
        if (is_alnum(ch)) {
            normalized_.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::size_t cipher::rows() const {
    const std::size_t n = normalized_.size();
    if (n == 0) return 0;
    const double root = std::sqrt(static_cast<double>(n));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < n) {
        r = c;
    }
    return r;
}

std::size_t cipher::cols() const {
    const std::size_t n = normalized_.size();
    if (n == 0) return 0;
    const double root = std::sqrt(static_cast<double>(n));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < n) {
        r = c;
    }
    return c;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    const std::size_t n = normalized_.size();
    const std::size_t c = cols();
    if (n == 0 || c == 0) {
        return segments;
    }
    segments.reserve((n + c - 1) / c);
    for (std::size_t i = 0; i < n; i += c) {
        segments.emplace_back(normalized_.substr(i, std::min(c, n - i)));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const std::size_t n = normalized_.size();
    const std::size_t r = rows();
    const std::size_t c = cols();
    if (n == 0 || c == 0 || r == 0) {
        return {};
    }
    std::string out;
    out.reserve(n);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(normalized_[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t n = normalized_.size();
    const std::size_t r = rows();
    const std::size_t c = cols();
    if (n == 0 || c == 0 || r == 0) {
        return {};
    }

    std::string out;
    // Each of the c chunks has length r, plus (c-1) spaces between chunks.
    out.reserve(c * r + (c > 0 ? (c - 1) : 0));

    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) out.push_back(' ');
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square

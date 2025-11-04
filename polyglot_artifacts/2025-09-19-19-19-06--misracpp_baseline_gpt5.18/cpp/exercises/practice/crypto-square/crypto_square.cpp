#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

namespace {

// Keep only [a-z0-9], lower-cased.
std::string normalize(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

// Compute rectangle dimensions (r rows, c columns) per rules:
// c = ceil(sqrt(L)), r = ceil(L / c). For L == 0, both 0.
std::pair<std::size_t, std::size_t> dimensions(std::size_t len) {
    if (len == 0) return {0u, 0u};
    const double root = std::sqrt(static_cast<double>(len));
    const std::size_t c = static_cast<std::size_t>(std::ceil(root));
    const std::size_t r = (len + c - 1) / c; // ceil(len / c)
    return {r, c};
}

} // namespace

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)) {}

std::string cipher::normalized_plain_text() const {
    return normalized_;
}

std::string cipher::normalize_plain_text() const {
    return normalized_plain_text();
}

std::vector<std::string> cipher::plain_text_segments() const {
    auto [r, c] = dimensions(normalized_.size());
    std::vector<std::string> segments;
    segments.reserve(r);
    for (std::size_t row = 0; row < r; ++row) {
        const std::size_t start = row * c;
        const std::size_t len = std::min(c, normalized_.size() - start);
        segments.emplace_back(normalized_.substr(start, len));
    }
    return segments;
}

std::string cipher::ciphertext() const {
    auto [r, c] = dimensions(normalized_.size());
    std::string out;
    out.reserve(normalized_.size());
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < normalized_.size()) {
                out.push_back(normalized_[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    auto [r, c] = dimensions(normalized_.size());
    if (r == 0 || c == 0) return std::string{};
    // Output consists of c chunks of length r, separated by a single space.
    std::string out;
    out.reserve(r * c + (c > 0 ? (c - 1) : 0));
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) out.push_back(' ');
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < normalized_.size()) {
                out.push_back(normalized_[idx]);
            } else {
                // Pad with a single trailing space where the rectangle is short.
                out.push_back(' ');
            }
        }
    }
    return out;
}

std::string cipher::normalize_cipher_text() const {
    return normalized_cipher_text();
}

std::string cipher::encode() const {
    return normalized_cipher_text();
}

std::string cipher::encoded() const {
    return normalized_cipher_text();
}

}  // namespace crypto_square

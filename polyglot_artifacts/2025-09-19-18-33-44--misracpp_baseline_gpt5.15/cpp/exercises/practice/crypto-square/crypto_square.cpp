#include "crypto_square.h"

#include <cctype>
#include <cmath>

namespace crypto_square {

cipher::cipher(const std::string& text) : input_(text) {}

std::string cipher::normalize_plain_text() const {
    std::string normalized;
    normalized.reserve(input_.size());
    for (unsigned char ch : input_) {
        if (std::isalnum(ch)) {
            normalized.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return normalized;
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    if (n == 0) return {};

    const std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    std::vector<std::string> segments;
    segments.reserve((n + c - 1) / c);

    for (std::size_t i = 0; i < n; i += c) {
        segments.emplace_back(norm.substr(i, c));
    }

    return segments;
}

std::string cipher::ciphertext() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    if (n == 0) return {};

    const std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    const std::size_t r = (c == 0) ? 0 : ((c * (c - 1) >= n) ? (c - 1) : c);

    std::string out;
    out.reserve(n);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(norm[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    if (n == 0) return {};

    const std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    const std::size_t r = (c == 0) ? 0 : ((c * (c - 1) >= n) ? (c - 1) : c);

    

    std::string out;
    // c chunks of length r, plus (c-1) spaces
    out.reserve(r * c + (c ? (c - 1) : 0));

    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(norm[idx]);
            } else {
                out.push_back(' ');
            }
        }
        if (col + 1 < c) out.push_back(' ');
    }

    // Ensure only the last `missing` chunks have trailing space; others naturally full.
    // The above construction already achieves this because missing cells occur in the last `missing` columns.

    return out;
}

}  // namespace crypto_square

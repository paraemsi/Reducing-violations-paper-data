#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

namespace {
std::pair<std::size_t, std::size_t> dimensions(std::size_t n) {
    if (n == 0) {
        return {0u, 0u};
    }
    auto root = std::sqrt(static_cast<long double>(n));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < n) {
        r = c;
    }
    return {r, c};
}

std::string normalize_text(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}
}  // namespace

std::string normalize_plain_text(const std::string& text) {
    return normalize_text(text);
}

std::vector<std::string> plaintext_segments(const std::string& text) {
    const std::string norm = normalize_text(text);
    const auto [r, c] = dimensions(norm.size());
    (void)r;  // r is not needed directly for segmentation
    if (c == 0) {
        return {};
    }

    std::vector<std::string> segments;
    segments.reserve((norm.size() + c - 1) / c);

    for (std::size_t i = 0; i < norm.size(); i += c) {
        segments.emplace_back(norm.substr(i, std::min(c, norm.size() - i)));
    }
    return segments;
}

std::string cipher_text(const std::string& text) {
    const std::string norm = normalize_text(text);
    const auto [r, c] = dimensions(norm.size());
    if (c == 0) {
        return {};
    }

    const auto segments = plaintext_segments(text);

    std::string out;
    out.reserve(norm.size());
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            if (row < segments.size() && col < segments[row].size()) {
                out.push_back(segments[row][col]);
            }
        }
    }
    return out;
}

std::string normalized_cipher_text(const std::string& text) {
    const std::string norm = normalize_text(text);
    const auto [r, c] = dimensions(norm.size());
    if (c == 0) {
        return {};
    }

    const auto segments = plaintext_segments(text);

    std::string out;
    // Each chunk has length r, and there are c chunks plus (c-1) spaces
    out.reserve(c * r + (c ? (c - 1) : 0));

    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) {
            out.push_back(' ');
        }
        for (std::size_t row = 0; row < r; ++row) {
            if (row < segments.size() && col < segments[row].size()) {
                out.push_back(segments[row][col]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    return normalize_text(text_);
}

std::vector<std::string> cipher::plaintext_segments() const {
    return crypto_square::plaintext_segments(text_);
}

std::string cipher::cipher_text() const {
    return crypto_square::cipher_text(text_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalized_cipher_text(text_);
}

}  // namespace crypto_square

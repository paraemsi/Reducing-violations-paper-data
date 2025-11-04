#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>

namespace crypto_square {

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    std::string normalized;
    normalized.reserve(text_.size());
    for (unsigned char ch : text_) {
        if (std::isalnum(ch)) {
            normalized.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return normalized;
}

std::size_t cipher::size() const {
    const std::string normalized = normalize_plain_text();
    if (normalized.empty()) {
        return 0u;
    }
    const double root = std::sqrt(static_cast<double>(normalized.size()));
    return static_cast<std::size_t>(std::ceil(root));
}

std::vector<std::string> cipher::plaintext_segments() const {
    const std::string normalized = normalize_plain_text();
    const std::size_t c = size();
    std::vector<std::string> segments;
    if (c == 0u) {
        return segments;
    }

    segments.reserve((normalized.size() + c - 1u) / c);
    for (std::size_t i = 0; i < normalized.size(); i += c) {
        const std::size_t len = std::min(c, normalized.size() - i);
        segments.emplace_back(normalized.substr(i, len));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const auto rows = plaintext_segments();
    if (rows.empty()) {
        return {};
    }

    const std::size_t c = size();
    const std::size_t r = rows.size();

    std::string out;
    out.reserve(rows[0].size() * r);

    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            if (col < rows[row].size()) {
                out.push_back(rows[row][col]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const auto rows = plaintext_segments();
    if (rows.empty()) {
        return {};
    }

    const std::size_t c = size();
    const std::size_t r = rows.size();

    std::string out;
    out.reserve(c * r + (c > 0 ? (c - 1) : 0));  // preallocate for chunks and spaces between them
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) {
            out.push_back(' ');
        }
        for (std::size_t row = 0; row < r; ++row) {
            if (col < rows[row].size()) {
                out.push_back(rows[row][col]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square

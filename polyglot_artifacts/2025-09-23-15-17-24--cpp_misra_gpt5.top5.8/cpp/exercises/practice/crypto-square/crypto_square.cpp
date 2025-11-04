#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

namespace {

std::size_t compute_columns(const std::size_t n) {
    if (n == static_cast<std::size_t>(0U)) {
        return static_cast<std::size_t>(0U);
    }

    std::size_t c = static_cast<std::size_t>(0U);
    while ((c * c) < n) {
        ++c;
    }
    return c;
}

std::size_t compute_rows(const std::size_t n, const std::size_t c) {
    if (c == static_cast<std::size_t>(0U)) {
        return static_cast<std::size_t>(0U);
    }
    // ceil(n / c) using integers
    return (n + (c - static_cast<std::size_t>(1U))) / c;
}

}  // namespace

namespace crypto_square {

cipher::cipher(const std::string& text) : normalized_() {
    normalized_.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            normalized_.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments{};
    const std::size_t n = normalized_.size();
    if (n == static_cast<std::size_t>(0U)) {
        return segments;
    }

    const std::size_t c = compute_columns(n);
    for (std::size_t pos = static_cast<std::size_t>(0U); pos < n; pos += c) {
        const std::size_t remaining = n - pos;
        const std::size_t take = (remaining < c) ? remaining : c;
        segments.emplace_back(normalized_.substr(pos, take));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const std::size_t n = normalized_.size();
    if (n == static_cast<std::size_t>(0U)) {
        return std::string{};
    }

    const std::size_t c = compute_columns(n);
    const std::size_t r = compute_rows(n, c);

    std::string out{};
    out.reserve(n);
    for (std::size_t col = static_cast<std::size_t>(0U); col < c; ++col) {
        for (std::size_t row = static_cast<std::size_t>(0U); row < r; ++row) {
            const std::size_t idx = (row * c) + col;
            if (idx < n) {
                out.push_back(normalized_[idx]);
            } else {
                // no-op for missing cells
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t n = normalized_.size();
    if (n == static_cast<std::size_t>(0U)) {
        return std::string{};
    }

    const std::size_t c = compute_columns(n);
    const std::size_t r = compute_rows(n, c);

    // Build column-wise chunks, each padded to length r
    std::vector<std::string> chunks{};
    chunks.reserve(c);

    for (std::size_t col = static_cast<std::size_t>(0U); col < c; ++col) {
        std::string chunk{};
        chunk.reserve(r);
        for (std::size_t row = static_cast<std::size_t>(0U); row < r; ++row) {
            const std::size_t idx = (row * c) + col;
            if (idx < n) {
                chunk.push_back(normalized_[idx]);
            } else {
                // no character in this cell
            }
        }
        while (chunk.size() < r) {
            chunk.push_back(' ');
        }
        chunks.emplace_back(chunk);
    }

    // Join chunks with single spaces
    std::string out{};
    if (c > static_cast<std::size_t>(0U)) {
        const std::size_t total_len = (c * r) + (c - static_cast<std::size_t>(1U));
        out.reserve(total_len);
    }

    for (std::size_t i = static_cast<std::size_t>(0U); i < chunks.size(); ++i) {
        if (i != static_cast<std::size_t>(0U)) {
            out.push_back(' ');
        } else {
            // first chunk, no separator
        }
        out += chunks[i];
    }

    return out;
}

}  // namespace crypto_square

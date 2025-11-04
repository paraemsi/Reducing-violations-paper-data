#include "crypto_square.h"

#include <cctype>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text)
    : normalized_(),
      columns_(static_cast<std::size_t>(0)),
      rows_(static_cast<std::size_t>(0)) {
    normalized_.reserve(text.size());

    for (const char ch : text) {
        const std::char_traits<char>::int_type ich = std::char_traits<char>::to_int_type(ch);
        if (std::isalnum(ich) != 0) {
            const std::char_traits<char>::int_type lower_i = std::tolower(ich);
            const char lower_ch = std::char_traits<char>::to_char_type(lower_i);
            normalized_.push_back(lower_ch);
        }
    }

    const std::size_t n = normalized_.size();
    if (n == static_cast<std::size_t>(0)) {
        columns_ = static_cast<std::size_t>(0);
        rows_ = static_cast<std::size_t>(0);
        return;
    }

    // Compute columns and rows using integer arithmetic to avoid floating conversions
    std::size_t c = static_cast<std::size_t>(1);
    while (((c * c) < n)) {
        c = c + static_cast<std::size_t>(1);
    }
    std::size_t r = c;
    if ((((c - static_cast<std::size_t>(1)) * c) >= n)) {
        r = c - static_cast<std::size_t>(1);
    }

    rows_ = r;
    columns_ = c;
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plaintext_segments() const {
    std::vector<std::string> segments;
    const std::size_t n = normalized_.size();

    if (columns_ == static_cast<std::size_t>(0)) {
        return segments;
    }

    for (std::size_t i = static_cast<std::size_t>(0); i < n; i += columns_) {
        const std::size_t remaining = n - i;
        const std::size_t take = (remaining < columns_) ? remaining : columns_;
        segments.emplace_back(normalized_.substr(i, take));
    }

    return segments;
}

std::string cipher::ciphertext() const {
    std::string out;
    const std::size_t n = normalized_.size();

    if (n == static_cast<std::size_t>(0)) {
        return out;
    }

    out.reserve(n);

    for (std::size_t col = static_cast<std::size_t>(0); col < columns_; ++col) {
        for (std::size_t row = static_cast<std::size_t>(0); row < rows_; ++row) {
            const std::size_t idx = (row * columns_) + col;
            if (idx < n) {
                out.push_back(normalized_[idx]);
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t n = normalized_.size();

    if (n == static_cast<std::size_t>(0)) {
        return std::string();
    }

    const std::size_t shortfall = (rows_ * columns_) - n;

    std::vector<std::string> chunks;
    chunks.reserve(columns_);

    for (std::size_t col = static_cast<std::size_t>(0); col < columns_; ++col) {
        std::string seg;
        seg.reserve(rows_);
        for (std::size_t row = static_cast<std::size_t>(0); row < rows_; ++row) {
            const std::size_t idx = (row * columns_) + col;
            if (idx < n) {
                seg.push_back(normalized_[idx]);
            }
        }
        if ((shortfall != static_cast<std::size_t>(0)) && (col >= (columns_ - shortfall))) {
            seg.push_back(' ');
        }
        chunks.push_back(seg);
    }

    std::string result;
    for (std::size_t i = static_cast<std::size_t>(0); i < chunks.size(); ++i) {
        if (i != static_cast<std::size_t>(0)) {
            result.push_back(' ');
        }
        result += chunks[i];
    }

    return result;
}

std::size_t cipher::size() const {
    return columns_;
}

}  // namespace crypto_square

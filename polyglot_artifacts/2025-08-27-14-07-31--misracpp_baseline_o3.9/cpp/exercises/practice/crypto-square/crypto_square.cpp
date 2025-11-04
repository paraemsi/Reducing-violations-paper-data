#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <utility>
#include <sstream>

namespace crypto_square {

// ---------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------
static std::string normalize(std::string_view text) {
    std::string out;
    out.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

static std::pair<std::size_t, std::size_t> dimensions(std::size_t n) {
    // smallest rectangle such that r * c >= n,  c >= r and c - r <= 1
    if (n == 0) {
        return {0, 0};
    }
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(static_cast<double>(n))));
    if (r * c < n) {
        ++r;
    }
    return {r, c};
}

// ---------------------------------------------------------------------
// cipher class implementation
// ---------------------------------------------------------------------
cipher::cipher(std::string_view text) : norm_(normalize(text)) {
    auto [r, c] = dimensions(norm_.size());
    rows_ = r;
    cols_ = c;

    segments_.reserve(rows_);
    for (std::size_t pos = 0; pos < norm_.size(); pos += cols_) {
        std::string segment = norm_.substr(pos, cols_);
        segments_.emplace_back(std::move(segment));
    }
}

std::string cipher::normalize_plain_text() const {
    return norm_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    return segments_;
}

std::string cipher::cipher_text() const {
    if (segments_.empty()) {
        return {};
    }
    std::string cipher_str;
    cipher_str.reserve(norm_.size());
    for (std::size_t col = 0; col < cols_; ++col) {
        for (const auto& row : segments_) {
            if (col < row.size() && row[col] != ' ') {
                cipher_str.push_back(row[col]);
            }
        }
    }
    return cipher_str;
}

std::string cipher::normalized_cipher_text() const {
    if (norm_.empty()) {
        return {};
    }
    std::ostringstream oss;
    for (std::size_t col = 0; col < cols_; ++col) {
        if (col != 0) {
            oss << ' ';
        }
        for (std::size_t row = 0; row < rows_; ++row) {
            if (row < segments_.size() && col < segments_[row].size()) {
                oss << segments_[row][col];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

// ---------------------------------------------------------------------
// public API
// ---------------------------------------------------------------------
std::string normalize_plain_text(std::string_view text) {
    return normalize(text);
}

std::vector<std::string> plain_text_segments(std::string_view text) {
    const std::string norm = normalize(text);
    const auto [r, c] = dimensions(norm.size());

    std::vector<std::string> segments;
    segments.reserve(r);

    for (std::size_t pos = 0; pos < norm.size(); pos += c) {
        std::string segment = norm.substr(pos, c);
        segments.emplace_back(std::move(segment));
    }
    return segments;
}

std::string cipher_text(std::string_view text) {
    const std::vector<std::string> rows = plain_text_segments(text);
    if (rows.empty()) {
        return {};
    }
    const std::size_t c = rows.front().size();
    std::string cipher;
    cipher.reserve(normalize(text).size());

    for (std::size_t col = 0; col < c; ++col) {
        for (const auto& row : rows) {
            if (col < row.size() && row[col] != ' ') {
                cipher.push_back(row[col]);
            }
        }
    }
    return cipher;
}

std::string normalized_cipher_text(std::string_view text) {
    const std::string norm = normalize(text);
    if (norm.empty()) {
        return {};
    }

    const auto [r, c] = dimensions(norm.size());
    const std::vector<std::string> rows = plain_text_segments(text);

    std::ostringstream oss;
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) {
            oss << ' ';
        }
        for (std::size_t row = 0; row < r; ++row) {
            if (row < rows.size() && col < rows[row].size()) {
                oss << rows[row][col];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

}  // namespace crypto_square

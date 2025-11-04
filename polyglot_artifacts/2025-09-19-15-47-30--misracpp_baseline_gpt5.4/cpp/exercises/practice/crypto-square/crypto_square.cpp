#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
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

static std::pair<std::size_t, std::size_t> dims(std::size_t L) {
    if (L == 0) {
        return {0u, 0u};
    }
    double root = std::sqrt(static_cast<double>(L));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < L) {
        ++r;
    }
    return {r, c};
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> rows;
    const std::size_t L = normalized_.size();
    std::pair<std::size_t, std::size_t> rc = dims(L);
    std::size_t r = rc.first;
    std::size_t c = rc.second;
    rows.reserve(r);
    for (std::size_t i = 0; i < L; i += c) {
        rows.emplace_back(normalized_.substr(i, std::min(c, L - i)));
    }
    return rows;
}

std::string cipher::cipher_text() const {
    const std::size_t L = normalized_.size();
    if (L == 0) {
        return {};
    }
    std::pair<std::size_t, std::size_t> rc = dims(L);
    std::size_t r = rc.first;
    std::size_t c = rc.second;
    std::vector<std::string> rows = plain_text_segments();

    std::string out;
    out.reserve(L);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::string& rowstr = rows[row];
            if (col < rowstr.size()) {
                out.push_back(rowstr[col]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t L = normalized_.size();
    if (L == 0) {
        return {};
    }
    std::pair<std::size_t, std::size_t> rc = dims(L);
    std::size_t r = rc.first;
    std::size_t c = rc.second;

    // Build a padded grid of size r x c
    std::vector<std::string> rows;
    rows.reserve(r);
    std::size_t idx = 0;
    for (std::size_t i = 0; i < r; ++i) {
        std::string row;
        row.reserve(c);
        for (std::size_t j = 0; j < c; ++j) {
            if (idx < L) {
                row.push_back(normalized_[idx++]);
            } else {
                row.push_back(' ');
            }
        }
        rows.push_back(std::move(row));
    }

    // Read down the columns and separate by spaces
    std::string out;
    out.reserve(r * c + (c ? c - 1 : 0));
    for (std::size_t col = 0; col < c; ++col) {
        if (col > 0) {
            out.push_back(' ');
        }
        for (std::size_t row = 0; row < r; ++row) {
            out.push_back(rows[row][col]);
        }
    }
    return out;
}

}  // namespace crypto_square

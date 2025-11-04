#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    normalized_.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            normalized_.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    compute_dimensions();
}

void cipher::compute_dimensions() {
    const std::size_t L = normalized_.size();
    if (L == 0) {
        rows_ = cols_ = 0;
        return;
    }
    const double root = std::sqrt(static_cast<double>(L));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < L) {
        r = c;
    }
    rows_ = r;
    cols_ = c;
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plaintext_segments() const {
    std::vector<std::string> segments;
    if (normalized_.empty()) return segments;

    segments.reserve(rows_);
    for (std::size_t i = 0; i < normalized_.size(); i += cols_) {
        segments.emplace_back(normalized_.substr(i, cols_));
    }
    return segments;
}

std::string cipher::ciphertext() const {
    if (normalized_.empty()) return {};

    const auto segments = plaintext_segments();
    std::string out;
    out.reserve(normalized_.size());

    for (std::size_t col = 0; col < cols_; ++col) {
        for (const auto& row : segments) {
            if (col < row.size()) {
                out.push_back(row[col]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) return {};

    const auto segments = plaintext_segments();

    // Build column strings (left to right)
    std::vector<std::string> columns;
    columns.reserve(cols_);
    for (std::size_t col = 0; col < cols_; ++col) {
        std::string s;
        s.reserve(rows_);
        for (const auto& row : segments) {
            if (col < row.size()) {
                s.push_back(row[col]);
            }
        }
        columns.push_back(std::move(s));
    }

    // Pad the last 'missing' columns with a single trailing space each
    const std::size_t missing = rows_ * cols_ - normalized_.size();
    for (std::size_t i = 0; i < missing; ++i) {
        columns[cols_ - 1 - i].push_back(' ');
    }

    // Join with single spaces
    std::string out;
    if (!columns.empty()) {
        out.reserve(cols_ * rows_ + (cols_ - 1));
        for (std::size_t i = 0; i < columns.size(); ++i) {
            if (i > 0) out.push_back(' ');
            out += columns[i];
        }
    }
    return out;
}

}  // namespace crypto_square

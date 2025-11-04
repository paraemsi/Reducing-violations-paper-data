#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

namespace {
inline bool is_valid_char(unsigned char ch) {
    return static_cast<bool>(std::isalnum(ch));
}

inline char to_lower_char(unsigned char ch) {
    return static_cast<char>(std::tolower(ch));
}

// Compute rectangle dimensions (rows r, cols c) for length n
inline std::pair<std::size_t, std::size_t> dimensions(std::size_t n) {
    if (n == 0) return {0, 0};
    double root = std::sqrt(static_cast<double>(n));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    std::size_t r = (n + c - 1) / c; // ceil(n / c)
    // ensures c >= r and c - r <= 1
    return {r, c};
}
} // namespace

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    std::string out;
    out.reserve(text_.size());
    for (unsigned char ch : text_) {
        if (is_valid_char(ch)) {
            out.push_back(to_lower_char(ch));
        }
    }
    return out;
}

std::vector<std::string> cipher::plaintext_segments() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    auto [r, c] = dimensions(n);

    std::vector<std::string> rows;
    rows.reserve(r);
    for (std::size_t i = 0; i < n; i += c) {
        rows.emplace_back(norm.substr(i, std::min(c, n - i)));
    }
    return rows;
}

std::string cipher::encoded() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    auto [r, c] = dimensions(n);
    if (n == 0) return std::string();

    std::string out;
    out.reserve(n);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(norm[idx]);
            }
        }
    }
    return out;
}

std::string cipher::cipher_text() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    auto [r, c] = dimensions(n);
    if (n == 0) return std::string();

    std::string out;
    // Build each column as a word (no padding), separated by spaces
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) out.push_back(' ');
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
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
    auto [r, c] = dimensions(n);
    if (n == 0) return std::string();


    std::string out;
    // Each chunk corresponds to a column, each of length r, separated by spaces.
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) out.push_back(' ');
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(norm[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }

    // The rule states: pad the last few chunks (those with fewer characters) with a trailing space.
    // Our construction already includes the necessary padding spaces inside each chunk,
    // and chunks are separated by single spaces. No additional adjustment needed.

    return out;
}

}  // namespace crypto_square

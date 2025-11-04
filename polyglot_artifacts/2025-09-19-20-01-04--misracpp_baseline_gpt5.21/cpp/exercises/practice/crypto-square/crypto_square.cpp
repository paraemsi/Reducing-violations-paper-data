#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    std::string out;
    out.reserve(text_.size());
    for (unsigned char ch : text_) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

std::size_t cipher::size() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    if (n == 0) return 0;
    return static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    const std::size_t c = (n == 0) ? 0 : static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    std::vector<std::string> rows;
    if (c == 0) return rows;
    rows.reserve((n + c - 1) / c);
    for (std::size_t i = 0; i < n; i += c) {
        rows.push_back(norm.substr(i, c));
    }
    return rows;
}

std::string cipher::ciphertext() const {
    const std::string norm = normalize_plain_text();
    const std::size_t n = norm.size();
    if (n == 0) return std::string{};
    const std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    const std::size_t r = (n + c - 1) / c;

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
    if (n == 0) return std::string{};
    const std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    const std::size_t r = (n + c - 1) / c;

    std::string out;
    // Reserve: c groups of length r, plus (c - 1) spaces between groups
    out.reserve(c * r + (c ? c - 1 : 0));

    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) out.push_back(' ');
        std::size_t col_len = 0;
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < n) {
                out.push_back(norm[idx]);
                ++col_len;
            }
        }
        if (col_len < r) {
            out.append(r - col_len, ' ');
        }
    }
    return out;
}

}  // namespace crypto_square

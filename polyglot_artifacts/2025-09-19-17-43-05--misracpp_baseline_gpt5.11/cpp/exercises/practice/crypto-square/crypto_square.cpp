#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>

namespace crypto_square {

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    std::string out;
    out.reserve(text_.size());
    for (unsigned char ch : text_) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

static std::pair<std::size_t, std::size_t> compute_dimensions(std::size_t n) {
    if (n == 0) return {0u, 0u};
    double root = std::sqrt(static_cast<double>(n));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    std::size_t r = (n + c - 1) / c; // ceil(n / c)
    return {r, c};
}

std::vector<std::string> cipher::plaintext_segments() const {
    std::string norm = normalize_plain_text();
    auto [r, c] = compute_dimensions(norm.size());

    std::vector<std::string> rows;
    if (c == 0u) return rows;

    rows.reserve(r);
    for (std::size_t i = 0; i < norm.size(); i += c) {
        rows.push_back(norm.substr(i, std::min<std::size_t>(c, norm.size() - i)));
    }
    return rows;
}

std::string cipher::encoded() const {
    auto rows = plaintext_segments();
    if (rows.empty()) return {};

    std::size_t r = rows.size();
    std::size_t c = 0u;
    for (const auto& row : rows) c = std::max<std::size_t>(c, row.size());

    std::string out;
    out.reserve(normalize_plain_text().size());

    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            if (col < rows[row].size()) {
                out.push_back(rows[row][col]);
            }
        }
    }
    return out;
}

std::string cipher::cipher_text() const {
    return encoded();
}

std::string cipher::normalized_cipher_text() const {
    auto rows = plaintext_segments();
    if (rows.empty()) return {};

    std::size_t r = rows.size();
    std::size_t c = 0u;
    for (const auto& row : rows) c = std::max<std::size_t>(c, row.size());

    const std::size_t n = normalize_plain_text().size();
    const std::size_t total = r * c;
    const std::size_t n_missing = total - n; // number of columns that are short by 1

    std::ostringstream oss;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            if (col < rows[row].size()) {
                oss << rows[row][col];
            } else {
                // Only the last n_missing columns are short; pad them with a trailing space.
                if (col >= c - n_missing) {
                    oss << ' ';
                }
            }
        }
        if (col + 1 < c) {
            oss << ' ';
        }
    }
    return oss.str();
}

}  // namespace crypto_square

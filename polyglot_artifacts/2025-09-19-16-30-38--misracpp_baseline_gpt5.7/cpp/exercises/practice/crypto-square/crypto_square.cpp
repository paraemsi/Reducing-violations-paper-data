#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

namespace {
inline bool is_alnum_uchar(unsigned char ch) {
    return std::isalnum(ch) != 0;
}

std::string normalize(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (unsigned char ch : input) {
        if (is_alnum_uchar(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

inline std::pair<std::size_t, std::size_t> dimensions(std::size_t len) {
    if (len == 0) {
        return {0u, 0u};
    }
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<long double>(len))));
    std::size_t r = (c == 0) ? 0 : (len + c - 1) / c; // ceil(len / c)
    return {r, c};
}

} // namespace

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    return normalize(text_);
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::string norm = normalize(text_);
    const std::size_t len = norm.size();
    auto dims = dimensions(len);
    std::size_t r = dims.first;
    std::size_t c = dims.second;
    std::vector<std::string> rows;
    rows.reserve(r);
    for (std::size_t row = 0; row < r; ++row) {
        const std::size_t start = row * c;
        const std::size_t count = (start + c <= len) ? c : (len > start ? (len - start) : 0u);
        rows.emplace_back(norm.substr(start, count));
    }
    return rows;
}

std::string cipher::ciphertext() const {
    const std::string norm = normalize(text_);
    const std::size_t len = norm.size();
    auto dims = dimensions(len);
    std::size_t r = dims.first;
    std::size_t c = dims.second;
    if (len == 0 || r == 0 || c == 0) {
        return std::string{};
    }

    std::string out;
    out.reserve(len);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < len) {
                out.push_back(norm[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::string norm = normalize(text_);
    const std::size_t len = norm.size();
    auto dims = dimensions(len);
    std::size_t r = dims.first;
    std::size_t c = dims.second;
    if (len == 0 || r == 0 || c == 0) {
        return std::string{};
    }

    std::string out;
    // Reserve len + (c - 1) spaces between chunks + possible padding inside chunks.
    // The padding inside chunks equals r*c - len.
    out.reserve(len + (c > 0 ? c - 1 : 0) + (r * c - len));

    for (std::size_t col = 0; col < c; ++col) {
        if (col > 0) {
            out.push_back(' ');
        }
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < len) {
                out.push_back(norm[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square

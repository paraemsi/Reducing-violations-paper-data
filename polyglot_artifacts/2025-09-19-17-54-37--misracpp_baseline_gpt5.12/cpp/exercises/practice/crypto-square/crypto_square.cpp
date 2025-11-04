#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <utility>

namespace crypto_square {

namespace {
    inline bool is_alnum_char(char ch) {
        unsigned char uch = static_cast<unsigned char>(ch);
        return std::isalnum(uch) != 0;
    }

    inline char to_lower_char(char ch) {
        unsigned char uch = static_cast<unsigned char>(ch);
        return static_cast<char>(std::tolower(uch));
    }

    inline std::pair<std::size_t, std::size_t> dimensions(std::size_t len) {
        if (len == 0) return {0, 0};
        double root = std::sqrt(static_cast<double>(len));
        std::size_t r = static_cast<std::size_t>(std::floor(root));
        std::size_t c = static_cast<std::size_t>(std::ceil(root));
        if (r * c < len) {
            r = c;
        }
        return {r, c};
    }
}

cipher::cipher(const std::string& text) : text_{text} {}

std::string cipher::normalize_plain_text() const {
    std::string out;
    out.reserve(text_.size());
    for (char ch : text_) {
        if (is_alnum_char(ch)) {
            out.push_back(to_lower_char(ch));
        }
    }
    return out;
}

std::vector<std::string> cipher::plaintext_segments() const {
    std::string normalized = normalize_plain_text();
    std::vector<std::string> segments;
    auto [r, c] = dimensions(normalized.size());
    if (c == 0) {
        return segments;
    }
    segments.reserve(r);
    for (std::size_t i = 0; i < normalized.size(); i += c) {
        segments.emplace_back(normalized.substr(i, std::min(c, normalized.size() - i)));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    std::string normalized = normalize_plain_text();
    auto [r, c] = dimensions(normalized.size());
    if (c == 0) {
        return {};
    }
    std::string out;
    out.reserve(normalized.size());
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
            if (idx < normalized.size()) {
                out.push_back(normalized[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    std::string normalized = normalize_plain_text();
    auto [r, c] = dimensions(normalized.size());
    if (c == 0) {
        return {};
    }
    std::string out;
    // Produce c chunks of length r separated by spaces, padding with spaces as needed.
    out.reserve(c * (r + 1) - 1);
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) out.push_back(' ');
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
            if (idx < normalized.size()) {
                out.push_back(normalized[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square

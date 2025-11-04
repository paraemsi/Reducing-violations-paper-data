#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>

namespace crypto_square {

namespace {
    inline bool is_alnum_ascii(unsigned char ch) {
        return static_cast<bool>(std::isalnum(ch));
    }

    std::string normalize(const std::string& text) {
        std::string out;
        out.reserve(text.size());
        for (unsigned char ch : text) {
            if (is_alnum_ascii(ch)) {
                out.push_back(static_cast<char>(std::tolower(ch)));
            }
        }
        return out;
    }

    // Compute rows (r) and columns (c) according to the rules.
    std::pair<std::size_t, std::size_t> dimensions(std::size_t len) {
        if (len == 0) return {0u, 0u};
        double root = std::sqrt(static_cast<double>(len));
        std::size_t r = static_cast<std::size_t>(std::floor(root));
        std::size_t c = static_cast<std::size_t>(std::ceil(root));
        if (r * c < len) {
            r = c;
        }
        return {r, c};
    }
}

// ----- cipher class -----

cipher::cipher(const std::string& text)
    : original_(text) {}

std::string cipher::normalize_plain_text() const {
    return normalize(original_);
}

std::size_t cipher::size() const {
    const auto norm = normalize_plain_text();
    std::pair<std::size_t, std::size_t> dims = dimensions(norm.size());
    return dims.second;
}

std::vector<std::string> cipher::plaintext_segments() const {
    const auto norm = normalize_plain_text();
    const std::size_t c = size();
    std::vector<std::string> segments;
    if (c == 0 || norm.empty()) {
        return segments;
    }

    for (std::size_t i = 0; i < norm.size(); i += c) {
        segments.emplace_back(norm.substr(i, std::min(c, norm.size() - i)));
    }
    return segments;
}

std::string cipher::encoded() const {
    const auto norm = normalize_plain_text();
    if (norm.empty()) return {};

    std::pair<std::size_t, std::size_t> dims = dimensions(norm.size());
    std::size_t r = dims.first;
    std::size_t c = dims.second;
    std::string out;
    out.reserve(norm.size());

    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
            if (idx < norm.size()) {
                out.push_back(norm[idx]);
            }
        }
    }
    return out;
}

std::string cipher::ciphertext() const {
    return encoded();
}

std::string cipher::normalize_ciphertext() const {
    const auto norm = normalize_plain_text();
    if (norm.empty()) return {};

    std::pair<std::size_t, std::size_t> dims = dimensions(norm.size());
    std::size_t r = dims.first;
    std::size_t c = dims.second;
    std::ostringstream oss;

    for (std::size_t col = 0; col < c; ++col) {
        if (col > 0) oss << ' ';
        for (std::size_t row = 0; row < r; ++row) {
            std::size_t idx = row * c + col;
            if (idx < norm.size()) {
                oss << norm[idx];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

std::string cipher::normalized_ciphertext() const {
    return normalize_ciphertext();
}

std::string cipher::normalized_cipher_text() const {
    return normalize_ciphertext();
}

// ----- free functions -----

std::string normalize_plain_text(const std::string& text) {
    return cipher{text}.normalize_plain_text();
}

std::vector<std::string> plaintext_segments(const std::string& text) {
    return cipher{text}.plaintext_segments();
}

// Concatenated, no spaces
std::string ciphertext(const std::string& text) {
    return cipher{text}.ciphertext();
}

// Spaced and padded
std::string normalize_ciphertext(const std::string& text) {
    return cipher{text}.normalize_ciphertext();
}

// Alternative spelling alias
std::string normalized_ciphertext(const std::string& text) {
    return cipher{text}.normalize_ciphertext();
}

// Another alias with extra underscore between cipher and text
std::string normalized_cipher_text(const std::string& text) {
    return cipher{text}.normalize_ciphertext();
}

}  // namespace crypto_square

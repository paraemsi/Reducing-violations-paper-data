#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>

namespace crypto_square {

// ------------------------------------------------------------------
// Helper/public functions
// ------------------------------------------------------------------

std::string normalize_plain_text(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            out.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

std::vector<std::string> plaintext_segments(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const std::size_t len = normalized.size();
    if (len == 0) {
        return {};
    }

    const std::size_t c =
        static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
    std::size_t r =
        static_cast<std::size_t>(std::floor(std::sqrt(static_cast<double>(len))));
    if (r * c < len) {
        ++r;
    }

    std::vector<std::string> segments;
    segments.reserve(r);
    for (std::size_t pos = 0; pos < len; pos += c) {
        segments.push_back(normalized.substr(pos, c));
    }
    return segments;
}

std::string cipher_text(const std::string& input) {
    // 1. Normalize the input.
    std::string normalized = normalize_plain_text(input);

    const std::size_t len = normalized.size();
    if (len == 0) {
        return "";
    }

    // 2. Determine rectangle dimensions satisfying:
    //    r * c >= len, c >= r and c - r <= 1
    const std::size_t c =
        static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
    std::size_t r =
        static_cast<std::size_t>(std::floor(std::sqrt(static_cast<double>(len))));
    if (r * c < len) {
        ++r;
    }

    // 3. Build cipher text column-wise, padding with spaces where necessary.
    std::ostringstream oss;
    for (std::size_t col = 0; col < c; ++col) {
        if (col != 0) {
            oss << ' ';
        }
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t idx = row * c + col;
            if (idx < len) {
                oss << normalized[idx];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

// ------------------------------------------------------------------
// cipher class definitions
// ------------------------------------------------------------------

cipher::cipher(const std::string& text) : text_{text} {}

std::string cipher::normalize_plain_text() const {
    return ::crypto_square::normalize_plain_text(text_);
}

std::vector<std::string> cipher::plaintext_segments() const {
    return ::crypto_square::plaintext_segments(text_);
}

std::string cipher::ciphertext() const {
    return ::crypto_square::cipher_text(text_);
}

std::string cipher::normalized_cipher_text() const {
    std::string result = ciphertext();
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

}  // namespace crypto_square

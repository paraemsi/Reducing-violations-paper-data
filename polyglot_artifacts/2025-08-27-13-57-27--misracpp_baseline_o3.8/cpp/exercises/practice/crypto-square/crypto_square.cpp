#include "crypto_square.h"
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstddef>

namespace crypto_square {

std::string normalize_plain_text(const std::string &text) {
    std::string res;
    res.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            res.push_back(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return res;
}

std::vector<std::string> plaintext_segments(const std::string &text) {
    std::string normalized = normalize_plain_text(text);
    if (normalized.empty()) {
        return {};
    }
    const std::size_t len = normalized.size();
    const std::size_t cols = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
    std::vector<std::string> segments;
    for (std::size_t i = 0; i < len; i += cols) {
        segments.emplace_back(normalized.substr(i, cols));
    }
    return segments;
}

std::string ciphertext(const std::string &text) {
    const auto segments = plaintext_segments(text);
    if (segments.empty()) {
        return {};
    }
    const std::size_t rows = segments.size();
    const std::size_t cols = segments.front().size();
    std::string result;
    result.reserve(rows * cols);
    for (std::size_t col = 0; col < cols; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                result.push_back(segments[row][col]);
            }
        }
    }
    return result;
}

std::string normalized_cipher_text(const std::string &text) {
    const auto segments = plaintext_segments(text);
    if (segments.empty()) {
        return {};
    }
    const std::size_t rows = segments.size();
    const std::size_t cols = segments.front().size();

    std::string result;
    for (std::size_t col = 0; col < cols; ++col) {
        if (col != 0) {
            result.push_back(' ');
        }
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                result.push_back(segments[row][col]);
            } else {
                result.push_back(' ');
            }
        }
    }
    return result;
}

/* ---- cipher class method definitions ----------------------------------- */

cipher::cipher(const std::string &input) : input_(input) {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(input_);
}

std::vector<std::string> cipher::plaintext_segments() const {
    return crypto_square::plaintext_segments(input_);
}

std::string cipher::ciphertext() const {
    return crypto_square::ciphertext(input_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalized_cipher_text(input_);
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>
#include <cstddef>

namespace {

std::string normalize(const std::string &text) {
    std::string result;
    result.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return result;
}

std::pair<std::size_t, std::size_t> dimensions(std::size_t len) {
    if (len == 0) {
        return {0, 0};
    }
    double root = std::sqrt(static_cast<double>(len));
    std::size_t rows = static_cast<std::size_t>(std::floor(root));
    std::size_t cols = static_cast<std::size_t>(std::ceil(root));
    if (rows * cols < len) {
        ++rows;
    }
    return {rows, cols};
}

} // namespace

namespace crypto_square {

std::string normalize_plain_text(const std::string &text) {
    return normalize(text);
}

std::vector<std::string> plaintext_segments(const std::string &text) {
    const std::string normalized = normalize(text);
    const auto [rows, cols] = dimensions(normalized.size());

    std::vector<std::string> segments;
    segments.reserve(rows);

    for (std::size_t i = 0; i < normalized.size(); i += cols) {
        segments.emplace_back(normalized.substr(i, cols));
    }
    return segments;
}

std::string cipher_text(const std::string &text) {
    const std::string normalized = normalize(text);
    if (normalized.empty()) {
        return "";
    }
    const auto segments = plaintext_segments(text);
    const auto [rows, cols] = dimensions(normalized.size());

    std::string cipher;
    cipher.reserve(normalized.size());

    for (std::size_t c = 0; c < cols; ++c) {
        for (const auto &row : segments) {
            if (c < row.size()) {
                cipher.push_back(row[c]);
            }
        }
    }
    return cipher;
}

std::string normalize_cipher_text(const std::string &text) {
    const std::string cipher = cipher_text(text);
    if (cipher.empty()) {
        return "";
    }
    const std::string normalized = normalize(text);
    const auto [rows, cols] = dimensions(normalized.size());

    const std::size_t pad_needed = rows * cols - cipher.size(); // spaces required
    std::ostringstream oss;

    std::size_t chunk_idx{0};
    for (std::size_t i = 0; i < cipher.size(); i += rows, ++chunk_idx) {
        std::string chunk = cipher.substr(i, rows);

        // Per spec: add exactly one trailing space to each of the last `pad_needed` chunks
        if (chunk_idx >= cols - pad_needed) {
            chunk.push_back(' ');
        }

        oss << chunk;
        if (chunk_idx + 1 < cols) {
            oss << ' ';
        }
    }
    return oss.str();
}

cipher::cipher(const std::string &text) : input_(text) {}

std::string cipher::normalized_plain_text() const {
    return normalize_plain_text(input_);
}

std::size_t cipher::size() const {
    const std::string normalized = normalized_plain_text();
    const auto [rows, cols] = dimensions(normalized.size());
    (void)rows;
    return cols;
}

std::vector<std::string> cipher::plaintext_segments() const {
    return crypto_square::plaintext_segments(input_);
}

std::string cipher::cipher_text() const {
    return crypto_square::cipher_text(input_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalize_cipher_text(input_);
}

}  // namespace crypto_square

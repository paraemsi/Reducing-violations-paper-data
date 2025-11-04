#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

std::string normalize_plain_text(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

std::vector<std::string> plaintext_segments(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const std::size_t len = normalized.length();
    if (len == 0) {
        return {};
    }

    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(len)));
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(len)));
    if (r * c < len) {
        ++r;
    }

    std::vector<std::string> segments;
    segments.reserve(r);
    for (std::size_t i = 0; i < len; i += c) {
        segments.push_back(normalized.substr(i, c));
    }
    return segments;
}

std::string ciphertext(const std::string& input) {
    const auto segments = plaintext_segments(input);
    if (segments.empty()) {
        return "";
    }

    std::size_t columns = 0;
    for (const auto& seg : segments) {
        columns = std::max(columns, seg.size());
    }

    std::string cipher;
    cipher.reserve(segments.size() * columns);

    for (std::size_t col = 0; col < columns; ++col) {
        for (const auto& row : segments) {
            if (col < row.size()) {
                cipher.push_back(row[col]);
            }
        }
    }

    return cipher;
}

std::string normalized_cipher_text(const std::string& input) {
    const auto segments = plaintext_segments(input);
    if (segments.empty()) {
        return "";
    }

    const std::size_t rows = segments.size();
    std::size_t columns = 0;
    for (const auto& seg : segments) {
        columns = std::max(columns, seg.size());
    }

    std::vector<std::string> chunks;
    chunks.reserve(columns);

    for (std::size_t col = 0; col < columns; ++col) {
        std::string chunk;
        chunk.reserve(rows);
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                chunk.push_back(segments[row][col]);
            } else {
                chunk.push_back(' ');
            }
        }
        chunks.push_back(std::move(chunk));
    }

    std::ostringstream oss;
    for (std::size_t i = 0; i < chunks.size(); ++i) {
        if (i != 0) {
            oss << ' ';
        }
        oss << chunks[i];
    }

    return oss.str();
}

// -----------------------------------------------------------------------------
// Convenience alias wrappers matching the Exercism canonical API
// -----------------------------------------------------------------------------
std::vector<std::string> plain_text_segments(const std::string& input) {
    return plaintext_segments(input);
}

std::string cipher_text(const std::string& input) {
    return ciphertext(input);
}

// -- cipher class implementation ------------------------------------------------

cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(text_);
}

std::vector<std::string> cipher::plain_text_segments() const {
    return crypto_square::plaintext_segments(text_);
}

std::string cipher::cipher_text() const {
    return crypto_square::ciphertext(text_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalized_cipher_text(text_);
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string &text) : text_(text) {}

/* --------------------------------------------------------------------------
 * Private helpers
 * --------------------------------------------------------------------------*/
std::string cipher::normalize(const std::string &input) const {
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

std::size_t cipher::columns() const {
    const std::size_t len = normalize_plaintext().size();
    if (len == 0)
        return 0;
    return static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
}

std::size_t cipher::rows() const {
    const std::size_t len = normalize_plaintext().size();
    const std::size_t c = columns();
    if (c == 0)
        return 0;
    return (len + c - 1) / c; // ceil(len / c)
}

/* --------------------------------------------------------------------------
 * Public API
 * --------------------------------------------------------------------------*/
std::string cipher::normalize_plaintext() const { return normalize(text_); }

std::vector<std::string> cipher::plaintext_segments() const {
    const std::string norm = normalize_plaintext();
    const std::size_t c = columns();

    std::vector<std::string> segments;
    segments.reserve(rows());

    for (std::size_t i = 0; i < norm.size(); i += c) {
        segments.emplace_back(norm.substr(i, c));
    }
    return segments;
}

std::string cipher::ciphertext() const {
    const auto segments = plaintext_segments();
    if (segments.empty())
        return "";

    const std::size_t c = columns();
    std::string out;
    out.reserve(segments.size() * c);

    for (std::size_t col = 0; col < c; ++col) {
        for (const auto &row : segments) {
            if (col < row.size())
                out.push_back(row[col]);
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const auto segments = plaintext_segments();
    if (segments.empty())
        return "";

    const std::size_t r = rows();
    const std::size_t c = columns();

    // Build column-wise chunks (one chunk per column)
    std::vector<std::string> chunks(c);
    for (const auto &row : segments) {
        for (std::size_t col = 0; col < row.size(); ++col) {
            chunks[col].push_back(row[col]);
        }
    }

    // Pad every under-filled chunk with exactly one trailing space.
    // Owing to the rectangle constraints, at most one space is ever needed.
    for (auto &chunk : chunks) {
        if (chunk.size() < r) {
            chunk.push_back(' ');
        }
    }

    std::ostringstream oss;
    for (std::size_t i = 0; i < chunks.size(); ++i) {
        if (i > 0)
            oss << ' ';
        oss << chunks[i];
    }

    return oss.str();
}

} // namespace crypto_square

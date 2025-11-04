#include "crypto_square.h"
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {

cipher::cipher(std::string_view text) : m_input{text.begin(), text.end()} {}

std::string cipher::normalize_plain_text() const {
    std::string normalized;
    normalized.reserve(m_input.size());
    for (unsigned char ch : m_input) {
        if (std::isalnum(ch)) {
            normalized.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return normalized;
}

std::size_t cipher::size() const {
    const auto normalized = normalize_plain_text();
    const std::size_t n = normalized.size();
    if (n == 0) {
        return 0;
    }

    std::size_t rows = static_cast<std::size_t>(std::floor(std::sqrt(n)));
    std::size_t cols = static_cast<std::size_t>(std::ceil(std::sqrt(n)));

    // Ensure r * c >= n while keeping c - r <= 1
    if (rows * cols < n) {
        ++rows;
    }
    return cols;
}

std::vector<std::string> cipher::plain_text_segments() const {
    const auto normalized = normalize_plain_text();
    const std::size_t width = size();
    if (width == 0) {
        return {};
    }

    std::vector<std::string> segments;
    for (std::size_t i = 0; i < normalized.size(); i += width) {
        segments.emplace_back(normalized.substr(i, width));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const auto segments = plain_text_segments();
    const std::size_t width = size();
    if (width == 0) {
        return {};
    }
    const std::size_t rows = segments.size();
    std::string result;
    result.reserve(width * rows);

    for (std::size_t col = 0; col < width; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                result.push_back(segments[row][col]);
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    const auto segments = plain_text_segments();
    const std::size_t width = size();
    const std::size_t rows = segments.size();

    if (width == 0) {
        return {};
    }

    std::string result;
    for (std::size_t col = 0; col < width; ++col) {
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

}  // namespace crypto_square

namespace crypto_square {

std::string normalize_plain_text(std::string_view text) {
    return cipher(text).normalize_plain_text();
}

std::size_t size(std::string_view text) {
    return cipher(text).size();
}

std::vector<std::string> plain_text_segments(std::string_view text) {
    return cipher(text).plain_text_segments();
}

std::string cipher_text(std::string_view text) {
    return cipher(text).cipher_text();
}

std::string normalized_cipher_text(std::string_view text) {
    return cipher(text).normalized_cipher_text();
}

}  // namespace crypto_square

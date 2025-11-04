#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <sstream>
#include <vector>

namespace crypto_square {

std::string normalize_plain_text(const std::string& input) {
    std::string normalized;
    normalized.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return normalized;
}

std::vector<std::string> plain_text_segments(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const std::size_t len = normalized.size();
    if (len == 0) {
        return {};
    }

    const std::size_t columns =
        static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
    const std::size_t rows =
        static_cast<std::size_t>(std::ceil(static_cast<double>(len) / columns));

    std::vector<std::string> segments;
    segments.reserve(rows);
    for (std::size_t row = 0; row < rows; ++row) {
        std::size_t start = row * columns;
        std::size_t end   = std::min(start + columns, len);
        std::string segment = normalized.substr(start, end - start);

        // Pad the last (or any short) segment with spaces to reach `columns` length
        if (segment.size() < columns) {
            segment.append(columns - segment.size(), ' ');
        }

        segments.emplace_back(std::move(segment));
    }
    return segments;
}

std::string cipher_text(const std::string& input) {
    const std::vector<std::string> segments = plain_text_segments(input);
    if (segments.empty()) {
        return {};
    }

    const std::size_t rows = segments.size();
    const std::size_t columns = segments.front().size();

    std::ostringstream oss;
    for (std::size_t col = 0; col < columns; ++col) {
        if (col > 0) {
            oss << ' ';
        }
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                oss << segments[row][col];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

/* ----------------------------------------------------------------------
 *  cipher class implementation
 * --------------------------------------------------------------------*/
cipher::cipher(const std::string& text) : input_(text) {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(input_);
}

std::vector<std::string> cipher::plain_text_segments() const {
    return crypto_square::plain_text_segments(input_);
}

std::string cipher::cipher_text() const {
    return crypto_square::cipher_text(input_);
}

std::string cipher::normalized_cipher_text() const {
    std::string result = cipher_text();
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

}  // namespace crypto_square

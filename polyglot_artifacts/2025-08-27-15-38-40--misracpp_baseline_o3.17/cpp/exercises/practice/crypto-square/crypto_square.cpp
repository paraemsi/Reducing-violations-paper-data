#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

std::string normalize_plain_text(const std::string& input) {
    std::string normalized;
    normalized.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return normalized;
}

std::size_t square_size(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    if (normalized.empty()) {
        return 0;
    }
    const std::size_t n = normalized.size();
    return static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
}

std::size_t size(const std::string& input) {
    return square_size(input);
}

std::vector<std::string> plain_text_segments(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    if (normalized.empty()) {
        return {};
    }

    const std::size_t n = normalized.size();
    const std::size_t columns = square_size(input);

    std::vector<std::string> segments;
    segments.reserve((n + columns - 1) / columns);

    for (std::size_t i = 0; i < n; i += columns) {
        segments.emplace_back(normalized.substr(i, columns));
    }

    return segments;
}

std::string cipher_text(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    if (normalized.empty()) {
        return "";
    }

    const std::size_t n = normalized.size();
    const std::size_t columns = square_size(input);
    const std::size_t rows = static_cast<std::size_t>(std::ceil(static_cast<double>(n) / columns));

    std::string output;
    output.reserve(n);

    for (std::size_t col = 0; col < columns; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            const std::size_t idx = row * columns + col;
            if (idx < n) {
                output.push_back(normalized[idx]);
            }
        }
    }

    return output;
}

std::string normalized_cipher_text(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    if (normalized.empty()) {
        return "";
    }

    const std::size_t n = normalized.size();
    const std::size_t columns = square_size(input);
    const std::size_t rows = static_cast<std::size_t>(std::ceil(static_cast<double>(n) / columns));

    std::string output;
    output.reserve(columns * (rows + 1)); // rows characters plus intermediary spaces

    for (std::size_t col = 0; col < columns; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            const std::size_t idx = row * columns + col;
            if (idx < n) {
                output.push_back(normalized[idx]);
            } else {
                output.push_back(' ');
            }
        }
        if (col + 1 < columns) {
            output.push_back(' ');
        }
    }

    return output;
}

}  // namespace crypto_square

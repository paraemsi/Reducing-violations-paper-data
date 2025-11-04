#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <utility>

namespace crypto_square {

namespace {

bool is_valid_char(char ch) {
    return std::isalnum(static_cast<unsigned char>(ch));
}

std::pair<std::size_t, std::size_t> rectangle_dimensions(std::size_t len) {
    if (len == 0) {
        return {0, 0};
    }
    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(len)));
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(len)));
    if (r * c < len) {
        ++r;
    }
    return {r, c};
}

} // namespace

std::string normalize_plain_text(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (char ch : text) {
        if (is_valid_char(ch)) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

std::vector<std::string> plaintext_segments(const std::string& text) {
    const std::string normalized = normalize_plain_text(text);
    const std::size_t len = normalized.size();
    auto [r, c] = rectangle_dimensions(len);

    std::vector<std::string> segments;
    segments.reserve(r);

    for (std::size_t i = 0; i < len; i += c) {
        segments.emplace_back(normalized.substr(i, std::min<std::size_t>(c, len - i)));
    }

    return segments;
}

std::string cipher_text(const std::string& text) {
    const auto segments = plaintext_segments(text);
    if (segments.empty()) {
        return {};
    }

    const std::size_t rows = segments.size();
    std::size_t cols = 0;
    for (const auto& s : segments) {
        cols = std::max(cols, s.size());
    }

    std::string result;
    result.reserve(rows * cols);

    for (std::size_t c = 0; c < cols; ++c) {
        for (std::size_t r = 0; r < rows; ++r) {
            if (c < segments[r].size()) {
                result.push_back(segments[r][c]);
            }
        }
    }

    return result;
}

std::string normalized_cipher_text(const std::string& text) {
    const std::string normalized = normalize_plain_text(text);
    const std::size_t len = normalized.size();
    if (len == 0) {
        return {};
    }

    auto [r, c] = rectangle_dimensions(len);
    const std::string cipher = cipher_text(text);

    std::string output;
    output.reserve(c * (r + 1)); // account for spaces

    for (std::size_t i = 0; i < c; ++i) {
        if (i != 0) {
            output.push_back(' ');
        }
        const std::size_t start = i * r;
        std::string chunk = cipher.substr(start, r);
        if (chunk.size() < r) {
            chunk.append(r - chunk.size(), ' ');
        }
        output += chunk;
    }

    return output;
}

cipher::cipher(std::string text) : text_(std::move(text)) {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(text_);
}

std::vector<std::string> cipher::plaintext_segments() const {
    return crypto_square::plaintext_segments(text_);
}

std::string cipher::cipher_text() const {
    return crypto_square::cipher_text(text_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalized_cipher_text(text_);
}

}  // namespace crypto_square

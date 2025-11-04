#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>

namespace crypto_square {

namespace {

// helper: compute rows and columns
static std::pair<std::size_t, std::size_t> dimensions(std::size_t len) {
    if (len == 0) return {0, 0};

    const std::size_t root = static_cast<std::size_t>(std::sqrt(len));
    std::size_t rows = root;
    std::size_t cols = root;

    if (rows * cols < len) {
        ++cols;
    }
    if (rows * cols < len) {
        ++rows;
    }
    return {rows, cols};
}

} // namespace

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

std::vector<std::string> plain_text_segments(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const auto [rows, cols] = dimensions(normalized.size());

    std::vector<std::string> segments;
    segments.reserve(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        const std::size_t start = i * cols;
        segments.emplace_back(normalized.substr(start, cols));
    }
    return segments;
}

std::string cipher_text(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const auto [rows, cols] = dimensions(normalized.size());
    if (rows == 0) return "";

    std::string cipher;
    cipher.reserve(normalized.size());

    for (std::size_t c = 0; c < cols; ++c) {
        for (std::size_t r = 0; r < rows; ++r) {
            const std::size_t pos = r * cols + c;
            if (pos < normalized.size()) {
                cipher.push_back(normalized[pos]);
            }
        }
    }
    return cipher;
}

std::string normalized_cipher_text(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const auto [rows, cols] = dimensions(normalized.size());
    if (rows == 0) return "";

    std::ostringstream oss;

    for (std::size_t c = 0; c < cols; ++c) {
        if (c != 0) {
            oss << ' ';
        }
        for (std::size_t r = 0; r < rows; ++r) {
            const std::size_t pos = r * cols + c;
            if (pos < normalized.size()) {
                oss << normalized[pos];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

// ------------------------------------------------------------------
// cipher class member definitions
cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(text_);
}

std::vector<std::string> cipher::plain_text_segments() const {
    return crypto_square::plain_text_segments(text_);
}

std::string cipher::cipher_text() const {
    return crypto_square::cipher_text(text_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalized_cipher_text(text_);
}

}  // namespace crypto_square

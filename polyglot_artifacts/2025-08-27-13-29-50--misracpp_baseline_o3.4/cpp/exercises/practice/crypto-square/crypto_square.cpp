#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>   // for std::pair

namespace crypto_square {

namespace {

// helper : compute rows (r) and columns (c) satisfying requirements
std::pair<std::size_t, std::size_t> compute_rectangle(std::size_t len) {
    if (len == 0) return {0, 0};

    const auto root   = std::sqrt(static_cast<double>(len));
    std::size_t rows  = static_cast<std::size_t>(std::floor(root));
    std::size_t cols  = static_cast<std::size_t>(std::ceil(root));

    if (rows * cols < len) {
        ++rows;                       // guarantee enough space
    }
    return {rows, cols};
}

} // namespace

std::string normalize_plain_text(const std::string &input) {
    std::string out;
    out.reserve(input.size());
    for (unsigned char ch : input) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

std::vector<std::string> plain_text_segments(const std::string &input) {
    const std::string normalized = normalize_plain_text(input);
    const auto [rows, cols]      = compute_rectangle(normalized.size());

    std::vector<std::string> segments;
    segments.reserve(rows);

    for (std::size_t i = 0; i < normalized.size(); i += cols) {
        segments.emplace_back(normalized.substr(i, cols));
    }
    return segments;
}

std::string cipher_text(const std::string &input) {
    const auto segments = plain_text_segments(input);
    if (segments.empty()) return {};

    const std::size_t cols = segments.front().size();
    const std::size_t rows = segments.size();

    std::string cipher;
    cipher.reserve(rows * cols);

    for (std::size_t c = 0; c < cols; ++c) {
        for (std::size_t r = 0; r < rows; ++r) {
            if (c < segments[r].size()) {
                cipher.push_back(segments[r][c]);
            }
        }
    }
    return cipher;
}

std::string normalized_cipher_text(const std::string &input) {
    const auto segments = plain_text_segments(input);
    if (segments.empty()) return {};

    const std::size_t cols = segments.front().size();
    const std::size_t rows = segments.size();

    std::ostringstream oss;
    for (std::size_t c = 0; c < cols; ++c) {
        if (c != 0) oss << ' ';

        for (std::size_t r = 0; r < rows; ++r) {
            if (c < segments[r].size()) {
                oss << segments[r][c];
            } else {
                oss << ' ';           // pad short final rows
            }
        }
    }
    return oss.str();
}

}  // namespace crypto_square

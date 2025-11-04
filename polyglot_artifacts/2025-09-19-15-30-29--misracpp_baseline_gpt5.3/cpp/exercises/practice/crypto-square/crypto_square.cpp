#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <sstream>

namespace crypto_square {

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)) {}

std::string cipher::normalize(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

std::size_t cipher::size() const noexcept {
    if (normalized_.empty()) return 0;
    double root = std::sqrt(static_cast<double>(normalized_.size()));
    return static_cast<std::size_t>(std::ceil(root));
}

std::size_t cipher::rows() const noexcept {
    std::size_t c = size();
    if (c == 0) return 0;
    std::size_t n = normalized_.size();
    return (n + c - 1) / c; // ceil(n / c)
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    if (normalized_.empty()) return segments;
    std::size_t c = size();
    for (std::size_t i = 0; i < normalized_.size(); i += c) {
        segments.push_back(normalized_.substr(i, c));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_.empty()) return "";
    auto segments = plain_text_segments();
    std::size_t c = size();
    std::size_t r = segments.size();
    std::string out;
    out.reserve(normalized_.size());
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::string& seg = segments[row];
            if (col < seg.size()) {
                out.push_back(seg[col]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) return "";
    auto segments = plain_text_segments();
    std::size_t c = size();
    std::size_t r = segments.size();
    std::ostringstream oss;
    for (std::size_t col = 0; col < c; ++col) {
        if (col > 0) oss << ' ';
        for (std::size_t row = 0; row < r; ++row) {
            const std::string& seg = segments[row];
            if (col < seg.size()) {
                oss << seg[col];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

}  // namespace crypto_square

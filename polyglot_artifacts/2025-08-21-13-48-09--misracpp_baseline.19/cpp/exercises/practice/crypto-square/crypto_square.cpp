#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>
#include <string>

namespace crypto_square {

static std::string normalize(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            result += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return result;
}

cipher::cipher(const std::string& text) {
    normalized = normalize(text);
    size_t len = normalized.size();
    if (len == 0) {
        r = c = 0;
        return;
    }
    c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    r = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (r * c < len) ++r;
    if (c < r) std::swap(c, r);
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

size_t cipher::size() const {
    return c;
}

size_t cipher::plaintext_segments() const {
    return r;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    if (normalized.empty()) return segments;
    for (size_t i = 0; i < normalized.size(); i += c) {
        segments.push_back(normalized.substr(i, c));
    }
    return segments;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    std::vector<std::string> segments = plain_text_segments();
    std::string result;
    for (size_t col = 0; col < c; ++col) {
        if (col > 0) result += " ";
        for (size_t row = 0; row < r; ++row) {
            if (col < segments[row].size())
                result += segments[row][col];
            else
                result += ' ';
        }
    }
    return result;
}

}  // namespace crypto_square

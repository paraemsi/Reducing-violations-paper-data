#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

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

cipher::cipher(const std::string& text) : normalized_(normalize(text)) {}

std::string cipher::normalized_cipher_text() const {
    size_t len = normalized_.size();
    if (len == 0) return "";

    // Find r and c
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (r * c < len) ++r;
    if (c < r) std::swap(c, r);

    // Pad norm to r*c with spaces
    std::string norm = normalized_;
    norm.resize(r * c, ' ');

    // Read down columns, left to right, to form c chunks of r length
    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            chunk += norm[row * c + col];
        }
        chunks.push_back(chunk);
    }

    // Join with spaces
    std::string result;
    for (size_t i = 0; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1 < chunks.size()) result += " ";
    }
    return result;
}

}  // namespace crypto_square

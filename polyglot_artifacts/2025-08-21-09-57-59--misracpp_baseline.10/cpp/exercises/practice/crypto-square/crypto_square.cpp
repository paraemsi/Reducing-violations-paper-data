#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>
#include <sstream>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input: remove non-alphanumeric, downcase
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_ += std::tolower(static_cast<unsigned char>(ch));
        }
    }
}

std::string cipher::normalized_cipher_text() const {
    size_t len = normalized_.size();
    if (len == 0) return "";

    // Determine rectangle size: c >= r, c - r <= 1, r * c >= len
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::floor(std::sqrt(len)));
    if (r * c < len) ++r;
    if (c < r) std::swap(c, r);

    // Pad normalized text to fit rectangle
    std::string padded = normalized_;
    size_t padded_len = r * c;
    padded.append(padded_len - len, ' ');

    // Build the output by reading columns
    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            chunk += padded[row * c + col];
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    std::ostringstream oss;
    for (size_t i = 0; i < chunks.size(); ++i) {
        oss << chunks[i];
        if (i + 1 < chunks.size()) oss << " ";
    }
    return oss.str();
}

}  // namespace crypto_square

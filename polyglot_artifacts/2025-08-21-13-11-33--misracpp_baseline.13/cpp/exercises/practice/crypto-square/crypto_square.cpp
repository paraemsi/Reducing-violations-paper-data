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

cipher::cipher(const std::string& text)
    : normalized_(normalize(text))
{
    // Precompute encoded_ for normalized_cipher_text()
    size_t len = normalized_.size();
    if (len == 0) {
        encoded_ = "";
        return;
    }

    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = static_cast<size_t>(std::ceil(static_cast<double>(len) / c));
    if (c < r) std::swap(c, r);

    std::string padded = normalized_;
    padded.resize(r * c, ' ');

    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            chunk += padded[row * c + col];
        }
        chunks.push_back(chunk);
    }

    std::string result;
    for (size_t i = 0; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1 < chunks.size()) result += " ";
    }
    encoded_ = result;
}

std::string cipher::normalized_cipher_text() const {
    return encoded_;
}

}  // namespace crypto_square

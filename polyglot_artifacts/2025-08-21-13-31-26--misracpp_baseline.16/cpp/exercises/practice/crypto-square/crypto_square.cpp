#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>
#include <sstream>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize: remove non-alphanum, to lower
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_ += std::tolower(static_cast<unsigned char>(ch));
        }
    }
}

std::string cipher::normalized_cipher_text() const {
    size_t len = normalized_.size();
    if (len == 0) return "";

    // Determine rectangle size
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = c;
    if ((c - 1) * c >= len) {
        r = c - 1;
    }

    // Pad normalized string to fit rectangle
    std::string padded = normalized_;
    size_t padded_len = r * c;
    if (padded.size() < padded_len) {
        padded.append(padded_len - padded.size(), ' ');
    }

    // Read down columns, left to right
    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            chunk += padded[row * c + col];
        }
        chunks.push_back(chunk);
    }

    // Join with spaces
    std::ostringstream oss;
    for (size_t i = 0; i < chunks.size(); ++i) {
        oss << chunks[i];
        if (i + 1 < chunks.size()) oss << " ";
    }
    return oss.str();
}

}  // namespace crypto_square

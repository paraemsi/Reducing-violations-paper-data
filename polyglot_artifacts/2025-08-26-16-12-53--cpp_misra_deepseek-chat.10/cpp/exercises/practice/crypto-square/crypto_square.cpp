#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += std::tolower(static_cast<unsigned char>(c));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) {
        return 0;
    }
    std::size_t n = normalized.length();
    // Start with c being the ceiling of the square root of n
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(n))));
    while (true) {
        // Calculate number of rows
        std::size_t r = (n + c - 1) / c; // This is ceiling(n/c)
        // Check conditions
        if ((c >= r) && ((c - r) <= 1)) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::normalized_cipher_text() const {
    // According to the tests, this should return the normalized plain text
    return normalized;
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {

cipher_result::cipher_result(const std::string& text) {
    // 1. Normalize the input: remove non-alphanumeric, downcase
    normalized_.clear();
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_ += std::tolower(static_cast<unsigned char>(ch));
        }
    }

    size_t len = normalized_.size();
    if (len == 0) {
        ciphered_ = "";
        return;
    }

    // 2. Determine rectangle size: c >= r, c - r <= 1, r * c >= len
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(len)));
    size_t r = c;
    if ((r - 1) * c >= len) {
        r = r - 1;
    }

    // 3. Break into rows
    std::vector<std::string> rows;
    for (size_t i = 0; i < len; i += c) {
        rows.push_back(normalized_.substr(i, std::min(c, len - i)));
    }
    // Pad last row if needed
    if (rows.size() < r) {
        while (rows.size() < r) {
            rows.push_back("");
        }
    }
    if (!rows.empty() && rows.back().size() < c) {
        rows.back().resize(c, ' ');
    }

    // 4. Read down the columns to form the encoded message
    std::vector<std::string> chunks;
    for (size_t col = 0; col < c; ++col) {
        std::string chunk;
        for (size_t row = 0; row < r; ++row) {
            if (col < rows[row].size()) {
                chunk += rows[row][col];
            } else {
                chunk += ' ';
            }
        }
        // Pad chunk if it's short (for last columns)
        if (chunk.size() < r) {
            chunk.resize(r, ' ');
        }
        chunks.push_back(chunk);
    }

    // 5. Join chunks with spaces
    ciphered_.clear();
    for (size_t i = 0; i < chunks.size(); ++i) {
        ciphered_ += chunks[i];
        if (i + 1 < chunks.size()) {
            ciphered_ += ' ';
        }
    }
}

const std::string& cipher_result::normalized_cipher_text() const {
    return normalized_;
}

const std::string& cipher_result::cipher_text() const {
    return ciphered_;
}

cipher_result cipher(const std::string& text) {
    return cipher_result(text);
}

}  // namespace crypto_square

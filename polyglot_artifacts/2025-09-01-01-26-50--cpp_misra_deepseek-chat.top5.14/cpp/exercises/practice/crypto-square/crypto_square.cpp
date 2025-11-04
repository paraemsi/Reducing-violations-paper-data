#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized.push_back(std::tolower(static_cast<unsigned char>(ch)));
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
    const std::size_t length = normalized.size();
    // Find the smallest c that satisfies the conditions
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / static_cast<double>(c)));
    
    // Adjust to meet all conditions
    while (true) {
        if ((c >= r) && ((c - r) <= 1)) {
            break;
        }
        // If conditions aren't met, increase c and recalculate r
        c++;
        r = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / static_cast<double>(c)));
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < normalized.size(); i += c) {
        if (i != 0) {
            result.push_back(' ');
        }
        // Get up to c characters
        result.append(normalized.substr(i, c));
    }
    return result;
}

std::string cipher::cipher_text() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t length = normalized.size();
    const std::size_t r = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / static_cast<double>(c)));
    
    // Build the encoded text by reading down the columns
    std::string encoded;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t index = (row * c) + col;
            if (index < length) {
                encoded.push_back(normalized[index]);
            } else {
                // No padding for cipher_text()
                // According to the instructions, cipher_text() should be without spaces
                // But the example shows padding with spaces? Wait, the instructions say:
                // "Output the encoded text in chunks that fill perfect rectangles (r X c), with c chunks of r length, separated by spaces."
                // This is for normalized_cipher_text(), not cipher_text()
                // So cipher_text() should be the raw encoded text without spaces
                // Let's not add anything
            }
        }
    }
    return encoded;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t length = normalized.size();
    const std::size_t r = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / static_cast<double>(c)));
    
    // Build the encoded text by reading down the columns, padding with spaces where necessary
    std::vector<std::string> columns(c);
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            const std::size_t index = (row * c) + col;
            if (index < length) {
                columns[col].push_back(normalized[index]);
            } else {
                columns[col].push_back(' ');
            }
        }
    }
    
    // Join each column's string with spaces between them
    std::string result;
    for (std::size_t i = 0; i < columns.size(); ++i) {
        if (i != 0) {
            result.push_back(' ');
        }
        result.append(columns[i]);
    }
    return result;
}

}  // namespace crypto_square

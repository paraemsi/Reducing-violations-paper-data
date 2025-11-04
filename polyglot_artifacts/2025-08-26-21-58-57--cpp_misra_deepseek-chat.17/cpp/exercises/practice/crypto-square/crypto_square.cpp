#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
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

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    const std::size_t n = normalized.size();
    if (n == 0) return segments;
    
    // Determine number of columns (c) and rows (r)
    // Find the smallest c that satisfies:
    // r = ceil(n / c)
    // c >= r
    // c - r <= 1
    std::size_t c = 0;
    for (std::size_t temp_c = 1; temp_c <= n; ++temp_c) {
        std::size_t temp_r = (n + temp_c - 1) / temp_c; // Ceiling division
        if (temp_c >= temp_r && (temp_c - temp_r) <= 1) {
            c = temp_c;
            break;
        }
    }
    
    // Now split into rows, each of length c, padding the last row if necessary
    std::size_t r = (n + c - 1) / c; // Ceiling division
    for (std::size_t i = 0; i < r; ++i) {
        std::size_t start = i * c;
        std::size_t length = std::min(c, n - start);
        std::string segment = normalized.substr(start, length);
        // Pad with spaces if necessary
        if (length < c) {
            segment += std::string(c - length, ' ');
        }
        segments.push_back(segment);
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const auto segments = plain_text_segments();
    if (segments.empty()) return "";
    
    std::string result;
    std::size_t c = segments[0].size();
    std::size_t r = segments.size();
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            result += segments[row][col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    const std::string ct = cipher_text();
    if (ct.empty()) return "";
    
    const auto segments = plain_text_segments();
    std::size_t r = segments.size();
    
    // Split into chunks of r characters and join with spaces
    std::string result;
    for (std::size_t i = 0; i < ct.size(); i += r) {
        if (!result.empty()) {
            result += ' ';
        }
        result += ct.substr(i, r);
    }
    return result;
}

}  // namespace crypto_square

#include "crypto_square.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>

namespace crypto_square {

cipher::cipher(const std::string& text) {
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
    if (normalized.empty()) {
        return {};
    }
    
    const size_t length = normalized.length();
    // Determine number of rows and columns
    size_t r = static_cast<size_t>(std::floor(std::sqrt(length)));
    size_t c = r;
    
    // Adjust to meet the conditions
    while (r * c < length) {
        if (c == r) {
            c++;
        } else {
            r++;
        }
    }
    
    // Split into rows, padding if necessary
    std::vector<std::string> segments;
    for (size_t i = 0; i < r; i++) {
        size_t start = i * c;
        if (start < length) {
            size_t end = std::min(start + c, length);
            std::string segment = normalized.substr(start, end - start);
            // Pad with spaces if needed
            if (segment.length() < c) {
                segment += std::string(c - segment.length(), ' ');
            }
            segments.push_back(segment);
        } else {
            segments.push_back(std::string(c, ' '));
        }
    }
    return segments;
}

std::string cipher::cipher_text() const {
    auto segments = plain_text_segments();
    if (segments.empty()) {
        return "";
    }
    
    std::string result;
    for (size_t i = 0; i < segments[0].size(); i++) {
        for (size_t j = 0; j < segments.size(); j++) {
            result += segments[j][i];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    auto segments = plain_text_segments();
    if (segments.empty()) {
        return "";
    }
    
    const size_t r = segments.size();
    const size_t c = segments[0].size();
    
    // Build the result by reading down each column
    std::string result;
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            result += segments[row][col];
        }
        // Add space between columns, but not after the last one
        if (col < c - 1) {
            result += ' ';
        }
    }
    return result;
}

}  // namespace crypto_square

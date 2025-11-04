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
    if (normalized.empty()) {
        return {};
    }
    
    const size_t length = normalized.size();
    // Determine number of columns and rows
    size_t r = static_cast<size_t>(std::floor(std::sqrt(static_cast<double>(length))));
    size_t c = r;
    
    // Adjust to meet conditions
    while (r * c < length) {
        // Increase c first
        c++;
        // Check if c - r > 1, then we need to increase r instead
        if (c - r > 1) {
            r++;
            c = r;
        }
    }
    
    // Organize into segments
    std::vector<std::string> segments;
    for (size_t i = 0; i < r; i++) {
        size_t start = i * c;
        size_t end = std::min(start + c, length);
        segments.emplace_back(normalized.substr(start, end - start));
    }
    
    return segments;
}

std::string cipher::cipher_text() const {
    const auto segments = plain_text_segments();
    if (segments.empty()) {
        return "";
    }
    
    const size_t c = segments[0].size();
    const size_t r = segments.size();
    std::string result;
    
    // Read down the columns to get the cipher text
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            // Check if the current column is within the current row's length
            if (col < segments[row].size()) {
                result += segments[row][col];
            }
            // No padding for cipher_text
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    const auto segments = plain_text_segments();
    if (segments.empty()) {
        return "";
    }
    
    const size_t r = segments.size();
    const size_t c = segments[0].size();
    std::string result;
    
    // For each column, read down all rows
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            // Add character or space if the segment is shorter
            if (col < segments[row].size()) {
                result += segments[row][col];
            } else {
                result += ' ';
            }
        }
        // Add space between columns, but not after the last one
        if (col < c - 1) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

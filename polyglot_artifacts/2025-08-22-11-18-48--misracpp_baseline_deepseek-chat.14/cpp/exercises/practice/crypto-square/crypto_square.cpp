#include "crypto_square.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <functional>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::vector<std::string> cipher::plain_text_segments() const {
    size_t length = normalized.size();
    if (length == 0) return {};
    
    // Determine number of columns (c) and rows (r)
    size_t c = 0;
    size_t r = 0;
    
    // Find the smallest c where c >= r and c - r <= 1, and r * c >= length
    // Start from the ceiling of the square root
    c = static_cast<size_t>(std::ceil(std::sqrt(length)));
    // Adjust to find the right c and r
    while (true) {
        r = (length + c - 1) / c; // This is ceiling(length / c)
        if (c >= r && (c - r) <= 1) {
            break;
        }
        c++;
    }
    
    // Split into segments of length c (no padding)
    std::vector<std::string> segments;
    for (size_t i = 0; i < length; i += c) {
        segments.push_back(normalized.substr(i, c));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    size_t length = normalized.size();
    if (length == 0) return "";
    
    // Get the plain text segments to determine the grid
    auto segments = plain_text_segments();
    size_t c = segments.size() > 0 ? segments[0].size() : 0;
    size_t r = segments.size();
    
    // Read down the columns to get the cipher text
    std::string result;
    for (size_t i = 0; i < c; i++) {
        for (size_t j = 0; j < r; j++) {
            if (i < segments[j].size()) {
                result += segments[j][i];
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    size_t length = normalized.size();
    if (length == 0) return "";
    
    // Get the plain text segments to determine the grid
    auto segments = plain_text_segments();
    size_t c = segments.size() > 0 ? segments[0].size() : 0;
    size_t r = segments.size();
    
    // Read down the columns to form the encoded text, padding with spaces where necessary
    // We'll have c chunks, each of length r
    std::vector<std::string> chunks(c);
    for (size_t i = 0; i < c; i++) {
        for (size_t j = 0; j < r; j++) {
            // Check if the current position exists in the original text
            if (j * c + i < length) {
                chunks[i] += normalized[j * c + i];
            } else {
                chunks[i] += ' ';
            }
        }
    }
    
    // Join the chunks with spaces
    std::string result;
    for (size_t i = 0; i < chunks.size(); i++) {
        if (i != 0) {
            result += ' ';
        }
        result += chunks[i];
    }
    return result;
}

}  // namespace crypto_square

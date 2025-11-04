#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

int cipher::determine_columns() const {
    int length = normalized.length();
    if (length == 0) return 0;
    // The number of columns is the ceiling of the square root of the length
    return static_cast<int>(std::ceil(std::sqrt(length)));
}

int cipher::determine_rows() const {
    int length = normalized.length();
    if (length == 0) return 0;
    int c = determine_columns();
    // Calculate number of rows needed (ceiling of length / columns)
    return (length + c - 1) / c;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    int c = determine_columns();
    int r = determine_rows();
    
    for (int i = 0; i < r; i++) {
        int start = i * c;
        int end = std::min(start + c, static_cast<int>(normalized.length()));
        segments.push_back(normalized.substr(start, end - start));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized.empty()) return "";
    
    int c = determine_columns();
    int r = determine_rows();
    
    // Pad the normalized string to fill the rectangle
    std::string padded = normalized;
    padded.resize(r * c, ' ');
    
    // Read down the columns
    std::string result;
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            result += padded[row * c + col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    
    std::string ct = cipher_text();
    int c = determine_columns();
    int r = determine_rows();
    
    // Split into c chunks of r characters, separated by spaces
    std::string result;
    for (int i = 0; i < c; i++) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

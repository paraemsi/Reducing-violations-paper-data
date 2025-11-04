#include "crypto_square.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
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

std::vector<unsigned int> cipher::plain_text_segment_sizes() const {
    int length = normalized.size();
    if (length == 0) return std::vector<unsigned int>();
    
    // Find c and r that meet the conditions
    int c = static_cast<int>(std::ceil(std::sqrt(length)));
    int r = static_cast<int>(std::ceil(static_cast<double>(length) / c));
    
    // Adjust to meet conditions: c >= r and c - r <= 1
    // If not, find the right c
    while (true) {
        if (c >= r && (c - r) <= 1) {
            break;
        }
        // Increase c to make sure c >= r and c - r <= 1
        c++;
        r = static_cast<int>(std::ceil(static_cast<double>(length) / c));
    }
    return {static_cast<unsigned int>(c)};
}

std::vector<std::string> cipher::plain_text_segments() const {
    int length = normalized.size();
    if (length == 0) return std::vector<std::string>();
    
    // Find c and r using the same logic as above
    int c = static_cast<int>(std::ceil(std::sqrt(length)));
    int r = static_cast<int>(std::ceil(static_cast<double>(length) / c));
    while (true) {
        if (c >= r && (c - r) <= 1) {
            break;
        }
        c++;
        r = static_cast<int>(std::ceil(static_cast<double>(length) / c));
    }
    
    std::vector<std::string> segments;
    for (int i = 0; i < r; i++) {
        int start = i * c;
        if (start < length) {
            int segment_length = std::min(c, length - start);
            std::string segment = normalized.substr(start, segment_length);
            // Pad with spaces if necessary
            if (segment_length < c) {
                segment += std::string(c - segment_length, ' ');
            }
            segments.push_back(segment);
        }
    }
    return segments;
}

std::string cipher::cipher_text() const {
    auto segments = plain_text_segments();
    if (segments.empty()) return "";
    
    int c = segments[0].size();
    int r = segments.size();
    
    std::string result;
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            result += segments[row][col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    if (ct.empty()) return "";
    
    // Number of chunks is equal to number of columns in the original grid
    // Each chunk has size equal to number of rows
    auto segments = plain_text_segments();
    if (segments.empty()) return "";
    int r = segments.size();
    
    // Split into chunks of size r
    std::string result;
    for (size_t i = 0; i < ct.size(); i += r) {
        if (i != 0) {
            result += ' ';
        }
        result += ct.substr(i, r);
    }
    return result;
}

}  // namespace crypto_square

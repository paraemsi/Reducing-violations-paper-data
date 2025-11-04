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

int cipher::determine_columns() const {
    size_t length = normalized.length();
    if (length == 0) return 0;
    
    // Find the smallest c such that c >= r, c - r <= 1, and r * c >= length
    // Start by finding the ideal number of rows and columns
    // Since c >= r and c - r <= 1, c is either equal to r or r + 1
    // Let's find r first, which is the floor of the square root
    int r = static_cast<int>(std::floor(std::sqrt(length)));
    int c = r;
    
    // Adjust to meet all conditions
    if (r * c < static_cast<int>(length)) {
        c++;
    }
    if (r * c < static_cast<int>(length)) {
        r++;
    }
    // Ensure c >= r and c - r <= 1
    // Since we want the smallest c, and the conditions are satisfied
    return c;
}

int cipher::determine_rows() const {
    size_t length = normalized.length();
    if (length == 0) return 0;
    
    int c = determine_columns();
    // Number of rows is the ceiling of length / c
    int r = (static_cast<int>(length) + c - 1) / c;
    return r;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    int c = determine_columns();
    const std::string& norm = normalized;
    
    // Split into rows
    for (size_t i = 0; i < norm.length(); i += c) {
        segments.push_back(norm.substr(i, c));
    }
    
    // Pad the last segment with spaces if necessary to reach length c
    if (!segments.empty()) {
        std::string& last = segments.back();
        if (last.size() < static_cast<size_t>(c)) {
            last.append(c - last.size(), ' ');
        }
    }
    return segments;
}

std::string cipher::cipher_text() const {
    // Read down the columns to get the encoded text
    std::vector<std::string> segments = plain_text_segments();
    if (segments.empty()) return "";
    
    int c = determine_columns();
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
    
    int r = determine_rows();
    // Split into chunks of size r, which is number of rows
    // Number of chunks equals number of columns
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

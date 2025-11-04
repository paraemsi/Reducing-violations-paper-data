#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += std::tolower(static_cast<unsigned char>(ch));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    if (normalized_text.empty()) {
        return 0;
    }
    std::size_t length = normalized_text.size();
    // Find the smallest number of columns c that satisfies the conditions
    // Start with c = ceil(sqrt(length)) and find the appropriate r
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r = (length + c - 1) / c; // Ceiling division
    
    // Adjust to meet conditions: c >= r and c - r <= 1
    // Since c starts at ceiling(sqrt(length)), and r is ceiling(length/c), we need to find the right c
    // Let's find the smallest c where c >= r and c - r <= 1
    while (true) {
        r = (length + c - 1) / c;
        if ((c >= r) && ((c - r) <= 1)) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    std::string result;
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    for (std::size_t i = 0; i < normalized_text.size(); i += c) {
        if (i != 0) {
            result += " ";
        }
        result += normalized_text.substr(i, c);
    }
    return result;
}

std::string cipher::cipher_text() const {
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Ceiling division to get number of rows
    
    // Create a grid with padding
    std::vector<std::string> grid(r);
    for (std::size_t i = 0; i < r; i++) {
        std::size_t start = i * c;
        if (start < length) {
            std::size_t end = std::min(start + c, length);
            grid[i] = normalized_text.substr(start, end - start);
            // Pad with spaces if necessary
            if (grid[i].size() < c) {
                grid[i].append(c - grid[i].size(), ' ');
            }
        } else {
            grid[i] = std::string(c, ' ');
        }
    }
    
    // Read down the columns
    std::string result;
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            result += grid[row][col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    std::size_t c = size();
    if (c == 0) {
        return "";
    }
    std::size_t length = normalized_text.size();
    std::size_t r = (length + c - 1) / c; // Number of rows
    
    // Split into c chunks of size r, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < ct.size(); i += r) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i, r);
    }
    return result;
}

}  // namespace crypto_square

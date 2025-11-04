#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    
    // For empty string, set c and r to 0
    std::size_t length = normalized.length();
    if (length == 0) {
        c = 0;
        r = 0;
        return;
    }
    
    // Calculate initial number of columns (c) which is the ceiling of the square root
    c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    // Calculate number of rows (r) which is the ceiling of length / c
    r = (length + c - 1) / c;
    
    // Adjust to meet conditions: c >= r and c - r <= 1
    // If conditions are not met, we need to find the right dimensions
    // Since c is the number of columns, and we want the rectangle to be as square as possible
    while (true) {
        if ((c >= r) && ((c - r) <= 1)) {
            break;
        }
        // If not, increase c and recalculate r
        c++;
        r = (length + c - 1) / c;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    return c;
}

std::string cipher::plain_text_segments() const {
    if (normalized.empty()) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < r; i++) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * c;
        std::size_t end = std::min(start + c, normalized.length());
        result += normalized.substr(start, (end - start));
        // No padding here according to the interface
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized.empty()) {
        return "";
    }
    
    std::string result;
    // Read column-wise
    for (std::size_t col = 0; col < c; col++) {
        for (std::size_t row = 0; row < r; row++) {
            std::size_t index = row * c + col;
            if (index < normalized.length()) {
                result += normalized[index];
            } else {
                result += ' '; // Pad with space
            }
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    std::string ct = cipher_text();
    if (ct.empty()) {
        return "";
    }
    
    // Split into c chunks of r length each, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < c; i++) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input
    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized_ += std::tolower(static_cast<unsigned char>(c));
        }
    }
    
    // Handle empty string
    if (normalized_.empty()) {
        c_ = 0;
        r_ = 0;
        return;
    }
    
    const std::int32_t length = static_cast<std::int32_t>(normalized_.size());
    
    // Find the smallest c where c >= r, c - r <= 1, and r * c >= length
    // Start with c being the ceiling of the square root
    c_ = 1;
    while (c_ * c_ < length) {
        c_++;
    }
    
    // Calculate initial r
    r_ = (length + c_ - 1) / c_; // Ceiling division
    
    // Adjust if conditions aren't met
    while (!((c_ >= r_) && ((c_ - r_) <= 1))) {
        c_++;
        r_ = (length + c_ - 1) / c_;
    }
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) {
        return "";
    }
    
    const std::int32_t length = static_cast<std::int32_t>(normalized_.size());
    // Pad the string with spaces
    std::string temp = normalized_;
    temp.append((r_ * c_) - length, ' ');
    
    // Build the encoded string by reading down the columns
    std::string result;
    for (std::int32_t i = 0; i < c_; i++) {
        for (std::int32_t j = 0; j < r_; j++) {
            result += temp[j * c_ + i];
        }
        if (i < (c_ - 1)) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

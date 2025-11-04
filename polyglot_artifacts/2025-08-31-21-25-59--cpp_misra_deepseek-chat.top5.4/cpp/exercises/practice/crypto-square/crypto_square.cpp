#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_ += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    
    // Determine number of columns and rows if the normalized text is not empty
    if (!normalized_.empty()) {
        const std::uint32_t length = static_cast<std::uint32_t>(normalized_.size());
        // Start with c as the ceiling of the square root
        double sqrt_length = std::sqrt(static_cast<double>(length));
        c_ = static_cast<std::uint32_t>(std::ceil(sqrt_length));
        r_ = c_;
        
        // Adjust to meet conditions
        while (true) {
            const std::uint32_t product = r_ * c_;
            if ((product >= length) && (c_ >= r_) && ((c_ - r_) <= 1)) {
                break;
            }
            if (c_ == r_) {
                c_ = c_ + 1;
            } else {
                r_ = r_ + 1;
            }
        }
    }
}

std::string cipher::normalized_cipher_text() const {
    // Handle empty normalized text
    if (normalized_.empty()) {
        return "";
    }
    
    // Pad the normalized string with spaces
    std::string padded = normalized_;
    const std::uint32_t length = static_cast<std::uint32_t>(normalized_.size());
    const std::uint32_t target_length = r_ * c_;
    if (target_length > length) {
        padded.append(target_length - length, ' ');
    }
    
    // Build the encoded text by reading down the columns
    std::vector<std::string> chunks;
    for (std::uint32_t i = 0; i < c_; i++) {
        std::string chunk;
        for (std::uint32_t j = 0; j < r_; j++) {
            const std::uint32_t index = j * c_ + i;
            chunk += padded[index];
        }
        chunks.push_back(chunk);
    }
    
    // Join the chunks with spaces
    std::string result;
    for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(chunks.size()); i++) {
        if (i != 0) {
            result += " ";
        }
        result += chunks[i];
    }
    
    return result;
}

}  // namespace crypto_square

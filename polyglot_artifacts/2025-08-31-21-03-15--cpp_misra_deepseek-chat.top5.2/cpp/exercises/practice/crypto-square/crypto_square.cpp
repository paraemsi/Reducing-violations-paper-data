#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input during construction
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_ += std::tolower(static_cast<unsigned char>(ch));
        }
    }
}

std::string cipher::normalized_cipher_text() const {
    // Handle empty string
    if (normalized_.empty()) {
        return "";
    }
    
    const std::int32_t length = static_cast<std::int32_t>(normalized_.size());
    
    // Determine number of columns and rows
    // Find the smallest integer c where c >= ceil(sqrt(length)) and r = ceil(length/c)
    // such that c >= r and c - r <= 1
    // Start by finding the number of rows which is the integer closest to sqrt(length)
    std::int32_t r = static_cast<std::int32_t>(std::round(std::sqrt(length)));
    std::int32_t c = r;
    
    // Adjust to meet conditions
    if ((r * c) < length) {
        c++;
    }
    // Ensure c >= r and c - r <= 1
    // If conditions are not met, adjust
    while (true) {
        if ((c >= r) && ((c - r) <= 1) && ((r * c) >= length)) {
            break;
        }
        if (c < r) {
            c++;
        } else if ((c - r) > 1) {
            r++;
        } else {
            c++;
        }
    }
    
    // Pad the normalized string to make it exactly r*c characters
    std::string padded = normalized_;
    padded.append(static_cast<std::size_t>(r * c - length), ' ');
    
    // Build the encoded text by reading down the columns
    // This will give us a string of length r*c
    std::string encoded;
    for (std::int32_t i = 0; i < c; ++i) {
        for (std::int32_t j = 0; j < r; ++j) {
            encoded += padded[j * c + i];
        }
    }
    
    // Split into c chunks of r characters each, separated by spaces
    std::string result;
    for (std::int32_t i = 0; i < c; ++i) {
        if (i != 0) {
            result += ' ';
        }
        result += encoded.substr(i * r, static_cast<std::size_t>(r));
    }
    
    return result;
}

}  // namespace crypto_square

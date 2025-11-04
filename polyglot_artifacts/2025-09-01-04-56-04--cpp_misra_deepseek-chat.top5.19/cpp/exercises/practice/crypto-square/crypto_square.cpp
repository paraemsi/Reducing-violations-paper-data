#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the text
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    
    const std::uint32_t length = static_cast<std::uint32_t>(normalized_text.size());
    if (length == 0) {
        num_cols = 0;
        num_rows = 0;
        return;
    }
    
    // Find the smallest c such that c >= r, c - r <= 1, and r * c >= length
    // Start by finding the integer square root
    std::uint32_t r = static_cast<std::uint32_t>(std::sqrt(length));
    std::uint32_t c = r;
    
    // Adjust to meet all conditions
    if ((r * c) < length) {
        c = r + 1;
        if ((r * c) < length) {
            r++;
            c = r;
        }
    }
    
    // Ensure c >= r and c - r <= 1
    // At this point, we have r and c where r * c >= length
    // Now make sure c >= r and c - r <= 1
    if (c < r) {
        std::swap(r, c);
    }
    // This should always be true due to how we set them above
    num_rows = r;
    num_cols = c;
    
    // For the conditions to be exactly met, we need to ensure c - r <= 1
    // Since we may have cases where r and c are not optimal
    // Let's find the smallest c where c >= r, c - r <= 1, and r * c >= length
    // Reset to find the proper values
    // Start from the square root and find the appropriate dimensions
    num_rows = static_cast<std::uint32_t>(std::floor(std::sqrt(length)));
    num_cols = num_rows;
    while ((num_rows * num_cols) < length) {
        if (num_cols == num_rows) {
            num_cols++;
        } else {
            num_rows++;
        }
    }
    // Now we have num_rows and num_cols where num_rows * num_cols >= length
    // Check if num_cols >= num_rows and num_cols - num_rows <= 1
    // This should always be true due to how we increment them
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::uint32_t cipher::size() const {
    return num_cols;
}

std::string cipher::plain_text_segments() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::uint32_t i = 0; i < num_rows; i++) {
        if (i != 0) {
            result += " ";
        }
        std::uint32_t start = i * num_cols;
        std::uint32_t end = start + num_cols;
        if (end > normalized_text.size()) {
            result += normalized_text.substr(start);
        } else {
            result += normalized_text.substr(start, num_cols);
        }
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::uint32_t col = 0; col < num_cols; col++) {
        for (std::uint32_t row = 0; row < num_rows; row++) {
            std::uint32_t index = row * num_cols + col;
            if (index < normalized_text.size()) {
                result += normalized_text[index];
            } else {
                result += ' ';
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
    
    // Split into num_cols chunks of num_rows length, separated by spaces
    std::string result;
    for (std::uint32_t i = 0; i < num_cols; i++) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * num_rows, num_rows);
    }
    return result;
}

}  // namespace crypto_square

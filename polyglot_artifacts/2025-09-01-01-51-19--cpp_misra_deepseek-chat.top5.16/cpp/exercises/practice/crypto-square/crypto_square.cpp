#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
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
    const std::size_t length = normalized_text.size();
    // Find the smallest c such that c >= r, c - r <= 1, and c * r >= length
    // Start with c as the ceiling of the square root
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    std::size_t r = c;
    
    // Adjust to meet all conditions
    // We need to find c where c * r >= length, with r being either c or c-1 (since c >= r and c - r <= 1)
    // So r can be c-1 or c
    // Let's find which combination works
    if (c > 0) {
        if ((c * (c - 1)) >= length) {
            r = c - 1;
        } else {
            r = c;
        }
        // Make sure all conditions are satisfied
        // c >= r is always true
        // c - r <= 1 is always true in our setup
        // Check if r * c >= length
        if (r * c < length) {
            // If not, we need to increase c
            c++;
            r = c;
            // Check if we can use c-1
            if ((c * (c - 1)) >= length) {
                r = c - 1;
            } else {
                r = c;
            }
        }
    }
    return c;
}

std::string cipher::plain_text_segments() const {
    const std::size_t c = size();
    const std::size_t length = normalized_text.size();
    // Determine number of rows
    // Since c is chosen such that r*c >= length, where r is either c or c-1
    // Let's find r
    std::size_t r;
    if (c == 0) {
        r = 0;
    } else {
        // Calculate r based on conditions
        if ((c * (c - 1)) >= length) {
            r = c - 1;
        } else {
            r = c;
        }
        // Ensure r*c >= length
        if (r * c < length) {
            r = c;
        }
    }
    
    // Split into segments of length c
    std::string result;
    for (std::size_t i = 0; i < r; ++i) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * c;
        std::size_t end = std::min(start + c, length);
        result += normalized_text.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    const std::size_t c = size();
    if (c == 0) {
        return "";
    }
    const std::size_t length = normalized_text.size();
    // Determine number of rows
    std::size_t r;
    if ((c * (c - 1)) >= length) {
        r = c - 1;
    } else {
        r = c;
    }
    // Ensure r*c >= length
    if (r * c < length) {
        r = c;
    }
    
    // Pad the text to fill the rectangle
    std::string padded = normalized_text;
    padded.append(r * c - length, ' ');
    
    // Read down the columns
    std::string result;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            result += padded[row * c + col];
        }
    }
    return result;
}

std::string cipher::normalized_cipher_text() const {
    const std::string ct = cipher_text();
    if (ct.empty()) {
        return "";
    }
    const std::size_t c = size();
    const std::size_t length = normalized_text.size();
    // Determine number of rows
    std::size_t r;
    if ((c * (c - 1)) >= length) {
        r = c - 1;
    } else {
        r = c;
    }
    // Ensure r*c >= length
    if (r * c < length) {
        r = c;
    }
    
    // Split into c chunks of r characters, separated by spaces
    std::string result;
    for (std::size_t i = 0; i < c; ++i) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i * r, r);
    }
    return result;
}

}  // namespace crypto_square

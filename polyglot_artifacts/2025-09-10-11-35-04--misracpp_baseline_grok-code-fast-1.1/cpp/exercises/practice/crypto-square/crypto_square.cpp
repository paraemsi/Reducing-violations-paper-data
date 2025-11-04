#include "crypto_square.h"
#include <string>
#include <vector>
#include <cmath>
#include <cctype>

namespace crypto_square {

std::string cipher_result::normalized_cipher_text() const {
    return text_;
}

cipher_result cipher(const std::string& plaintext) {
    // Normalize: remove spaces and punctuation, downcase
    std::string normalized;
    for (char ch : plaintext) {
        if (std::isalnum(ch)) {
            normalized += std::tolower(ch);
        }
    }
    
    size_t length = normalized.size();
    if (length == 0) {
        return cipher_result{""};
    }
    
    // Find c and r
    size_t c = static_cast<size_t>(std::ceil(std::sqrt(length)));
    size_t r = (length + c - 1) / c;  // ceil(length / c)
    
    // Adjust c to satisfy c >= r and c - r <= 1
    while (c < r || c - r > 1) {
        if (c < r) {
            c++;
        } else {
            r++;
        }
        if (r * c < length) {
            c++;
        }
    }
    
    // Create the grid: r rows, each of size c
    std::vector<std::string> grid(r, std::string(c, ' '));
    size_t idx = 0;
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c && idx < length; ++j) {
            grid[i][j] = normalized[idx++];
        }
    }
    
    // Read column-wise
    std::string encoded;
    for (size_t j = 0; j < c; ++j) {
        for (size_t i = 0; i < r; ++i) {
            encoded += grid[i][j];
        }
    }
    
    // Now, output in chunks of r characters, separated by spaces
    std::string result;
    size_t chunk_size = r;
    for (size_t i = 0; i < encoded.size(); i += chunk_size) {
        if (i > 0) {
            result += " ";
        }
        std::string chunk = encoded.substr(i, chunk_size);
        // Pad with space if short
        if (chunk.size() < chunk_size) {
            chunk += std::string(chunk_size - chunk.size(), ' ');
        }
        result += chunk;
    }
    
    return cipher_result{result};
}

}  // namespace crypto_square

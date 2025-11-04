#include "crypto_square.h"
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized;
}

std::size_t cipher::size() const {
    if (normalized.empty()) return 0;
    // Determine the number of columns which is the smallest integer c where:
    // c >= ceil(sqrt(n)) and c >= r and c - r <= 1
    // Actually, we need to find c and r that satisfy:
    // r * c >= n, c >= r, c - r <= 1
    std::size_t n = normalized.size();
    // Start by finding the smallest possible c that is at least the ceiling of sqrt(n)
    // and find r = ceil(n / c)
    // Then check if c >= r and c - r <= 1
    // If not, adjust
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(n)));
    std::size_t r = (n + c - 1) / c; // Ceiling division
    
    // Check conditions
    while (!(c >= r && c - r <= 1)) {
        // Increase c until conditions are satisfied
        c++;
        r = (n + c - 1) / c;
    }
    return c;
}

std::string cipher::cipher_text() const {
    // This seems to be used internally, but the tests want normalized_cipher_text
    // Let's implement it to return the same as normalized_cipher_text without spaces
    // But according to the instructions, it might be different
    // For now, let's implement normalized_cipher_text and have cipher_text call it
    std::string result = normalized_cipher_text();
    // Remove spaces
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    
    std::size_t n = normalized.size();
    std::size_t c = size();
    std::size_t r = (n + c - 1) / c;
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    for (std::size_t i = 0; i < n; ++i) {
        grid[i / c][i % c] = normalized[i];
    }
    
    // Read down the columns to form the encoded text
    std::string encoded;
    for (std::size_t col = 0; col < c; ++col) {
        for (std::size_t row = 0; row < r; ++row) {
            encoded += grid[row][col];
        }
        // Add space between chunks, but not after the last chunk
        if (col != c - 1) {
            encoded += ' ';
        }
    }
    return encoded;
}

}  // namespace crypto_square

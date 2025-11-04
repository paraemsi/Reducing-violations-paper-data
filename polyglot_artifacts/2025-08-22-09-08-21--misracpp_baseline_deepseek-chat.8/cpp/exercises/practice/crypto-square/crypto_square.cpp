#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the text upon construction
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized_text += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    int length = normalized_text.size();
    // Determine the number of columns and rows
    int c = 0;
    int r = 0;
    
    // Find c which is the ceiling of the square root
    c = static_cast<int>(std::ceil(std::sqrt(length)));
    r = (length + c - 1) / c; // This is integer ceiling division
    
    // Adjust to meet the conditions
    // We need to ensure c >= r and c - r <= 1
    // If not, we may need to increase c
    while (true) {
        if (c >= r && (c - r) <= 1) {
            break;
        }
        // If conditions are not met, increase c and recalculate r
        c++;
        r = (length + c - 1) / c;
    }
    
    // Create the grid by reading row-wise and padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    for (int i = 0; i < length; i++) {
        grid[i / c][i % c] = normalized_text[i];
    }
    
    // Read down the columns to build the result
    std::string result;
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            result += grid[row][col];
        }
        if (col != c - 1) {
            result += ' ';
        }
    }
    
    return result;
}

}  // namespace crypto_square

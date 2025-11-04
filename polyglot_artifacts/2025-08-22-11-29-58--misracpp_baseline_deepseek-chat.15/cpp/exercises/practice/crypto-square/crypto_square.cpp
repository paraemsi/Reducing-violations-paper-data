#include "crypto_square.h"
#include <string>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>

namespace crypto_square {

cipher::cipher(const std::string& text) {
    // Normalize the input text
    for (char c : text) {
        if (std::isalnum(c)) {
            normalized_text += std::tolower(c);
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

#include <cmath>
#include <string>
#include <vector>
using namespace std;

std::size_t cipher::size() const {
    if (normalized_text.empty()) return 0;
    std::size_t n = normalized_text.size();
    // Start with c as the ceiling of the square root
    std::size_t c = ceil(sqrt(n));
    while (true) {
        std::size_t r = (n + c - 1) / c; // Ceiling division for number of rows
        if (c >= r && c - r <= 1) {
            break;
        }
        c++;
    }
    return c;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) return "";
    std::size_t n = normalized_text.size();
    std::size_t c = size();
    std::size_t r = (n + c - 1) / c; // Number of rows using ceiling division
    
    // Create a grid with r rows and c columns, padding with spaces
    std::vector<std::string> grid(r, std::string(c, ' '));
    for (std::size_t i = 0; i < n; i++) {
        grid[i / c][i % c] = normalized_text[i];
    }
    
    // Read down the columns to build the cipher text
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
    if (ct.empty()) return "";
    
    std::size_t n = normalized_text.size();
    std::size_t c = size();
    std::size_t r = (n + c - 1) / c;
    
    // Split into chunks of r characters
    std::string result;
    for (std::size_t i = 0; i < ct.size(); i++) {
        if (i != 0 && i % r == 0) {
            result += ' ';
        }
        result += ct[i];
    }
    return result;
}

}  // namespace crypto_square

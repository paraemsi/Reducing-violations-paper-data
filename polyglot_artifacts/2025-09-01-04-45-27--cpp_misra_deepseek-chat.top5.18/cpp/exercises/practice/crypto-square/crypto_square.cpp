#include "crypto_square.h"
#include <string>
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
    
    const std::size_t length = normalized_text.length();
    if (length == 0) {
        num_columns = 0;
        num_rows = 0;
        return;
    }
    
    // Find the smallest c that satisfies the conditions
    // Start with c = ceil(sqrt(length)) and adjust if necessary
    num_columns = static_cast<std::size_t>(std::ceil(std::sqrt(length)));
    num_rows = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / num_columns));
    
    // Adjust to meet c >= r and c - r <= 1
    // We need to find the right c and r
    // Let's find c such that c >= ceil(sqrt(length)) and conditions are satisfied
    // Since c must be at least ceil(sqrt(length)), and r is ceil(length/c)
    while (true) {
        if ((num_columns >= num_rows) && ((num_columns - num_rows) <= 1)) {
            break;
        }
        // If not, increase c and recalculate r
        num_columns++;
        num_rows = static_cast<std::size_t>(std::ceil(static_cast<double>(length) / num_columns));
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::size_t cipher::size() const {
    return num_columns;
}

std::string cipher::plain_text_segments() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::size_t i = 0; i < num_rows; ++i) {
        if (i != 0) {
            result += " ";
        }
        std::size_t start = i * num_columns;
        std::size_t end = std::min(start + num_columns, normalized_text.length());
        result += normalized_text.substr(start, end - start);
    }
    return result;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::string result;
    for (std::size_t col = 0; col < num_columns; ++col) {
        for (std::size_t row = 0; row < num_rows; ++row) {
            std::size_t index = row * num_columns + col;
            if (index < normalized_text.length()) {
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
    
    // Split into chunks of size num_rows (which is correct because each column has num_rows characters)
    std::string result;
    for (std::size_t i = 0; i < ct.size(); i += num_rows) {
        if (i != 0) {
            result += " ";
        }
        result += ct.substr(i, num_rows);
    }
    return result;
}

}  // namespace crypto_square

#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) : plain_text(text) {
    normalize();
}

void cipher::normalize() {
    normalized_text.clear();
    normalized_text.reserve(plain_text.size());
    
    for (char ch : plain_text) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            normalized_text.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text;
}

std::uint32_t cipher::calculate_columns() const {
    if (normalized_text.empty()) {
        return 0;
    }
    
    std::uint32_t length = static_cast<std::uint32_t>(normalized_text.size());
    std::uint32_t cols = static_cast<std::uint32_t>(std::ceil(std::sqrt(static_cast<double>(length))));
    
    return cols;
}

std::uint32_t cipher::calculate_rows(std::uint32_t cols) const {
    if ((cols == 0) || normalized_text.empty()) {
        return 0;
    }
    
    std::uint32_t length = static_cast<std::uint32_t>(normalized_text.size());
    std::uint32_t rows = cols;
    
    // Find the smallest rectangle where c >= r and c - r <= 1
    while ((rows * cols) >= length) {
        if ((cols - rows) <= 1) {
            return rows;
        }
        rows = rows - 1;
    }
    
    return rows + 1;
}

std::string cipher::cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::uint32_t cols = calculate_columns();
    std::uint32_t rows = calculate_rows(cols);
    
    if ((cols == 0) || (rows == 0)) {
        return "";
    }
    
    // Create rectangle with padding
    std::vector<std::string> rectangle;
    rectangle.reserve(rows);
    
    std::uint32_t index = 0;
    for (std::uint32_t r = 0; r < rows; ++r) {
        std::string row;
        row.reserve(cols);
        
        for (std::uint32_t c = 0; c < cols; ++c) {
            if (index < normalized_text.size()) {
                row.push_back(normalized_text[index]);
                ++index;
            } else {
                row.push_back(' ');
            }
        }
        rectangle.push_back(row);
    }
    
    // Read columns to create cipher text (no spaces)
    std::string result;
    result.reserve(cols * rows);
    
    for (std::uint32_t c = 0; c < cols; ++c) {
        for (std::uint32_t r = 0; r < rows; ++r) {
            result.push_back(rectangle[r][c]);
        }
    }
    
    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text.empty()) {
        return "";
    }
    
    std::uint32_t cols = calculate_columns();
    std::uint32_t rows = calculate_rows(cols);
    
    if ((cols == 0) || (rows == 0)) {
        return "";
    }
    
    // Create rectangle with padding
    std::vector<std::string> rectangle;
    rectangle.reserve(rows);
    
    std::uint32_t index = 0;
    for (std::uint32_t r = 0; r < rows; ++r) {
        std::string row;
        row.reserve(cols);
        
        for (std::uint32_t c = 0; c < cols; ++c) {
            if (index < normalized_text.size()) {
                row.push_back(normalized_text[index]);
                ++index;
            } else {
                row.push_back(' ');
            }
        }
        rectangle.push_back(row);
    }
    
    // Read columns to create cipher text with spaces between chunks
    std::string result;
    result.reserve((cols * rows) + cols);
    
    for (std::uint32_t c = 0; c < cols; ++c) {
        if (c > 0) {
            result.push_back(' ');
        }
        
        for (std::uint32_t r = 0; r < rows; ++r) {
            result.push_back(rectangle[r][c]);
        }
    }
    
    return result;
}

}  // namespace crypto_square

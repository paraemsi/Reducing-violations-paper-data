#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

namespace crypto_square {
    
    cipher::cipher(const std::string& text) : rows_(0), cols_(0) {
        normalize(text);
        calculate_dimensions();
    }
    
    void cipher::normalize(const std::string& text) {
        normalized_plain_text_.clear();
        for (char c : text) {
            if (std::isalnum(c)) {
                normalized_plain_text_ += std::tolower(c);
            }
        }
    }
    
    void cipher::calculate_dimensions() {
        if (normalized_plain_text_.empty()) {
            rows_ = 0;
            cols_ = 0;
            return;
        }
        
        int length = normalized_plain_text_.length();
        cols_ = std::ceil(std::sqrt(length));
        rows_ = std::ceil(static_cast<double>(length) / cols_);
        
        // Ensure c >= r and c - r <= 1
        while (rows_ > cols_) {
            cols_++;
            rows_ = std::ceil(static_cast<double>(length) / cols_);
        }
    }
    
    std::string cipher::normalized_cipher_text() const {
        return normalized_plain_text_;
    }
    
    std::string cipher::encoded() const {
        if (normalized_plain_text_.empty()) {
            return "";
        }
        
        // Create rectangle with padding
        std::vector<std::string> rectangle;
        for (int i = 0; i < rows_; i++) {
            int start = i * cols_;
            int end = std::min(start + cols_, static_cast<int>(normalized_plain_text_.length()));
            std::string row = normalized_plain_text_.substr(start, end - start);
            
            // Pad with spaces if needed
            while (row.length() < static_cast<size_t>(cols_)) {
                row += ' ';
            }
            rectangle.push_back(row);
        }
        
        // Read down columns
        std::string result;
        for (int col = 0; col < cols_; col++) {
            for (int row = 0; row < rows_; row++) {
                result += rectangle[row][col];
            }
        }
        
        return result;
    }
    
    std::string cipher::ciphertext() const {
        if (normalized_plain_text_.empty() || rows_ == 0) {
            return "";
        }
        
        std::string encoded_text = encoded();
        std::string result;
        
        // Split into chunks of r length
        for (size_t i = 0; i < encoded_text.length(); i += rows_) {
            if (i > 0) {
                result += ' ';
            }
            result += encoded_text.substr(i, rows_);
        }
        
        return result;
    }
    
}  // namespace crypto_square

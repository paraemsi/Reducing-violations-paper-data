#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cmath>

namespace crypto_square {

namespace {
using size_type = std::size_t;

std::string normalize(const std::string& text) {
    std::string result;
    for (const char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

void rectangle_size(size_type len, size_type& rows, size_type& cols) {
    // Find the smallest c such that r * c >= len, c >= r, c - r <= 1
    cols = static_cast<size_type>(std::ceil(std::sqrt(static_cast<double>(len))));
    rows = cols;
    if (((cols - 1U) * cols) >= len) {
        rows = cols - 1U;
    }
}

std::string encode(const std::string& norm, size_type rows, size_type cols) {
    if (norm.empty()) {
        return "";
    }
    // Fill the rectangle row-wise
    std::vector<std::string> rectangle;
    for (size_type i = 0U; i < norm.length(); i += cols) {
        rectangle.push_back(norm.substr(i, ((i + cols) < norm.length()) ? cols : (norm.length() - i)));
    }
    // Pad last row if needed
    if (rectangle.back().length() < cols) {
        rectangle.back() += std::string(cols - rectangle.back().length(), ' ');
    }
    // Pad with empty rows if needed
    while (rectangle.size() < rows) {
        rectangle.push_back(std::string(cols, ' '));
    }

    // Read columns to form the encoded chunks
    std::vector<std::string> chunks;
    for (size_type c = 0U; c < cols; ++c) {
        std::string chunk;
        for (size_type r = 0U; r < rows; ++r) {
            chunk += rectangle[r][c];
        }
        // Pad with trailing space if chunk is short (for incomplete columns)
        if (chunk.length() < rows) {
            chunk += std::string(rows - chunk.length(), ' ');
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    std::string result;
    for (size_type i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if ((i + 1U) < chunks.size()) {
            result += ' ';
        }
    }
    return result;
}

} // anonymous namespace

cipher_result::cipher_result(const std::string& input)
    : normalized_(normalize(input)), encoded_()
{
    if (!normalized_.empty()) {
        size_type rows = 0U;
        size_type cols = 0U;
        rectangle_size(normalized_.length(), rows, cols);
        encoded_ = encode(normalized_, rows, cols);
    }
}

std::string cipher_result::normalized_cipher_text() const {
    return normalized_;
}

std::string cipher_result::cipher_text() const {
    return encoded_;
}

cipher_result cipher(const std::string& text) {
    return cipher_result(text);
}

}  // namespace crypto_square

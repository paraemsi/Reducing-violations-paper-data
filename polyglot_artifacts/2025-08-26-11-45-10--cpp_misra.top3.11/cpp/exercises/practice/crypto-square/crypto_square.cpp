#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cmath>

namespace crypto_square {

namespace {
using string_size = std::string::size_type;

// Normalize the input: remove non-alphanum, to lower
std::string normalize(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

// Compute rectangle dimensions
void rectangle_dimensions(string_size len, string_size& rows, string_size& cols) {
    cols = static_cast<string_size>(std::ceil(std::sqrt(static_cast<double>(len))));
    rows = cols;
    if (((cols - 1U) * cols) >= len) {
        rows = cols - 1U;
    }
}

std::string encode(const std::string& norm) {
    string_size len = norm.length();
    if (len == 0U) {
        return "";
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    std::string padded = norm;
    string_size pad_len = (rows * cols) - len;
    if (pad_len > 0U) {
        padded.append(pad_len, ' ');
    }

    // Read down the columns
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            string_size idx = (r * cols) + c;
            if (idx < padded.length()) {
                chunk += padded[idx];
            }
        }
        chunks.push_back(chunk);
    }

    // Pad last n chunks with trailing space if needed
    string_size n = (rows * cols) - len;
    for (string_size i = (cols - n); i < cols; ++i) {
        if (i < chunks.size()) {
            chunks[i] += ' ';
        }
    }

    // Join with spaces
    std::string result;
    for (string_size i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1U < chunks.size()) {
            result += ' ';
        }
    }
    return result;
}

} // end anonymous namespace

cipher_result::cipher_result(const std::string& input)
    : normalized_(normalize(input)), encoded_(encode(normalized_)) {}

std::string cipher_result::normalized_cipher_text() const {
    return normalized_;
}

std::string cipher_result::ciphertext() const {
    return encoded_;
}

cipher_result cipher(const std::string& text) {
    return cipher_result(text);
}

}  // namespace crypto_square

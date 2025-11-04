#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cmath>

namespace crypto_square {

namespace {
using string_size_t = std::size_t;

// Normalize the input: remove non-alphanumerics, downcase
std::string normalize(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if ((ch >= 'A') && (ch <= 'Z')) {
            result += static_cast<char>(ch + ('a' - 'A'));
        } else if (((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9'))) {
            result += ch;
        }
    }
    return result;
}

// Compute rectangle dimensions (rows, cols)
void rectangle_dimensions(string_size_t len, string_size_t& rows, string_size_t& cols) {
    cols = static_cast<string_size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
    rows = cols;
    if (((cols - 1U) * cols) >= len) {
        rows = cols - 1U;
    }
}

std::string make_cipher_text(const std::string& norm) {
    string_size_t len = norm.length();
    if (len == 0U) {
        return "";
    }

    string_size_t rows = 0U;
    string_size_t cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    string_size_t pad = (rows * cols) - len;
    std::string padded = norm;
    if (pad > 0U) {
        padded += std::string(pad, ' ');
    }

    // Read down the columns
    std::vector<std::string> chunks;
    for (string_size_t c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size_t r = 0U; r < rows; ++r) {
            chunk += padded[(r * cols) + c];
        }
        chunks.push_back(chunk);
    }

    // Join with spaces
    std::string result;
    for (string_size_t i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1U < chunks.size()) {
            result += ' ';
        }
    }
    return result;
}

} // anonymous namespace

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)),
      cipher_text_(make_cipher_text(normalized_))
{
}

std::string cipher::normalized_cipher_text() const {
    return cipher_text_;
}

} // namespace crypto_square

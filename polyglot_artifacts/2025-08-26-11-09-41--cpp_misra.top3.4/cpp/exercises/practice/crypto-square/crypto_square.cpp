#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>

namespace crypto_square {

namespace {
using string_size = std::size_t;

// Normalize the input: remove non-alphanum, to lower
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

// Compute rectangle dimensions
void rectangle_dims(string_size len, string_size& rows, string_size& cols) {
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
    rectangle_dims(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    string_size pad = (rows * cols) - len;
    std::string padded = norm;
    if (pad > 0U) {
        padded += std::string(pad, ' ');
    }

    // Read down the columns, left to right, outputting in chunks of rows
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += padded[(r * cols) + c];
        }
        chunks.push_back(chunk);
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
    : normalized_(normalize(input)), encoded_(encode(normalized_))
{
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

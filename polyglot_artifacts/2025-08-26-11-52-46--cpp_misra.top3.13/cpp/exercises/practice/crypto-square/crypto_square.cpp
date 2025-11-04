#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

namespace crypto_square {

namespace {
using string_size_t = std::string::size_type;

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
void rectangle_dimensions(string_size_t len, string_size_t& rows, string_size_t& cols) {
    cols = static_cast<string_size_t>(std::ceil(std::sqrt(static_cast<double>(len))));
    rows = cols;
    if (((cols - 1U) * cols) >= len) {
        rows = cols - 1U;
    }
}

} // anonymous namespace

cipher_result cipher(const std::string& text) {
    std::string norm = normalize(text);
    string_size_t len = norm.length();
    if (len == 0U) {
        return cipher_result("", norm);
    }

    string_size_t rows = 0U;
    string_size_t cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    std::string padded = norm;
    string_size_t pad_len = (rows * cols) - len;
    if (pad_len > 0U) {
        padded.append(pad_len, ' ');
    }

    // Read down the columns
    std::vector<std::string> chunks;
    for (string_size_t c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size_t r = 0U; r < rows; ++r) {
            string_size_t idx = (r * cols) + c;
            if (idx < padded.length()) {
                chunk += padded[idx];
            }
        }
        chunks.push_back(chunk);
    }

    // Pad last n chunks with trailing space if needed
    string_size_t n = (rows * cols) - len;
    for (string_size_t i = (cols - n); i < cols; ++i) {
        if (i < chunks.size()) {
            chunks[i] += ' ';
        }
    }

    // Join with spaces
    std::string result;
    for (string_size_t i = 0U; i < chunks.size(); ++i) {
        if (i > 0U) {
            result += ' ';
        }
        result += chunks[i];
    }
    return cipher_result(result, norm);
}

}  // namespace crypto_square

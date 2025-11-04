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
} // anonymous namespace

cipher_result::cipher_result(const std::string& text)
    : normalized_{normalize(text)}
    , encoded_{}
{
    string_size len = normalized_.length();
    if (len == 0U) {
        encoded_ = "";
        return;
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    std::string padded = normalized_;
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

    // Join with spaces
    std::string result;
    for (string_size i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if ((i + 1U) < chunks.size()) {
            result += ' ';
        }
    }
    encoded_ = result;
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

#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

namespace crypto_square {

namespace {
using string_size = std::size_t;

std::string normalize(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

void rectangle_size(string_size len, string_size& rows, string_size& cols) {
    // Find smallest c such that r * c >= len, c >= r, c - r <= 1
    rows = 0U;
    cols = 0U;
    for (string_size c = 1U; c <= (len + 1U); ++c) {
        string_size r = (len + c - 1U) / c;
        if ((c >= r) && ((c - r) <= 1U) && ((r * c) >= len)) {
            rows = r;
            cols = c;
            break;
        }
    }
}

std::string encode(const std::string& norm) {
    string_size len = norm.length();
    if (len == 0U) {
        return "";
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_size(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    std::string padded = norm;
    string_size pad_len = (rows * cols) - len;
    if (pad_len > 0U) {
        padded += std::string(pad_len, ' ');
    }

    // Build the output by reading down the columns
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
        if ((i + 1U) < chunks.size()) {
            result += " ";
        }
    }
    return result;
}

} // anonymous namespace

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)), encoded_(encode(normalized_))
{
}

std::string cipher::normalized_cipher_text() const {
    return encoded_;
}

}  // namespace crypto_square

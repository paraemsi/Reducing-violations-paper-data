#include "crypto_square.h"
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

namespace crypto_square {

namespace {
using string_size = std::string::size_type;

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

// Compute rectangle dimensions (rows, cols) for given length
void rectangle_dimensions(string_size len, string_size& rows, string_size& cols) {
    cols = 0U;
    rows = 0U;
    for (string_size c = 1U; ; ++c) {
        string_size r = c;
        if ((c * r) < len) {
            ++r;
        }
        if (((c * r) >= len) && ((c >= r)) && ((c - r) <= 1U)) {
            cols = c;
            rows = r;
            break;
        }
    }
}

} // anonymous namespace

cipher::cipher(const std::string& text)
    : normalized_(normalize(text)), encoded_("")
{
    string_size len = normalized_.length();
    if (len == 0U) {
        encoded_ = "";
        return;
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Pad normalized text to fill the rectangle
    std::string padded = normalized_;
    string_size pad_len = (rows * cols) - len;
    if (pad_len > 0U) {
        padded += std::string(pad_len, ' ');
    }

    // Read down the columns, left to right, to form the encoded chunks
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += padded[(r * cols) + c];
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    std::string result;
    for (string_size i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if ((i + 1U) < chunks.size()) {
            result += ' ';
        }
    }
    encoded_ = result;
}

std::string cipher::normalized_cipher_text() const {
    return encoded_;
}

}  // namespace crypto_square

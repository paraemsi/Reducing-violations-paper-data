#include "crypto_square.h"
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

namespace crypto_square {

namespace {
using string_size = std::string::size_type;

// Normalize the input: remove non-alphanumeric, downcase
std::string normalize(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if ((ch >= 'A') && (ch <= 'Z')) {
            result += static_cast<char>(ch + ('a' - 'A'));
        } else if ((ch >= 'a') && (ch <= 'z')) {
            result += ch;
        } else if ((ch >= '0') && (ch <= '9')) {
            result += ch;
        } else {
            // skip
        }
    }
    return result;
}

// Compute rectangle size: find smallest c such that r*c >= len, c >= r, c - r <= 1
void rectangle_size(string_size len, string_size& rows, string_size& cols) {
    rows = 0U;
    cols = 0U;
    for (string_size c = 1U; c <= len; ++c) {
        string_size r = (len + c - 1U) / c;
        if ((c >= r) && ((c - r) <= 1U)) {
            rows = r;
            cols = c;
            return;
        }
    }
    // fallback: 1 row, len columns
    rows = 1U;
    cols = len;
}

std::string encode(const std::string& norm) {
    string_size len = norm.length();
    if (len == 0U) {
        return "";
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_size(len, rows, cols);

    // Pad with spaces to fill the rectangle
    std::string padded = norm;
    string_size pad_len = (rows * cols) - len;
    if (pad_len > 0U) {
        padded.append(pad_len, ' ');
    }

    // Read columns into output chunks
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
            result += ' ';
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

} // namespace crypto_square

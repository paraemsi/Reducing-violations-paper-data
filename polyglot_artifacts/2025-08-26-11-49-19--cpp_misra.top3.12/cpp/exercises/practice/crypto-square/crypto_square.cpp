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
    // Find the smallest c such that r * c >= len, c >= r, c - r <= 1
    string_size c = 1U;
    string_size r = 1U;
    while ((c * r) < len) {
        if ((c - r) <= 0U) {
            ++c;
        } else {
            ++r;
        }
    }
    cols = c;
    rows = r;
}

std::string encode(const std::string& normalized) {
    const string_size len = normalized.length();
    if (len == 0U) {
        return "";
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_size(len, rows, cols);

    // Fill the rectangle row-wise
    std::vector<std::string> rectangle;
    for (string_size i = 0U; i < rows; ++i) {
        string_size start = (i * cols);
        string_size end = ((start + cols) < len) ? (start + cols) : len;
        std::string row = normalized.substr(start, (end - start));
        if ((row.length()) < cols) {
            row.append((cols - row.length()), ' ');
        }
        rectangle.push_back(row);
    }

    // Read column-wise to build the encoded message
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += rectangle[r][c];
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

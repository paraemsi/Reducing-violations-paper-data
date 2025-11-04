#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
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

// Compute rectangle dimensions
void rectangle_dimensions(string_size len, string_size& rows, string_size& cols) {
    cols = 0U;
    rows = 0U;
    while ((cols * rows) < len) {
        if (cols <= rows) {
            ++cols;
        } else {
            ++rows;
        }
    }
}

} // anonymous namespace

cipher::cipher(const std::string& text)
    : normalized_(normalize(text))
{
}

std::string cipher::normalized_cipher_text() const {
    const string_size len = normalized_.length();
    if (len == 0U) {
        return "";
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Fill the rectangle row-wise
    std::vector<std::string> rectangle;
    for (string_size r = 0U; r < rows; ++r) {
        string_size start = r * cols;
        if (start >= len) {
            rectangle.push_back(std::string(cols, ' '));
        } else {
            string_size end = (start + cols < len) ? (start + cols) : len;
            std::string row = normalized_.substr(start, (end - start));
            if (row.length() < cols) {
                row += std::string(cols - row.length(), ' ');
            }
            rectangle.push_back(row);
        }
    }

    // Read column-wise and build output chunks
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += rectangle[r][c];
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

}  // namespace crypto_square

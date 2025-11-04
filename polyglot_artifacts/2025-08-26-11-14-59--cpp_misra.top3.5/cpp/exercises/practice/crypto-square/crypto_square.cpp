#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

namespace crypto_square {

cipher_result::cipher_result(const std::string& normalized, const std::string& encoded)
    : normalized_text_(normalized), encoded_text_(encoded) {}

std::string cipher_result::normalized_cipher_text() const {
    return normalized_text_;
}

std::string cipher_result::cipher_text() const {
    return encoded_text_;
}

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
        } else {
            // skip
        }
    }
    return result;
}

// Compute rectangle dimensions
void rectangle_dimensions(string_size len, string_size& rows, string_size& cols) {
    cols = 0U;
    rows = 0U;
    for (string_size c = 1U; ; ++c) {
        string_size r = c;
        if ((c * r) < len) {
            r = c + 1U;
        }
        if (((r * c) >= len) && ((c >= r)) && ((c - r) <= 1U)) {
            rows = r;
            cols = c;
            break;
        }
    }
}

} // anonymous namespace

cipher_result cipher(const std::string& text) {
    std::string norm = normalize(text);
    string_size len = norm.length();
    if (len == 0U) {
        return cipher_result("", "");
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
            std::string row = norm.substr(start, (end - start));
            if (row.length() < cols) {
                row += std::string(cols - row.length(), ' ');
            }
            rectangle.push_back(row);
        }
    }

    // Read columns to form the encoded message
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
    return cipher_result(norm, result);
}

}  // namespace crypto_square

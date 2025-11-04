#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

namespace crypto_square {

namespace {
using string_size = std::string::size_type;

// Normalize the input: remove non-alphanum, to lower
std::string normalize(const std::string& text)
{
    std::string result;
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return result;
}

// Compute rectangle size: returns {rows, cols}
std::pair<string_size, string_size> rectangle_size(string_size len)
{
    string_size c = 0U;
    string_size r = 0U;
    for (c = 1U; ; ++c) {
        r = (len + c - 1U) / c;
        if (((r * c) >= len) && ((c >= r)) && (((c - r) <= 1U))) {
            break;
        }
    }
    return std::make_pair(r, c);
}
} // anonymous namespace

cipher_result cipher(const std::string& text)
{
    const std::string norm = normalize(text);
    const string_size len = norm.length();
    if (len == 0U) {
        return cipher_result("", "");
    }

    const auto rc = rectangle_size(len);
    const string_size rows = rc.first;
    const string_size cols = rc.second;

    // Fill the rectangle row-wise
    std::vector<std::string> rectangle;
    rectangle.reserve(rows);
    for (string_size i = 0U; i < rows; ++i) {
        string_size start = (i * cols);
        string_size end = ((start + cols) < len) ? (start + cols) : len;
        std::string row = norm.substr(start, (end - start));
        if ((row.length()) < cols) {
            row.append((cols - row.length()), ' ');
        }
        rectangle.push_back(row);
    }

    // Read columns to form the encoded message
    std::vector<std::string> chunks;
    chunks.reserve(cols);
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        chunk.reserve(rows);
        for (string_size r = 0U; r < rows; ++r) {
            chunk += rectangle[r][c];
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    std::string result;
    for (string_size i = 0U; i < cols; ++i) {
        result += chunks[i];
        if ((i + 1U) < cols) {
            result += ' ';
        }
    }
    return cipher_result(result, norm);
}

}  // namespace crypto_square

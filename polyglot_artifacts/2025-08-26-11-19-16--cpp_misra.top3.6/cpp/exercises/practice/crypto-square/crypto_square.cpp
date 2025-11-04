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

cipher_result cipher(const std::string& text) {
    std::string norm = normalize(text);
    string_size len = norm.length();
    if (len == 0U) {
        return cipher_result("", norm);
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Fill the rectangle row-wise
    std::vector<std::string> rectangle;
    for (string_size i = 0U; i < len; i += cols) {
        rectangle.push_back(norm.substr(i, ((i + cols) < len) ? cols : (len - i)));
    }
    // Pad last row if needed
    if (rectangle.back().length() < cols) {
        rectangle.back() += std::string(cols - rectangle.back().length(), ' ');
    }
    // Pad with empty rows if needed
    while (rectangle.size() < rows) {
        rectangle.push_back(std::string(cols, ' '));
    }

    // Read column-wise to build output chunks
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += rectangle[r][c];
        }
        chunks.push_back(chunk);
    }

    // Pad last n chunks with trailing space if needed
    string_size n = (rows * cols) - len;
    for (string_size i = (cols - n); i < cols; ++i) {
        if (i < chunks.size()) {
            chunks[i] += ' ';
        }
    }

    // Join with spaces
    std::string result;
    for (string_size i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if ((i + 1U) < chunks.size()) {
            result += ' ';
        }
    }
    return cipher_result(result, norm);
}

}  // namespace crypto_square

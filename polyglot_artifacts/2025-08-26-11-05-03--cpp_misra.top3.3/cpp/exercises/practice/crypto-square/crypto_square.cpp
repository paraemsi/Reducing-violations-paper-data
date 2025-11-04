#include "crypto_square.h"
#include <cstdint>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>

namespace crypto_square {

namespace {
using string_size = std::string::size_type;

// Normalize the input: remove non-alphanumerics, downcase
auto normalize(const std::string& text) -> std::string {
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
    cols = static_cast<string_size>(std::ceil(std::sqrt(static_cast<double>(len))));
    rows = cols;
    if (((cols - 1U) * cols) >= len) {
        rows = cols - 1U;
    }
}

} // end anonymous namespace

auto cipher(const std::string& text) -> cipher_result {
    std::string norm = normalize(text);
    string_size len = norm.length();
    if (len == 0U) {
        return cipher_result("", "");
    }

    string_size rows = 0U;
    string_size cols = 0U;
    rectangle_dimensions(len, rows, cols);

    // Pad the normalized string to fill the rectangle
    string_size pad = (rows * cols) - len;
    if (pad > 0U) {
        norm += std::string(pad, ' ');
    }

    // Read down the columns to form the encoded chunks
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += norm[(r * cols) + c];
        }
        chunks.push_back(chunk);
    }

    // Join chunks with spaces
    std::string result;
    for (string_size i = 0U; i < chunks.size(); ++i) {
        result += chunks[i];
        if (i + 1U < chunks.size()) {
            result += ' ';
        }
    }
    return cipher_result(result, normalize(text));
}

}  // namespace crypto_square

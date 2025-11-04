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

// Compute rectangle dimensions (rows, cols) for the crypto square
void rectangle_dimensions(string_size len, string_size& rows, string_size& cols) {
    cols = static_cast<string_size>(std::ceil(std::sqrt(static_cast<double>(len))));
    rows = cols;
    if (((cols - 1U) * cols) >= len) {
        rows = cols - 1U;
    }
}

std::string encode(const std::string& norm, string_size rows, string_size cols) {
    string_size len = norm.length();
    // Fill the rectangle row-wise
    std::vector<std::string> rectangle;
    for (string_size i = 0U; i < len; i += cols) {
        rectangle.push_back(norm.substr(i, ((i + cols) < len) ? cols : (len - i)));
    }
    // Pad last row if needed
    if ((!rectangle.empty()) && (rectangle.back().length() < cols)) {
        rectangle.back() += std::string(cols - rectangle.back().length(), ' ');
    }
    // Pad with empty rows if needed
    while (rectangle.size() < rows) {
        rectangle.push_back(std::string(cols, ' '));
    }

    // Read columns to form the encoded message
    std::vector<std::string> chunks;
    for (string_size c = 0U; c < cols; ++c) {
        std::string chunk;
        for (string_size r = 0U; r < rows; ++r) {
            chunk += rectangle[r][c];
        }
        // Pad with space if chunk is short (for perfect rectangle)
        if (chunk.length() < rows) {
            chunk += std::string(rows - chunk.length(), ' ');
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
    return result;
}

} // anonymous namespace

class cipher_result::impl {
public:
    impl(const std::string& text)
        : normalized_(normalize(text))
        , ciphered_()
    {
        if (!normalized_.empty()) {
            string_size rows = 0U;
            string_size cols = 0U;
            rectangle_dimensions(normalized_.length(), rows, cols);
            ciphered_ = encode(normalized_, rows, cols);
        }
    }

    std::string normalized_;
    std::string ciphered_;
};

cipher_result::cipher_result(const std::string& text)
    : pimpl_(new impl(text))
{
}

cipher_result::~cipher_result() = default;

std::string cipher_result::normalized_cipher_text() const {
    return pimpl_->normalized_;
}

std::string cipher_result::cipher_text() const {
    return pimpl_->ciphered_;
}

cipher_result cipher(const std::string& text) {
    return cipher_result(text);
}

}  // namespace crypto_square

#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <utility>

namespace crypto_square {

namespace {

// Remove non-alphanumeric characters and convert to lowercase
std::string normalize(const std::string& input) {
    std::string out;
    out.reserve(input.size());
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return out;
}

// Compute rectangle dimensions (rows, columns)
std::pair<std::size_t, std::size_t> rectangle_size(std::size_t len) {
    if (len == 0) {
        return {0, 0};
    }
    double root = std::sqrt(static_cast<double>(len));
    std::size_t r = static_cast<std::size_t>(std::floor(root));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    if (r * c < len) {
        ++r;                // ensure enough rows
    }
    return {r, c};
}

} // namespace

std::string normalize_plain_text(const std::string& input) {
    return normalize(input);
}

std::vector<std::string> plaintext_segments(const std::string& input) {
    const std::string norm = normalize(input);
    auto [rows, cols] = rectangle_size(norm.size());
    std::vector<std::string> segments;
    segments.reserve(rows);
    for (std::size_t i = 0; i < norm.size(); i += cols) {
        segments.push_back(norm.substr(i, cols));
    }
    return segments;
}

std::string ciphertext(const std::string& input) {
    const std::string norm = normalize(input);
    auto [rows, cols] = rectangle_size(norm.size());
    if (cols == 0) {
        return "";
    }
    std::string cipher;
    cipher.reserve(norm.size());
    for (std::size_t col = 0; col < cols; ++col) {
        for (std::size_t row = 0; row < rows; ++row) {
            std::size_t idx = row * cols + col;
            if (idx < norm.size()) {
                cipher.push_back(norm[idx]);
            }
        }
    }
    return cipher;
}

std::string normalize_cipher_text(const std::string& input) {
    const std::string norm = normalize(input);
    auto [rows, cols] = rectangle_size(norm.size());
    if (cols == 0) {
        return "";
    }
    std::string output;
    output.reserve(norm.size() + cols - 1); // include spaces
    for (std::size_t col = 0; col < cols; ++col) {
        if (col != 0) {
            output.push_back(' ');
        }
        for (std::size_t row = 0; row < rows; ++row) {
            std::size_t idx = row * cols + col;
            if (idx < norm.size()) {
                output.push_back(norm[idx]);
            } else {
                output.push_back(' ');
            }
        }
    }
    return output;
}

/* ------------------------------------------------------------------------
 *  cipher class implementation
 * --------------------------------------------------------------------- */
cipher::cipher(const std::string& input)
    : text_{input} {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(text_);
}

std::vector<std::string> cipher::plaintext_segments() const {
    return crypto_square::plaintext_segments(text_);
}

std::string cipher::ciphertext() const {
    return crypto_square::ciphertext(text_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalize_cipher_text(text_);
}

}  // namespace crypto_square

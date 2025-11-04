#include "crypto_square.h"

#include <cmath>
#include <cstdint>
#include <locale>
#include <string>
#include <utility>
#include <vector>

namespace {
/* Anonymous namespace for internal helpers – no external linkage */
[[nodiscard]] std::pair<std::size_t, std::size_t> compute_dimensions(std::size_t len) {
    if (len == static_cast<std::size_t>(0U)) {
        return {0U, 0U};
    }

    const double root_d {std::sqrt(static_cast<double>(len))};
    std::size_t rows {static_cast<std::size_t>(std::floor(root_d))};
    std::size_t cols {static_cast<std::size_t>(std::ceil(root_d))};

    if ((rows * cols) < len) {
        ++rows;
    }

    /* Ensure the invariants: cols >= rows and (cols - rows) <= 1 */
    if (cols < rows) {
        cols = rows;
    }
    if ((cols - rows) > static_cast<std::size_t>(1U)) {
        cols = rows + static_cast<std::size_t>(1U);
    }

    return {rows, cols};
}
}  // namespace

namespace crypto_square {

std::string normalize_plain_text(const std::string& text) {
    const std::locale loc {};
    std::string result {};

    for (const char ch : text) {
        if (std::isalnum(ch, loc) != 0) {
            const char lowered {std::tolower(ch, loc)};
            result.push_back(lowered);
        }
    }

    return result;
}

std::vector<std::string> plaintext_segments(const std::string& text) {
    const std::string normalized {normalize_plain_text(text)};
    const std::size_t len {normalized.size()};

    const auto [rows, cols] {compute_dimensions(len)};
    std::vector<std::string> segments {};

    for (std::size_t start {0U}; start < len; start += cols) {
        segments.push_back(normalized.substr(start, cols));
    }

    return segments;
}

std::string ciphertext(const std::string& text) {
    const std::string normalized {normalize_plain_text(text)};
    const std::size_t len {normalized.size()};

    const auto [rows, cols] {compute_dimensions(len)};

    std::string cipher {};
    cipher.reserve(len);

    for (std::size_t col {0U}; col < cols; ++col) {
        for (std::size_t row {0U}; row < rows; ++row) {
            const std::size_t index {(row * cols) + col};
            if (index < len) {
                cipher.push_back(normalized[index]);
            }
        }
    }

    return cipher;
}

std::string normalize_ciphertext(const std::string& text) {
    const std::string normalized {normalize_plain_text(text)};
    const std::size_t len {normalized.size()};

    const auto [rows, cols] {compute_dimensions(len)};

    if (len == static_cast<std::size_t>(0U)) {
        return std::string {};
    }

    /* Build the ciphertext in column-chunks directly so we can pad each
       of the last ‘n’ chunks with exactly one space, as required. */
    std::string result {};
    result.reserve(len + cols); /* extra capacity for inter-chunk spaces */

    for (std::size_t col {0U}; col < cols; ++col) {
        std::string chunk {};

        for (std::size_t row {0U}; row < rows; ++row) {
            const std::size_t index {(row * cols) + col};
            if (index < len) {
                chunk.push_back(normalized[index]);
            }
        }

        /* If the rectangle is not perfect, the last (cols * rows - len)
           columns are one character short – pad those with a single space. */
        if (chunk.size() < rows) {
            chunk.push_back(' ');
        }

        result.append(chunk);

        if (col < (cols - static_cast<std::size_t>(1U))) {
            result.push_back(' ');
        }
    }

    return result;
}

/* Cipher class wrappers */

cipher::cipher(std::string text) : m_text(std::move(text)) {}

std::string cipher::normalized_plain_text() const {
    return normalize_plain_text(m_text);
}

std::string cipher::cipher_text() const {
    return ciphertext(m_text);
}

std::string cipher::normalized_cipher_text() const {
    return normalize_ciphertext(m_text);
}

}  // namespace crypto_square

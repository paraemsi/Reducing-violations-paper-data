#include "crypto_square.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string &plaintext) : plaintext_(plaintext) {}

std::string cipher::normalized_cipher_text() const {
    // Normalize the plaintext: remove non-alphabetic characters and convert to lowercase
    std::string normalized;
    for (char ch : plaintext_) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            normalized += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }

    // Get the length of the normalized string
    std::size_t length = normalized.size();
    if (length == 0U) {
        return "";
    }

    // Determine the number of columns (c) and rows (r)
    std::size_t c = 1U;
    while (true) {
        std::size_t r = ((length + c) - 1U) / c;  // Ceiling division
        if (((r * c) >= length) && (c >= r) && ((c - r) <= 1U)) {
            break;
        }
        c++;
    }
    std::size_t r = ((length + c) - 1U) / c;

    // Build the rows
    std::vector<std::string> rows(r);
    for (std::size_t i = 0U; i < length; ++i) {
        std::size_t row_idx = i / c;
        rows[row_idx] += normalized[i];
    }

    // Pad the last row with spaces if necessary
    if (rows.back().size() < c) {
        rows.back().append((c - rows.back().size()), ' ');
    }

    // Read the columns and build the result
    std::string result;
    for (std::size_t col = 0U; col < c; ++col) {
        for (std::size_t row_idx = 0U; row_idx < r; ++row_idx) {
            result += rows[row_idx][col];
        }
        if (col < (c - 1U)) {
            result += ' ';
        }
    }

    return result;
}

}  // namespace crypto_square

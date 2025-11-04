#include "crypto_square.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) : original_{text} {}

void cipher::dimensions(std::size_t length, std::size_t& rows, std::size_t& cols)
{
    if (length == static_cast<std::size_t>(0U)) {
        rows = static_cast<std::size_t>(0U);
        cols = static_cast<std::size_t>(0U);
        return;
    }

    // Find the smallest cols such that cols*cols >= length
    std::size_t c = static_cast<std::size_t>(1U);
    while (((c * c) < length)) {
        c = c + static_cast<std::size_t>(1U);
    }

    // Determine rows: either c or (c - 1) such that rows * c >= length and (c - rows) <= 1
    std::size_t r = c;
    const std::size_t c_minus_1 = c - static_cast<std::size_t>(1U);
    if (((c_minus_1 * c) >= length)) {
        r = c_minus_1;
    } else {
        r = c;
    }

    rows = r;
    cols = c;
}

std::string cipher::normalize_plain_text() const
{
    std::string result{};
    result.reserve(original_.size());

    for (char ch : original_) {
        const std::int32_t ci = std::char_traits<char>::to_int_type(ch);
        if ((std::isalnum(ci)) != 0) {
            const std::int32_t lower_i = std::tolower(ci);
            const char lower_ch = std::char_traits<char>::to_char_type(lower_i);
            result.push_back(lower_ch);
        } else {
            // skip non-alphanumeric
        }
    }

    return result;
}

std::vector<std::string> cipher::plain_text_segments() const
{
    const std::string norm = normalize_plain_text();

    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    dimensions(norm.size(), rows, cols);

    std::vector<std::string> segments{};
    if (cols == static_cast<std::size_t>(0U)) {
        return segments;
    }

    for (std::size_t i = static_cast<std::size_t>(0U); i < norm.size(); i = i + cols) {
        const std::size_t remaining = norm.size() - i;
        const std::size_t take = (remaining < cols) ? remaining : cols;
        segments.emplace_back(norm.substr(i, take));
    }

    return segments;
}

std::string cipher::ciphertext() const
{
    const std::string norm = normalize_plain_text();

    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    dimensions(norm.size(), rows, cols);

    if ((rows == static_cast<std::size_t>(0U)) || (cols == static_cast<std::size_t>(0U))) {
        return std::string{};
    }

    std::string out{};
    out.reserve(norm.size());

    for (std::size_t c = static_cast<std::size_t>(0U); c < cols; c = c + static_cast<std::size_t>(1U)) {
        for (std::size_t r = static_cast<std::size_t>(0U); r < rows; r = r + static_cast<std::size_t>(1U)) {
            const std::size_t idx = (r * cols) + c;
            if (idx < norm.size()) {
                out.push_back(norm[idx]);
            } else {
                // beyond the end, skip for compact ciphertext
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const
{
    const std::string norm = normalize_plain_text();

    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    dimensions(norm.size(), rows, cols);

    if ((rows == static_cast<std::size_t>(0U)) || (cols == static_cast<std::size_t>(0U))) {
        return std::string{};
    }

    // Build c chunks of length r, padding with spaces where the rectangle is short.
    std::vector<std::string> chunks{};
    chunks.reserve(cols);

    for (std::size_t c = static_cast<std::size_t>(0U); c < cols; c = c + static_cast<std::size_t>(1U)) {
        std::string col_chunk{};
        col_chunk.reserve(rows);

        for (std::size_t r = static_cast<std::size_t>(0U); r < rows; r = r + static_cast<std::size_t>(1U)) {
            const std::size_t idx = (r * cols) + c;
            if (idx < norm.size()) {
                col_chunk.push_back(norm[idx]);
            } else {
                col_chunk.push_back(' ');
            }
        }

        chunks.emplace_back(col_chunk);
    }

    // Join with single spaces.
    std::string out{};
    for (std::size_t i = static_cast<std::size_t>(0U); i < chunks.size(); i = i + static_cast<std::size_t>(1U)) {
        out += chunks[i];
        if ((i + static_cast<std::size_t>(1U)) < chunks.size()) {
            out.push_back(' ');
        }
    }

    return out;
}

std::size_t cipher::size() const
{
    const std::string norm = normalize_plain_text();
    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    dimensions(norm.size(), rows, cols);
    return cols;
}

}  // namespace crypto_square

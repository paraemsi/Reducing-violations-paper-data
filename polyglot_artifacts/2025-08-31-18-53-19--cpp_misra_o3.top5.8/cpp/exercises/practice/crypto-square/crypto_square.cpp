#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <utility>
#include <vector>

namespace {

/*
 * Determine the rectangle dimensions (rows r, columns c)
 * according to the rules in the exercise statement.
 */
auto compute_dimensions(std::uint32_t length) -> std::pair<std::uint32_t, std::uint32_t>
{
    if (length == static_cast<std::uint32_t>(0U)) {
        return {0U, 0U};
    }

    const long double len_ld {static_cast<long double>(length)};
    const std::uint32_t c {
        static_cast<std::uint32_t>(std::ceil(std::sqrt(len_ld)))
    };
    std::uint32_t r {
        static_cast<std::uint32_t>(std::floor(std::sqrt(len_ld)))
    };

    if ((r * c) < length) {
        ++r;
    }

    /* Post-condition: r * c >= length, c >= r, c - r <= 1 */
    return {r, c};
}

} // unnamed namespace

namespace crypto_square {

auto normalize_plain_text(const std::string& text) -> std::string
{
    std::string result {};
    result.reserve(text.size());

    for (const char ch : text) {
        /*  Characters are cast to unsigned char for the
         *  <cctype> classification functions as required.
         *  No unsigned char variables are declared, keeping
         *  MISRA-compliance with the fixed-width rule.
         */
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            result.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch)))
            );
        }
    }
    return result;
}

auto plaintext_segments(const std::string& text) -> std::vector<std::string>
{
    const std::string normalized {normalize_plain_text(text)};
    const std::uint32_t len {static_cast<std::uint32_t>(normalized.size())};

    const auto [rows, cols] {compute_dimensions(len)};

    std::vector<std::string> segments {};
    if (cols == static_cast<std::uint32_t>(0U)) {
        return segments;
    }

    segments.reserve(rows);

    std::string segment {};
    segment.reserve(cols);

    for (std::uint32_t idx {0U}; idx < len; ++idx) {
        segment.push_back(normalized[static_cast<std::size_t>(idx)]);
        if (((idx + 1U) % cols) == 0U) {
            segments.push_back(segment);
            segment.clear();
        }
    }

    if (!segment.empty()) {
        segments.push_back(segment);
    }

    return segments;
}

auto cipher_text(const std::string& text) -> std::string
{
    const std::string normalized {normalize_plain_text(text)};
    const std::uint32_t len {static_cast<std::uint32_t>(normalized.size())};

    const auto [rows, cols] {compute_dimensions(len)};
    if (cols == static_cast<std::uint32_t>(0U)) {
        return "";
    }

    std::string encoded {};
    encoded.reserve(len);

    for (std::uint32_t col {0U}; col < cols; ++col) {
        for (std::uint32_t row {0U}; row < rows; ++row) {
            const std::uint32_t index {(row * cols) + col};
            if (index < len) {
                encoded.push_back(normalized[static_cast<std::size_t>(index)]);
            }
        }
    }

    return encoded;
}

auto normalized_cipher_text(const std::string& text) -> std::string
{
    const std::string normalized {normalize_plain_text(text)};
    const std::uint32_t len {static_cast<std::uint32_t>(normalized.size())};

    const auto [rows, cols] {compute_dimensions(len)};
    if (cols == static_cast<std::uint32_t>(0U)) {
        return "";
    }

    /* Build the padded matrix row-wise */
    std::vector<std::string> matrix(rows, std::string(cols, ' '));
    for (std::uint32_t idx {0U}; idx < len; ++idx) {
        const std::uint32_t row {idx / cols};
        const std::uint32_t col {idx % cols};
        matrix[row][col] = normalized[static_cast<std::size_t>(idx)];
    }

    /* Read down the columns and separate groups with spaces */
    std::string result {};
    result.reserve((cols * rows) + cols); /* rough upper bound */

    for (std::uint32_t col {0U}; col < cols; ++col) {
        if (col != static_cast<std::uint32_t>(0U)) {
            result.push_back(' ');
        }
        for (std::uint32_t row {0U}; row < rows; ++row) {
            result.push_back(matrix[row][col]);
        }
    }

    return result;
}

/* ------------------------------------------------------------------ */
/*  cipher_result implementation                                      */
/* ------------------------------------------------------------------ */

cipher_result::cipher_result(const std::string& text)
    : original_{text}
{
    /* no further work */
}

auto cipher_result::cipher_text() const -> std::string
{
    return crypto_square::cipher_text(original_);
}

auto cipher_result::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalized_cipher_text(original_);
}


}  // namespace crypto_square

#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <utility>

namespace {

/*  Determine the rectangle dimensions (rows, cols) that satisfy:
 *  – r * c >= length,
 *  – c >= r,
 *  – c - r <= 1.
 */
auto dimensions(std::size_t length) -> std::pair<std::size_t, std::size_t>
{
    if (length == 0U) {
        return {0U, 0U};
    }

    for (std::size_t cols = 1U; ; ++cols) {
        const std::size_t rows = (length + cols - 1U) / cols;
        if ((cols >= rows) && ((cols - rows) <= 1U)) {
            return {rows, cols};
        }
    }
}

}  // namespace

namespace crypto_square {

auto normalize_plain_text(const std::string& text) -> std::string
{
    std::string normalised{};
    normalised.reserve(text.size());

    for (char ch : text) {
        const int code = std::char_traits<char>::to_int_type(ch);
        if (std::isalnum(code) != 0) {
            normalised.push_back(static_cast<char>(std::tolower(code)));
        }
    }

    return normalised;
}

auto plaintext_segments(const std::string& text) -> std::vector<std::string>
{
    const std::string normalised = normalize_plain_text(text);
    const std::size_t len = normalised.length();

    const auto [rows, cols] = dimensions(len);
    std::vector<std::string> segments{};
    segments.reserve(rows);

    for (std::size_t row = 0U; row < rows; ++row) {
        const std::size_t start = row * cols;
        const std::size_t part_len =
            (start + cols <= len) ? cols : (len - start);
        segments.emplace_back(normalised.substr(start, part_len));
    }

    return segments;
}

auto ciphertext(const std::string& text) -> std::string
{
    const std::string normalised = normalize_plain_text(text);
    const std::size_t len = normalised.length();

    const auto [rows, cols] = dimensions(len);
    if (len == 0U) {
        return std::string{};
    }

    std::string cipher{};
    cipher.reserve(len);

    for (std::size_t col = 0U; col < cols; ++col) {
        for (std::size_t row = 0U; row < rows; ++row) {
            const std::size_t index = (row * cols) + col;
            if (index < len) {
                cipher.push_back(normalised[index]);
            }
        }
    }

    return cipher;
}

auto normalized_cipher_text(const std::string& text) -> std::string
{
    const std::string normalised = normalize_plain_text(text);
    const std::size_t len = normalised.length();

    const auto [rows, cols] = dimensions(len);
    if (len == 0U) {
        return std::string{};
    }

    /*  Prepare column-wise chunks of equal length ‘rows’.             */
    std::vector<std::string> chunks(cols, std::string(rows, ' '));

    for (std::size_t col = 0U; col < cols; ++col) {
        for (std::size_t row = 0U; row < rows; ++row) {
            const std::size_t index = (row * cols) + col;
            if (index < len) {
                chunks[col][row] = normalised[index];
            }
        }
    }

    /*  Join the chunks with single spaces.                            */
    std::ostringstream oss{};
    for (std::size_t i = 0U; i < cols; ++i) {
        if (i != 0U) {
            oss << ' ';
        }
        oss << chunks[i];
    }

    return oss.str();
}

/* ------------------------------------------------------------------ */
/*                       cipher_text class methods                     */
/* ------------------------------------------------------------------ */

cipher_text::cipher_text(const std::string& text) : original_(text)
{
    /*  Constructor stores the original input.                         */
}

auto cipher_text::normalize_plain_text() const -> std::string
{
    return crypto_square::normalize_plain_text(original_);
}

auto cipher_text::plaintext_segments() const -> std::vector<std::string>
{
    return crypto_square::plaintext_segments(original_);
}

auto cipher_text::ciphertext() const -> std::string
{
    return crypto_square::ciphertext(original_);
}

auto cipher_text::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalized_cipher_text(original_);
}

/* ------------------------------------------------------------------ */
/*          factory free-function expected by the unit tests           */
/* ------------------------------------------------------------------ */

auto cipher(const std::string& text) -> cipher_text
{
    return cipher_text(text);
}

}  // namespace crypto_square

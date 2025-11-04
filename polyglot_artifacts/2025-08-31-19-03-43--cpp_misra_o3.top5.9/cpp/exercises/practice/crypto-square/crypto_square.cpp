#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstddef>
#include <utility>

namespace {

/*  Compute rectangle dimensions conforming to:
 *   • rows * columns >= length
 *   • columns >= rows
 *   • columns − rows <= 1
 */
auto compute_rectangle_dimensions(std::size_t length)
    -> std::pair<std::size_t, std::size_t>
{
    if(length == 0U)
    {
        return {0U, 0U};
    }

    std::size_t columns {1U};
    while((columns * columns) < length)
    {
        ++columns;
    }

    std::size_t rows {columns};
    if(((columns - 1U) * columns) >= length)
    {
        rows = columns - 1U;
    }

    return {rows, columns};
}

} // namespace

namespace crypto_square {

auto normalize_plain_text(std::string_view text) -> std::string
{
    std::string result {};
    result.reserve(text.size());

    for(char ch : text)
    {
        const unsigned char uch {static_cast<unsigned char>(ch)};
        if((std::isalnum(uch)) != 0)
        {
            result.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    return result;
}

auto plain_text_segments(std::string_view text) -> std::vector<std::string>
{
    const std::string normalized {normalize_plain_text(text)};

    std::vector<std::string> segments {};
    const std::size_t length {normalized.length()};
    if(length == 0U)
    {
        return segments;
    }

    const auto [rows, columns] {compute_rectangle_dimensions(length)};
    (void)rows; /* rows not required here but kept for clarity */

    for(std::size_t index {0U}; index < length; index += columns)
    {
        segments.push_back(
            std::string {normalized.substr(index, columns)});
    }

    return segments;
}

auto cipher_text(std::string_view text) -> std::string
{
    const std::string normalized {normalize_plain_text(text)};
    const std::size_t length {normalized.length()};

    if(length == 0U)
    {
        return std::string {};
    }

    const auto [rows, columns] {compute_rectangle_dimensions(length)};
    std::string cipher {};
    cipher.reserve(length);

    for(std::size_t col {0U}; col < columns; ++col)
    {
        for(std::size_t row {0U}; row < rows; ++row)
        {
            const std::size_t index {(row * columns) + col};
            if(index < length)
            {
                cipher.push_back(normalized[index]);
            }
        }
    }

    return cipher;
}

auto normalized_cipher_text(std::string_view text) -> std::string
{
    const std::string normalized {normalize_plain_text(text)};
    const std::size_t length {normalized.length()};

    if(length == 0U)
    {
        return std::string {};
    }

    const auto [rows, columns] {compute_rectangle_dimensions(length)};

    std::string result {};
    /* reserve rectangle size plus spaces between the column-chunks */
    result.reserve(((rows * columns) + (columns - 1U)));

    for(std::size_t col {0U}; col < columns; ++col)
    {
        if(col != 0U)
        {
            result.push_back(' ');
        }

        for(std::size_t row {0U}; row < rows; ++row)
        {
            const std::size_t index {((row * columns) + col)};
            if(index < length)
            {
                result.push_back(normalized[index]);
            }
            else
            {
                result.push_back(' ');
            }
        }
    }

    return result;
}

/* ------------------------------------------------------------------
 *   cipher class – thin wrapper delegating to the helper functions
 * ----------------------------------------------------------------*/
cipher::cipher(std::string_view text)
    : m_text{text.data(), text.size()}
{
}

auto cipher::normalize_plain_text() const -> std::string
{
    return crypto_square::normalize_plain_text(m_text);
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    return crypto_square::plain_text_segments(m_text);
}

auto cipher::cipher_text() const -> std::string
{
    return crypto_square::cipher_text(m_text);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalized_cipher_text(m_text);
}

}  // namespace crypto_square

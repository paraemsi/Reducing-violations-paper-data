#include "crypto_square.h"
#include <vector>
#include <cctype>

namespace crypto_square {

auto encode(std::string_view text) -> std::string
{
    // Normalize text: keep alphanumerics and down-case them
    std::string normalized {};
    normalized.reserve(text.size());

    for (const char ch : text)
    {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0)
        {
            const int lower_int { std::tolower(static_cast<unsigned char>(ch)) };
            normalized.push_back(std::char_traits<char>::to_char_type(lower_int));
        }
    }

    const std::uint32_t n { static_cast<std::uint32_t>(normalized.size()) };
    if (n == 0U)
    {
        return std::string {};
    }

    /* Determine rectangle dimensions
       Find smallest columns (c) such that:
       r * c >= n, c >= r, and (c - r) <= 1                                    */
    std::uint32_t columns { 1U };
    while ((columns * columns) < n)
    {
        columns += 1U;
    }

    std::uint32_t rows { columns };

    if (((rows - 1U) * columns) >= n)
    {
        rows -= 1U;
    }

    /* Build padded rows of length `columns`                                    */
    std::vector<std::string> rectangle {};
    rectangle.reserve(rows);

    for (std::uint32_t idx { 0U }; idx < n; idx += columns)
    {
        const std::uint32_t remaining { n - idx };
        std::string row { normalized.substr(idx, columns) };
        if (remaining < columns)
        {
            row.append(columns - remaining, ' ');
        }
        rectangle.push_back(row);
    }

    while (static_cast<std::uint32_t>(rectangle.size()) < rows)
    {
        rectangle.push_back(std::string(columns, ' '));
    }

    /* Read column-wise to create cipher chunks of length `rows`                */
    std::string output {};
    for (std::uint32_t col { 0U }; col < columns; ++col)
    {
        if (col != 0U)
        {
            output.push_back(' ');
        }

        for (std::uint32_t row { 0U }; row < rows; ++row)
        {
            output.push_back(rectangle[row][col]);
        }
    }

    return output;
}

/*---------------------------------------------------------------------------*/
/*  cipher member functions                                                  */
/*---------------------------------------------------------------------------*/
cipher::cipher(std::string_view text) : cipher_text_{ encode(text) }
{
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return cipher_text_;
}

}  // namespace crypto_square

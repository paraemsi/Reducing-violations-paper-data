#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

auto cipher_text(const std::string& input) -> std::string
{
    const std::locale loc {};

    std::string normalized {};
    normalized.reserve(input.size());

    for (char ch : input)
    {
        /* retain only alphanumeric characters and convert to lower-case */
        if (std::isalnum(ch, loc) != 0)
        {
            normalized.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    const std::size_t length { normalized.size() };

    if (length == static_cast<std::size_t>(0))
    {
        return std::string {};
    }

    const double root { std::sqrt(static_cast<double>(length)) };

    std::size_t columns { static_cast<std::size_t>(std::ceil(root)) };
    std::size_t rows { static_cast<std::size_t>(std::floor(root)) };

    if ((rows * columns) < length)
    {
        ++rows;
    }

    std::vector<std::string> chunks {};
    chunks.reserve(columns);

    for (std::size_t col { static_cast<std::size_t>(0) }; col < columns; ++col)
    {
        std::string chunk {};
        chunk.reserve(rows);

        for (std::size_t row { static_cast<std::size_t>(0) }; row < rows; ++row)
        {
            const std::size_t index { (row * columns) + col };

            if (index < length)
            {
                chunk.push_back(normalized[index]);
            }
            else
            {
                chunk.push_back(' ');
            }
        }

        chunks.push_back(chunk);
    }

    std::string result {};
    for (std::size_t idx { static_cast<std::size_t>(0) }; idx < chunks.size(); ++idx)
    {
        result += chunks[idx];

        if ((idx + static_cast<std::size_t>(1)) < chunks.size())
        {
            result.push_back(' ');
        }
    }

    return result;
}

/* ------------------------------------------------------------------ */
/* cipher class implementation                                        */
/* ------------------------------------------------------------------ */

cipher::cipher(const std::string& text) : m_text(text) { }

auto cipher::normalize_plain_text() const -> std::string
{
    const std::locale loc {};
    std::string normalized {};
    normalized.reserve(m_text.size());

    for (char ch : m_text)
    {
        if (std::isalnum(ch, loc) != 0)
        {
            normalized.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    return normalized;
}

auto cipher::size() const -> std::size_t
{
    const std::size_t length { normalize_plain_text().size() };

    if (length == static_cast<std::size_t>(0))
    {
        return static_cast<std::size_t>(0);
    }

    const double root { std::sqrt(static_cast<double>(length)) };

    std::size_t columns { static_cast<std::size_t>(std::ceil(root)) };
    std::size_t rows { static_cast<std::size_t>(std::floor(root)) };

    if ((rows * columns) < length)
    {
        ++rows;
    }

    (void)rows; /* rows not required outside this function */
    return columns;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    const std::string normalized { normalize_plain_text() };
    const std::size_t length { normalized.size() };
    const std::size_t columns { size() };

    std::vector<std::string> segments {};
    if (columns == static_cast<std::size_t>(0))
    {
        return segments;
    }

    for (std::size_t idx { static_cast<std::size_t>(0) }; idx < length; idx += columns)
    {
        segments.push_back(normalized.substr(idx,
            (idx + columns <= length) ? columns : length - idx));
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    const std::string spaced { normalized_cipher_text() };

    /* remove the spaces to obtain concatenated cipher text */
    std::string merged {};
    merged.reserve(spaced.size());

    for (char ch : spaced)
    {
        if (ch != ' ')
        {
            merged.push_back(ch);
        }
    }

    return merged;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    const std::string normalized { normalize_plain_text() };
    const std::size_t length { normalized.size() };

    if (length == static_cast<std::size_t>(0))
    {
        return std::string {};
    }

    const double root { std::sqrt(static_cast<double>(length)) };

    std::size_t columns { static_cast<std::size_t>(std::ceil(root)) };
    std::size_t rows { static_cast<std::size_t>(std::floor(root)) };

    if ((rows * columns) < length)
    {
        ++rows;
    }

    std::vector<std::string> chunks {};
    chunks.reserve(columns);

    for (std::size_t col { static_cast<std::size_t>(0) }; col < columns; ++col)
    {
        std::string chunk {};
        chunk.reserve(rows);

        for (std::size_t row { static_cast<std::size_t>(0) }; row < rows; ++row)
        {
            const std::size_t index { (row * columns) + col };

            if (index < length)
            {
                chunk.push_back(normalized[index]);
            }
            else
            {
                chunk.push_back(' ');
            }
        }

        chunks.push_back(chunk);
    }

    std::string result {};
    for (std::size_t idx { static_cast<std::size_t>(0) }; idx < chunks.size(); ++idx)
    {
        result += chunks[idx];

        if ((idx + static_cast<std::size_t>(1)) < chunks.size())
        {
            result.push_back(' ');
        }
    }

    return result;
}

} // namespace crypto_square

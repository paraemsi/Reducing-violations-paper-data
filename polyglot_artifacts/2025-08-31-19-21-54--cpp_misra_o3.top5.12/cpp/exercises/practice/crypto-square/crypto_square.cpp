#include "crypto_square.h"

#include <algorithm>
#include <cstddef>
#include <locale>
#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

auto cipher_text(const std::string& input) -> std::string
{
    if(input.empty())
    {
        return std::string{};
    }

    auto const loc = std::locale{};
    std::string normalized{};
    normalized.reserve(input.size());

    for(char ch : input)
    {
        if(std::isalnum(static_cast<unsigned char>(ch), loc) != 0)
        {
            normalized.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch), loc)));
        }
        else
        {
            /* ignore non-alphanumeric character */
        }
    }

    std::size_t const length = normalized.length();

    if(length == static_cast<std::size_t>(0))
    {
        return std::string{};
    }

    /* determine rectangle dimensions */
    std::size_t columns = static_cast<std::size_t>(0);
    while(((columns * columns) < length))
    {
        ++columns;
    }

    std::size_t rows = columns;
    if(((columns * (columns - static_cast<std::size_t>(1U))) >= length))
    {
        rows = columns - static_cast<std::size_t>(1U);
    }

    std::string output{};
    output.reserve((columns * rows) + columns); /* space separators */

    for(std::size_t col = static_cast<std::size_t>(0U); col < columns; ++col)
    {
        for(std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row)
        {
            std::size_t const index = ((row * columns) + col);
            if(index < length)
            {
                output.push_back(normalized[index]);
            }
            else
            {
                output.push_back(' ');
            }
        }

        if((col + static_cast<std::size_t>(1U)) < columns)
        {
            output.push_back(' ');
        }
        else
        {
            /* last chunk ‑ no trailing space separator needed */
        }
    }

    return output;
}

/* -------------------------------------------------------------------------- */
/*  cipher implementation                                                     */
/* -------------------------------------------------------------------------- */
cipher::cipher(std::string_view text)
{
    const auto loc = std::locale{};
    m_normalized.reserve(text.size());

    for(char ch : text)
    {
        if(std::isalnum(static_cast<unsigned char>(ch), loc) != 0)
        {
            m_normalized.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch), loc)));
        }
        else
        {
            /* ignore non-alphanumeric characters */
        }
    }

    const std::size_t length = m_normalized.length();

    std::size_t columns = static_cast<std::size_t>(0U);
    while(((columns * columns) < length))
    {
        ++columns;
    }

    std::size_t rows = columns;
    if(((columns * (columns - static_cast<std::size_t>(1U))) >= length))
    {
        rows = columns - static_cast<std::size_t>(1U);
    }

    m_columns = columns;
    m_rows    = rows;
}

auto cipher::normalize_plain_text() const -> std::string
{
    return m_normalized;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments{};
    if(m_normalized.empty())
    {
        return segments;
    }

    segments.reserve(m_rows);

    for(std::size_t row = static_cast<std::size_t>(0U); row < m_rows; ++row)
    {
        const std::size_t start = (row * m_columns);
        if(start >= m_normalized.length())
        {
            break;
        }
        const std::size_t len =
            (std::min)(m_columns, m_normalized.length() - start);
        segments.emplace_back(m_normalized.substr(start, len));
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    if(m_normalized.empty())
    {
        return std::string{};
    }

    std::string output{};
    output.reserve(m_columns * m_rows);

    for(std::size_t col = static_cast<std::size_t>(0U); col < m_columns; ++col)
    {
        for(std::size_t row = static_cast<std::size_t>(0U); row < m_rows; ++row)
        {
            const std::size_t index = ((row * m_columns) + col);
            if(index < m_normalized.length())
            {
                output.push_back(m_normalized[index]);
            }
        }
    }

    return output;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    if(m_normalized.empty())
    {
        return std::string{};
    }

    std::string output{};
    output.reserve((m_columns * m_rows) + (m_columns - static_cast<std::size_t>(1U)));

    for(std::size_t col = static_cast<std::size_t>(0U); col < m_columns; ++col)
    {
        for(std::size_t row = static_cast<std::size_t>(0U); row < m_rows; ++row)
        {
            const std::size_t index = ((row * m_columns) + col);
            if(index < m_normalized.length())
            {
                output.push_back(m_normalized[index]);
            }
            else
            {
                output.push_back(' ');
            }
        }

        if((col + static_cast<std::size_t>(1U)) < m_columns)
        {
            output.push_back(' ');
        }
    }

    return output;
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iterator>

namespace crypto_square {

// ---- private helpers ------------------------------------------------------

std::size_t cipher::row_count(const std::size_t length)
{
    const std::size_t columns { column_count(length) };
    const bool one_less_row_possible { (columns * (columns - static_cast<std::size_t>(1U))) >= length };
    return one_less_row_possible ? (columns - static_cast<std::size_t>(1U)) : columns;
}

std::size_t cipher::column_count(const std::size_t length)
{
    const double d_len { static_cast<double>(length) };
    return static_cast<std::size_t>(std::ceil(std::sqrt(d_len)));
}

// ---- public interface ------------------------------------------------------

cipher::cipher(std::string_view text) : m_normalized{}
{
    m_normalized.reserve(text.size());

    std::transform(text.begin(), text.end(),
                   std::back_inserter(m_normalized),
                   [](const char ch) -> char
                   {
                       if(std::isalnum(static_cast<unsigned char>(ch)) != 0)
                       {
                           return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                       }
                       else
                       {
                           return static_cast<char>('\0'); // filtered later
                       }
                   });

    m_normalized.erase(std::remove(m_normalized.begin(),
                                   m_normalized.end(),
                                   static_cast<char>('\0')),
                       m_normalized.end());
}

std::string cipher::normalize_plain_text() const
{
    return m_normalized;
}

std::vector<std::string> cipher::plain_text_segments() const
{
    const std::size_t len { m_normalized.length() };
    if(len == static_cast<std::size_t>(0U))
    {
        return {};
    }

    const std::size_t rows { row_count(len) };
    const std::size_t columns { column_count(len) };
    std::vector<std::string> segments;
    segments.reserve(rows);

    for(std::size_t row { static_cast<std::size_t>(0U) }; row < rows; ++row)
    {
        const std::size_t start { row * columns };
        std::string segment { m_normalized.substr(start, columns) };

        if(segment.length() < columns)
        {
            segment.append(columns - segment.length(), ' ');
        }

        segments.push_back(segment);
    }

    return segments;
}

std::string cipher::cipher_text() const
{
    const std::vector<std::string> segments { plain_text_segments() };
    if(segments.empty())
    {
        return {};
    }

    const std::size_t columns { segments.front().length() };
    const std::size_t rows { segments.size() };
    std::string result;
    result.reserve(columns * rows);

    for(std::size_t col { static_cast<std::size_t>(0U) }; col < columns; ++col)
    {
        for(const std::string& seg : segments)
        {
            const char ch { seg[col] };
            if(ch != ' ')
            {
                result.push_back(ch);
            }
        }
    }

    return result;
}

std::string cipher::normalized_cipher_text() const
{
    const std::vector<std::string> segments { plain_text_segments() };
    if(segments.empty())
    {
        return {};
    }

    const std::size_t columns { segments.front().length() };
    const std::size_t rows { segments.size() };
    std::string result;

    for(std::size_t col { static_cast<std::size_t>(0U) }; col < columns; ++col)
    {
        for(std::size_t row { static_cast<std::size_t>(0U) }; row < rows; ++row)
        {
            result.push_back(segments[row][col]);
        }

        if(col + static_cast<std::size_t>(1U) < columns)
        {
            result.push_back(' ');
        }
    }

    return result;
}

}  // namespace crypto_square

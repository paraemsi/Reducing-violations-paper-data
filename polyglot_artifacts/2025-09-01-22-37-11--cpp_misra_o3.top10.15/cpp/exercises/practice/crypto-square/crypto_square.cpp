#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(std::string_view input)
{
    /* Normalise ----------------------------------------------------------- */
    const std::locale loc {};
    m_normalized.reserve(input.size());

    for (char ch : input)
    {
        if (std::isalnum(static_cast<unsigned char>(ch), loc) != 0)
        {
            m_normalized.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch), loc)));
        }
    }

    const std::size_t len { m_normalized.length() };
    if (len == static_cast<std::size_t>(0U))
    {
        m_rows    = static_cast<std::size_t>(0U);
        m_columns = static_cast<std::size_t>(0U);
        return;
    }

    const double root { std::sqrt(static_cast<double>(len)) };

    m_columns = static_cast<std::size_t>(std::ceil(root));
    m_rows    = static_cast<std::size_t>(std::floor(root));

    if (((m_rows * m_columns) < len) != false)
    {
        ++m_rows;
    }
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return m_normalized;
}

auto cipher::size() const -> std::size_t
{
    return m_columns;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments {};
    if (m_columns == static_cast<std::size_t>(0U))
    {
        return segments;
    }

    for (std::size_t idx { 0U }; idx < m_normalized.length(); idx += m_columns)
    {
        segments.emplace_back(m_normalized.substr(idx, m_columns));
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    if (m_columns == static_cast<std::size_t>(0U))
    {
        return std::string {};
    }

    std::string result {};
    for (std::size_t col { 0U }; col < m_columns; ++col)
    {
        for (std::size_t row { 0U }; row < m_rows; ++row)
        {
            const std::size_t index { (row * m_columns) + col };
            if (index < m_normalized.length())
            {
                result.push_back(m_normalized[index]);
            }
            else
            {
                result.push_back(' ');
            }
        }

        if ((col + static_cast<std::size_t>(1U)) < m_columns)
        {
            result.push_back(' ');
        }
    }

    return result;
}

auto cipher_text(std::string_view input) -> std::string
{
    return cipher(input).cipher_text();
}

}  // namespace crypto_square

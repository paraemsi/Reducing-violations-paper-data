#include "crypto_square.h"

#include <cstdint>
#include <cstddef>
#include <cmath>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

namespace crypto_square {

namespace {

/*
 * Normalise the input string by
 *   – removing all non-alphanumeric characters, and
 *   – converting the remaining characters to lower-case.
 */
auto normalize(const std::string& input) -> std::string
{
    const std::locale loc {};
    std::string output {};
    output.reserve(input.size());

    for(char ch : input)
    {
        if(std::isalnum(static_cast<unsigned char>(ch), loc) != 0)
        {
            output.push_back(
                static_cast<char>(
                    std::tolower(static_cast<unsigned char>(ch), loc)));
        }
    }
    return output;
}

} // unnamed namespace

cipher::cipher(const std::string& text)
    : m_normalized{ normalize(text) }
{
    const std::size_t len { m_normalized.size() };

    if(len == static_cast<std::size_t>(0U))
    {
        m_rows = 0U;
        m_columns = 0U;
        return;
    }

    const double root { std::sqrt(static_cast<double>(len)) };
    m_rows = static_cast<std::size_t>(root);
    m_columns = static_cast<std::size_t>(std::ceil(root));

    if((m_rows * m_columns) < len)
    {
        ++m_rows;
    }
}

auto cipher::normalize_plain_text() const -> std::string
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
    segments.reserve((m_columns != 0U) ? ((m_normalized.size() + (m_columns - static_cast<std::size_t>(1U))) / m_columns) : static_cast<std::size_t>(0U));

    for(std::size_t pos = static_cast<std::size_t>(0U); pos < m_normalized.size(); pos += m_columns)
    {
        segments.push_back(m_normalized.substr(pos, m_columns));
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    if(m_normalized.empty())
    {
        return std::string {};
    }

    std::string result {};
    result.reserve(m_normalized.size());

    const std::size_t len { m_normalized.size() };

    for(std::size_t col = static_cast<std::size_t>(0U); col < m_columns; ++col)
    {
        for(std::size_t row = static_cast<std::size_t>(0U); row < m_rows; ++row)
        {
            const std::size_t index { (row * m_columns) + col };
            if(index < len)
            {
                result.push_back(m_normalized[index]);
            }
        }
    }
    return result;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    if(m_normalized.empty())
    {
        return std::string {};
    }

    const std::string raw_cipher { cipher_text() };
    std::vector<std::string> chunks {};
    chunks.reserve(m_columns);

    for(std::size_t i = static_cast<std::size_t>(0U); i < m_columns; ++i)
    {
        const std::size_t start { i * m_rows };
        std::string chunk { raw_cipher.substr(start, m_rows) };
        if(chunk.size() < m_rows)
        {
            chunk.append(m_rows - chunk.size(), ' ');
        }
        chunks.push_back(chunk);
    }

    std::ostringstream oss {};
    for(std::size_t i = static_cast<std::size_t>(0U); i < chunks.size(); ++i)
    {
        oss << chunks[i];
        if(((i + static_cast<std::size_t>(1U)) < chunks.size()))
        {
            oss << ' ';
        }
    }
    return oss.str();
}

}  // namespace crypto_square

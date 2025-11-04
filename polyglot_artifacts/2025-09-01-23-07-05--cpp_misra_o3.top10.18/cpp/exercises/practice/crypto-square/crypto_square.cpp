#include "crypto_square.h"

#include <cstdint>
#include <locale>
#include <string>
#include <string_view>

namespace crypto_square {

cipher_result::cipher_result(std::string_view input)
{
    const std::locale loc{};

    m_normalized.reserve(input.size());

    for(const char ch : input)
    {
        if(std::isalnum(ch, loc) != 0)
        {
            m_normalized.push_back(std::tolower(ch, loc));
        }
    }

    const std::uint64_t len{static_cast<std::uint64_t>(m_normalized.size())};

    if(len == static_cast<std::uint64_t>(0U))
    {
        m_rows    = 0U;
        m_columns = 0U;
        return;
    }

    m_columns = 1U;
    for(;; ++m_columns)
    {
        m_rows = ((len + m_columns) - static_cast<std::uint64_t>(1U)) /
                 m_columns; /* ceil division */

        if((m_columns >= m_rows) &&
           ((m_columns - m_rows) <= static_cast<std::uint64_t>(1U)))
        {
            break;
        }
    }
}

auto cipher_result::normalize_plain_text() const -> std::string
{
    return m_normalized;
}

auto cipher_result::plaintext_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments{};

    if(m_normalized.empty())
    {
        return segments;
    }

    segments.reserve(static_cast<std::vector<std::string>::size_type>(m_rows));

    for(std::uint64_t row{0U}; row < m_rows; ++row)
    {
        const std::uint64_t start_idx{row * m_columns};
        const std::uint64_t remaining{
            static_cast<std::uint64_t>(m_normalized.size()) - start_idx};
        const std::uint64_t length{(remaining < m_columns) ? remaining : m_columns};

        segments.emplace_back(
            m_normalized.substr(static_cast<std::string::size_type>(start_idx),
                                static_cast<std::string::size_type>(length)));
    }

    return segments;
}

auto cipher_result::cipher_text() const -> std::string
{
    if(m_normalized.empty())
    {
        return std::string{};
    }

    std::string result{};
    result.reserve(m_normalized.size());

    for(std::uint64_t col{0U}; col < m_columns; ++col)
    {
        for(std::uint64_t row{0U}; row < m_rows; ++row)
        {
            const std::uint64_t idx{(row * m_columns) + col};

            if(idx < static_cast<std::uint64_t>(m_normalized.size()))
            {
                result.push_back(
                    m_normalized[static_cast<std::string::size_type>(idx)]);
            }
        }
    }

    return result;
}

auto cipher_result::normalized_cipher_text() const -> std::string
{
    if(m_normalized.empty())
    {
        return std::string{};
    }

    std::string result{};
    result.reserve(static_cast<std::string::size_type>(
        (m_rows * m_columns) + (m_columns - static_cast<std::uint64_t>(1U))));

    for(std::uint64_t col{0U}; col < m_columns; ++col)
    {
        for(std::uint64_t row{0U}; row < m_rows; ++row)
        {
            const std::uint64_t idx{(row * m_columns) + col};

            if(idx < static_cast<std::uint64_t>(m_normalized.size()))
            {
                result.push_back(
                    m_normalized[static_cast<std::string::size_type>(idx)]);
            }
            else
            {
                result.push_back(' ');
            }
        }

        if((col + static_cast<std::uint64_t>(1U)) < m_columns)
        {
            result.push_back(' ');
        }
    }

    return result;
}

auto cipher(std::string_view input) -> cipher_result
{
    return cipher_result{input};
}

}  // namespace crypto_square

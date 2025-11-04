#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <vector>

namespace {

auto cleanse_and_lower(const std::string& input) -> std::string
{
    std::string result {};
    result.reserve(input.size());

    for(const char ch : input)
    {
        /* NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index) */
        if((std::isalnum(static_cast<unsigned char>(ch))) != 0)
        {
            /* cppcheck-suppress useStlAlgorithm */
            result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return result;
}

auto calc_columns(std::uint32_t len) -> std::uint32_t
{
    const auto root {static_cast<double>(std::sqrt(static_cast<double>(len)))};
    std::uint32_t cols {static_cast<std::uint32_t>(std::ceil(root))};
    std::uint32_t rows {static_cast<std::uint32_t>(std::floor(root))};

    if((rows * cols) < len)
    {
        ++rows;
    }

    if(cols < rows)
    {
        cols = rows;
    }

    return cols;
}

} // unnamed namespace

namespace crypto_square {

auto normalize_plain_text(const std::string& text) -> std::string
{
    return cleanse_and_lower(text);
}

auto plaintext_segments(const std::string& text) -> std::vector<std::string>
{
    const std::string normalized {cleanse_and_lower(text)};
    const std::uint32_t length {static_cast<std::uint32_t>(normalized.size())};

    if(length == static_cast<std::uint32_t>(0U))
    {
        return {};
    }

    const std::uint32_t columns {calc_columns(length)};
    std::vector<std::string> segments {};
    segments.reserve(static_cast<std::size_t>((length + columns - 1U) / columns));

    for(std::uint32_t start {0U}; start < length; start += columns)
    {
        const std::uint32_t end {static_cast<std::uint32_t>(
            std::min<std::size_t>(
                static_cast<std::size_t>(length),
                static_cast<std::size_t>(start + columns)))};

        segments.emplace_back(
            normalized.substr(
                static_cast<std::size_t>(start),
                static_cast<std::size_t>(end - start)));
    }

    return segments;
}

auto cipher_text(const std::string& text) -> std::string
{
    const std::string normalized {cleanse_and_lower(text)};
    const std::uint32_t length {static_cast<std::uint32_t>(normalized.size())};

    if(length == static_cast<std::uint32_t>(0U))
    {
        return "";
    }

    const std::uint32_t columns {calc_columns(length)};
    const std::uint32_t rows {(length + columns - 1U) / columns};

    std::string cipher {};
    cipher.reserve(static_cast<std::size_t>(length));

    for(std::uint32_t c {0U}; c < columns; ++c)
    {
        for(std::uint32_t r {0U}; r < rows; ++r)
        {
            const std::uint32_t idx {(r * columns) + c};
            if(idx < length)
            {
                cipher.push_back(normalized[static_cast<std::size_t>(idx)]);
            }
        }
    }

    return cipher;
}

auto normalized_cipher_text(const std::string& text) -> std::string
{
    const std::string normalized {cleanse_and_lower(text)};
    const std::uint32_t length {static_cast<std::uint32_t>(normalized.size())};

    if(length == static_cast<std::uint32_t>(0U))
    {
        return "";
    }

    const std::uint32_t columns {calc_columns(length)};
    const std::uint32_t rows {(length + columns - 1U) / columns};

    std::string cipher {};
    cipher.reserve(static_cast<std::size_t>(columns * (rows + 1U)));

    for(std::uint32_t c {0U}; c < columns; ++c)
    {
        if(c != static_cast<std::uint32_t>(0U))
        {
            cipher.push_back(' ');
        }

        for(std::uint32_t r {0U}; r < rows; ++r)
        {
            const std::uint32_t idx {(r * columns) + c};
            if(idx < length)
            {
                cipher.push_back(normalized[static_cast<std::size_t>(idx)]);
            }
            else
            {
                cipher.push_back(' ');
            }
        }
    }

    return cipher;
}

// -----------------------------------------------------------------------------
// class crypto_square::cipher
// -----------------------------------------------------------------------------
cipher::cipher(const std::string& text) : m_text(text) {}

auto cipher::normalize_plain_text() const -> std::string
{
    return ::crypto_square::normalize_plain_text(m_text);
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    return ::crypto_square::plaintext_segments(m_text);
}

auto cipher::cipher_text() const -> std::string
{
    return ::crypto_square::cipher_text(m_text);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return ::crypto_square::normalized_cipher_text(m_text);
}

}  // namespace crypto_square

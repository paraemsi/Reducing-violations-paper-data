#include "crypto_square.h"

#include <locale>
#include <cmath>
#include <cstdint>
#include <utility>

namespace crypto_square {

namespace {

auto normalize_string(const std::string& text) -> std::string
{
    const std::locale loc{};
    std::string result{};
    result.reserve(text.length());
    for(char ch : text)
    {
        if(std::isalnum(static_cast<char>(ch), loc) != 0)
        {
            result.push_back(
                static_cast<char>(std::tolower(static_cast<char>(ch), loc)));
        }
        else
        {
            /* ignore non-alphanumeric characters */
        }
    }
    return result;
}

auto rows_columns(const std::size_t len) -> std::pair<std::size_t, std::size_t>
{
    const double root = std::sqrt(static_cast<double>(len));
    std::size_t c = static_cast<std::size_t>(std::ceil(root));
    std::size_t r = static_cast<std::size_t>(std::floor(root));

    if(((r * c) < len))
    {
        ++r;
    }

    return {r, c};
}

} // unnamed namespace

auto normalize_plain_text(const std::string& input) -> std::string
{
    return normalize_string(input);
}

auto plaintext_segments(const std::string& input) -> std::vector<std::string>
{
    const std::string normalized = normalize_string(input);
    const std::size_t len = normalized.length();

    if(len == static_cast<std::size_t>(0))
    {
        return {};
    }

    const auto rc = rows_columns(len);
    const std::size_t c = rc.second;

    std::vector<std::string> segments{};
    for(std::size_t start = 0U; start < len; start += c)
    {
        segments.push_back(normalized.substr(start, c));
    }

    return segments;
}

auto cipher_text(const std::string& input) -> std::string
{
    const std::string normalized = normalize_string(input);
    const std::size_t len = normalized.length();

    if(len == static_cast<std::size_t>(0))
    {
        return {};
    }

    const auto rc = rows_columns(len);
    const std::size_t r = rc.first;
    const std::size_t c = rc.second;

    std::string cipher{};
    cipher.reserve(r * c);

    for(std::size_t col = 0U; col < c; ++col)
    {
        for(std::size_t row = 0U; row < r; ++row)
        {
            const std::size_t index = ((row * c) + col);
            if(index < len)
            {
                cipher.push_back(normalized[index]);
            }
            else
            {
                /* skip padding positions */
            }
        }
    }

    return cipher;
}

auto normalized_cipher_text(const std::string& input) -> std::string
{
    const std::string normalized = normalize_string(input);
    const std::size_t len = normalized.length();

    if(len == static_cast<std::size_t>(0))
    {
        return {};
    }

    const auto rc = rows_columns(len);
    const std::size_t r = rc.first;
    const std::size_t c = rc.second;

    std::string output{};

    for(std::size_t col = 0U; col < c; ++col)
    {
        if(col != static_cast<std::size_t>(0))
        {
            output.push_back(' ');
        }

        for(std::size_t row = 0U; row < r; ++row)
        {
            const std::size_t index = ((row * c) + col);
            if(index < len)
            {
                output.push_back(normalized[index]);
            }
            else
            {
                output.push_back(' ');
            }
        }
    }

    return output;
}

/* cipher class member definitions */

cipher::cipher(const std::string& text) : m_input{text} {}

auto cipher::normalize_plain_text() const -> std::string
{
    return crypto_square::normalize_plain_text(m_input);
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    return crypto_square::plaintext_segments(m_input);
}

auto cipher::cipher_text() const -> std::string
{
    return crypto_square::cipher_text(m_input);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalized_cipher_text(m_input);
}

}  // namespace crypto_square

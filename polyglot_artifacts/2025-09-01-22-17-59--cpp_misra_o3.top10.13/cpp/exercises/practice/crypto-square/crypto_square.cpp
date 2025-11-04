#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <locale>
#include <utility>

namespace crypto_square {

namespace {

[[nodiscard]] auto compute_dimensions(std::size_t length) -> std::pair<std::size_t, std::size_t>
{
    /* Handle the empty-string case explicitly to avoid unsigned wraparound. */
    if(length == static_cast<std::size_t>(0U))
    {
        return { static_cast<std::size_t>(0U), static_cast<std::size_t>(0U) };
    }

    const double root { std::sqrt(static_cast<double>(length)) };

    std::size_t columns { static_cast<std::size_t>(std::ceil(root)) };
    std::size_t rows    { static_cast<std::size_t>(std::floor(root)) };

    if((rows * columns) < length)
    {
        rows = columns;
    }

    return { rows, columns };
}

} // unnamed namespace

auto normalize_plaintext(std::string_view text) -> std::string
{
    std::string normalized {};
    normalized.reserve(text.size());

    const std::locale loc {};

    for(char ch : text)
    {
        if(std::isalnum(ch, loc) != 0)
        {
            normalized.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    return normalized;
}

auto plaintext_segments(std::string_view text) -> std::vector<std::string>
{
    const std::string normalized { normalize_plaintext(text) };

    const std::pair<std::size_t, std::size_t> dims { compute_dimensions(normalized.size()) };
    const std::size_t columns { dims.second };

    std::vector<std::string> segments {};
    for(std::size_t idx { 0U }; idx < normalized.size(); idx += columns)
    {
        segments.emplace_back(normalized.substr(idx, columns));
    }

    return segments;
}

auto ciphertext(std::string_view text) -> std::string
{
    const std::vector<std::string> segments { plaintext_segments(text) };
    const std::size_t rows { segments.size() };
    const std::size_t columns { segments.empty() ? static_cast<std::size_t>(0U) : segments.front().size() };

    std::string cipher {};
    cipher.reserve(rows * columns);

    for(std::size_t col { 0U }; col < columns; ++col)
    {
        for(const std::string& row_str : segments)
        {
            if(col < row_str.size())
            {
                cipher.push_back(row_str[col]);
            }
        }
    }

    return cipher;
}

auto normalize_ciphertext(std::string_view text) -> std::string
{
    const std::string cipher { ciphertext(text) };

    if(cipher.empty())
    {
        return std::string {};
    }

    const std::pair<std::size_t, std::size_t> dims { compute_dimensions(cipher.size()) };
    const std::size_t rows { dims.first };
    const std::size_t columns { dims.second };

    std::vector<std::string> chunks(columns, std::string(rows, ' '));

    std::size_t index { 0U };
    for(std::size_t col { 0U }; col < columns; ++col)
    {
        for(std::size_t row { 0U }; row < rows; ++row)
        {
            if(index < cipher.size())
            {
                chunks[col][row] = cipher[index];
                ++index;
            }
        }
    }

    std::string result {};
    for(std::size_t col { 0U }; col < columns; ++col)
    {
        if(col > static_cast<std::size_t>(0U))
        {
            result.push_back(' ');
        }
        result.append(chunks[col]);
    }

    return result;
}

/* ---------------------------------------------------------------------- */
/*  cipher class implementation                                           */
/* ---------------------------------------------------------------------- */

cipher::cipher(std::string_view text_in) : m_input{text_in}
{
    /* constructor body intentionally left blank */
}

auto cipher::normalize_plaintext() const -> std::string
{
    return crypto_square::normalize_plaintext(m_input);
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    return crypto_square::plaintext_segments(m_input);
}

auto cipher::ciphertext() const -> std::string
{
    return crypto_square::ciphertext(m_input);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalize_ciphertext(m_input);
}

}  // namespace crypto_square

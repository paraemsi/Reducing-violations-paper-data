#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <locale>
#include <utility>

namespace {

/* Helper to compute the rectangle dimensions that satisfy:
 *   r * c >= len, c >= r, and c - r <= 1                                    */
auto compute_dimensions(crypto_square::index_t len)
    -> std::pair<crypto_square::index_t, crypto_square::index_t>
{
    if(len == static_cast<crypto_square::index_t>(0U))
    {
        return {static_cast<crypto_square::index_t>(0U),
                static_cast<crypto_square::index_t>(0U)};
    }

    const double root {std::sqrt(static_cast<double>(len))};

    crypto_square::index_t c {
        static_cast<crypto_square::index_t>(std::ceil(root))};
    crypto_square::index_t r {
        static_cast<crypto_square::index_t>(std::floor(root))};

    if(((r * c) < len))
    {
        ++r;
    }

    return {r, c};
}

} // unnamed namespace

namespace crypto_square {

auto normalize_plain_text(const std::string& input) -> std::string
{
    const std::locale loc {};
    std::string       result {};
    result.reserve(input.size());

    for(char ch : input)
    {
        if(std::isalnum(ch, loc) != 0)
        {
            const char lower {static_cast<char>(std::tolower(ch, loc))};
            result.push_back(lower);
        }
    }

    return result;
}

auto plain_text_segments(const std::string& input) -> std::vector<std::string>
{
    const std::string normalized {normalize_plain_text(input)};
    const index_t     len        {static_cast<index_t>(normalized.length())};

    const auto [r, c] {compute_dimensions(len)};

    std::vector<std::string> segments {};
    segments.reserve(r);

    for(index_t start = static_cast<index_t>(0U); start < len;
        start += c)
    {
        segments.emplace_back(
            normalized.substr(start, static_cast<std::size_t>(c)));
    }

    return segments;
}

auto ciphertext(const std::string& input) -> std::string
{
    const auto segments {plain_text_segments(input)};
    if(segments.empty())
    {
        return std::string {};
    }

    const index_t r {static_cast<index_t>(segments.size())};
    const index_t c {static_cast<index_t>(segments.front().length())};

    std::string cipher {};
    cipher.reserve(static_cast<std::size_t>(r * c));

    for(index_t col = static_cast<index_t>(0U); col < c; ++col)
    {
        for(const std::string& row : segments)
        {
            if(col < static_cast<index_t>(row.length()))
            {
                cipher.push_back(row[static_cast<std::size_t>(col)]);
            }
        }
    }

    return cipher;
}

auto normalized_cipher_text(const std::string& input) -> std::string
{
    const std::string cipher {ciphertext(input)};
    if(cipher.empty())
    {
        return std::string {};
    }

    const index_t len {static_cast<index_t>(cipher.length())};

    const auto [r, c] {compute_dimensions(len)};

    std::string result {};
    result.reserve(static_cast<std::size_t>(len + c)); // spaces included

    for(index_t col = static_cast<index_t>(0U); col < c; ++col)
    {
        const index_t start {static_cast<index_t>(col * r)};
        const std::string chunk {
            cipher.substr(static_cast<std::size_t>(start),
                          static_cast<std::size_t>(r))};

        if(col != static_cast<index_t>(0U))
        {
            result.push_back(' ');
        }

        result.append(chunk);

        if(chunk.length() < static_cast<std::size_t>(r))
        {
            result.append(static_cast<std::size_t>(r - chunk.length()), ' ');
        }
    }

    return result;
}

/* ------------------------------------------------------------------------- */
/* cipher class member-function definitions                                   */
/* ------------------------------------------------------------------------- */

cipher::cipher(const std::string& text) : m_input(text) {}

auto cipher::normalize_plain_text() const -> std::string
{
    return ::crypto_square::normalize_plain_text(m_input);
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    return ::crypto_square::plain_text_segments(m_input);
}

auto cipher::ciphertext() const -> std::string
{
    return ::crypto_square::ciphertext(m_input);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return ::crypto_square::normalized_cipher_text(m_input);
}

}  // namespace crypto_square

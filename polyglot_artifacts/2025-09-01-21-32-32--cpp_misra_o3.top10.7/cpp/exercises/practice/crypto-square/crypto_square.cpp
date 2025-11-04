#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <locale>

namespace crypto_square {

namespace {

/*  Helper to build the locale once. */
auto default_locale() -> const std::locale &
{
    static const std::locale loc {};
    return loc;
}

}  // namespace

auto normalize_plain_text(std::string_view text) -> std::string
{
    std::string result {};
    result.reserve(text.size());

    const std::locale & loc { default_locale() };

    for(char ch : text)
    {
        if(std::isalnum(ch, loc) != 0)
        {
            result.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
        else
        {
            /*  Discard non-alphanumeric characters. */
        }
    }

    return result;
}

auto square_size(std::string_view normalized_text) -> std::uint64_t
{
    const std::uint64_t len { static_cast<std::uint64_t>(normalized_text.size()) };

    if(len == static_cast<std::uint64_t>(0U))
    {
        return static_cast<std::uint64_t>(0U);
    }

    const double root { std::sqrt(static_cast<double>(len)) };

    std::uint64_t r { static_cast<std::uint64_t>(std::floor(root)) };
    std::uint64_t c { r };

    if((r * c) < len)
    {
        ++c;
    }

    if((r * c) < len)
    {
        ++r;
    }

    /*  At this point:
     *  - (r * c) >= len
     *  - c >= r
     *  - c - r <= 1
     */
    return c;
}

auto plaintext_segments(std::string_view text) -> std::vector<std::string>
{
    const std::string normalized { normalize_plain_text(text) };
    const std::uint64_t col { square_size(normalized) };

    std::vector<std::string> segments {};
    if(col == static_cast<std::uint64_t>(0U))
    {
        return segments;
    }

    for(std::uint64_t idx { static_cast<std::uint64_t>(0U) }; idx < normalized.size(); idx += col)
    {
        const std::uint64_t len { std::min(col, static_cast<std::uint64_t>(normalized.size() - idx)) };
        segments.emplace_back(normalized.substr(idx, len));
    }

    return segments;
}

auto ciphertext(std::string_view text) -> std::string
{
    const auto segments { plaintext_segments(text) };
    if(segments.empty())
    {
        return std::string {};
    }

    const std::uint64_t rows { static_cast<std::uint64_t>(segments.size()) };
    const std::uint64_t cols { static_cast<std::uint64_t>(segments.front().size()) };

    std::string cipher {};
    cipher.reserve(rows * cols);

    for(std::uint64_t c { static_cast<std::uint64_t>(0U) }; c < cols; ++c)
    {
        for(std::uint64_t r { static_cast<std::uint64_t>(0U) }; r < rows; ++r)
        {
            if(c < segments[r].size())
            {
                cipher.push_back(segments[r][static_cast<std::size_t>(c)]);
            }
        }
    }

    return cipher;
}

auto normalize_cipher_text(std::string_view text) -> std::string
{
    const std::string norm { normalize_plain_text(text) };
    if(norm.empty())
    {
        return std::string {};
    }

    const std::uint64_t c { square_size(norm) };
    const std::uint64_t r { static_cast<std::uint64_t>((norm.size() + c - static_cast<std::uint64_t>(1U)) / c) };

    const std::string raw_cipher { ciphertext(text) };

    /*  Allocate: cipher text plus (c - 1) spaces. */
    std::string output {};
    output.reserve(raw_cipher.size() + c); /* conservative */

    for(std::uint64_t col { static_cast<std::uint64_t>(0U) }; col < c; ++col)
    {
        for(std::uint64_t row { static_cast<std::uint64_t>(0U) }; row < r; ++row)
        {
            const std::uint64_t index { (col * r) + row };
            if(index < raw_cipher.size())
            {
                output.push_back(raw_cipher[static_cast<std::size_t>(index)]);
            }
            else
            {
                output.push_back(' ');
            }
        }

        if(col + static_cast<std::uint64_t>(1U) < c)
        {
            output.push_back(' ');
        }
    }

    return output;
}

/* ------------------------------------------------------------------ */
/*  cipher                                                             */
/* ------------------------------------------------------------------ */

cipher::cipher(std::string_view text) : original_(text) {}

auto cipher::normalized_cipher_text() const -> std::string
{
    return normalize_cipher_text(original_);
}

}  // namespace crypto_square

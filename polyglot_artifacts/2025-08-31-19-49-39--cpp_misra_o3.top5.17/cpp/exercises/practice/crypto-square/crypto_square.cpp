#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <vector>

namespace crypto_square {

/* ------------------------------------------------------------------------- */
/*  cipher – constructor                                                     */
/* ------------------------------------------------------------------------- */
cipher::cipher(::std::string_view text)
{
    normalized_.reserve(text.size());
    for (char ch : text)
    {
        if (::std::isalnum(static_cast<unsigned char>(ch)) != 0)
        {
            normalized_.push_back(
                static_cast<char>(::std::tolower(static_cast<unsigned char>(ch))));
        }
    }
}

/* ------------------------------------------------------------------------- */
/*  cipher – helpers                                                         */
/* ------------------------------------------------------------------------- */
auto cipher::normalized_cipher_text() const -> ::std::string
{
    return normalized_;
}

auto cipher::ciphertext() const -> ::std::string
{
    const ::std::uint32_t length = static_cast<::std::uint32_t>(normalized_.size());
    if (length == 0U)
    {
        return ::std::string {};
    }

    const double sqrt_len = ::std::sqrt(static_cast<double>(length));
    const ::std::uint32_t columns =
        static_cast<::std::uint32_t>(::std::ceil(sqrt_len));
    const ::std::uint32_t rows =
        static_cast<::std::uint32_t>(
            ::std::ceil(static_cast<double>(length)
                        / static_cast<double>(columns)));

    ::std::vector<::std::string> chunks(columns, ::std::string {});
    for (::std::uint32_t col = 0U; col < columns; ++col)
    {
        chunks[col].reserve(rows);
        for (::std::uint32_t row = 0U; row < rows; ++row)
        {
            const ::std::uint32_t index = ((row * columns) + col);
            if (index < length)
            {
                chunks[col].push_back(normalized_[index]);
            }
            else
            {
                chunks[col].push_back(' ');
            }
        }
    }

    ::std::string cipher_out {};
    cipher_out.reserve(((rows + 1U) * columns));
    for (::std::uint32_t col = 0U; col < columns; ++col)
    {
        cipher_out.append(chunks[col]);
        if ((col + 1U) < columns)
        {
            cipher_out.push_back(' ');
        }
    }

    return cipher_out;
}

auto cipher_text(::std::string_view plain) -> ::std::string
{
    /* Normalize the input: keep alphanumeric characters and convert them
       to lowercase */
    ::std::string normalized {};
    normalized.reserve(plain.size());
    for (char ch : plain)
    {
        if (::std::isalnum(static_cast<unsigned char>(ch)) != 0)
        {
            normalized.push_back(
                static_cast<char>(::std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    const ::std::uint32_t length = static_cast<::std::uint32_t>(normalized.size());
    if (length == 0U)
    {
        return ::std::string {};
    }

    const double sqrt_len = ::std::sqrt(static_cast<double>(length));
    const ::std::uint32_t columns =
        static_cast<::std::uint32_t>(::std::ceil(sqrt_len));
    const ::std::uint32_t rows =
        static_cast<::std::uint32_t>(
            ::std::ceil(static_cast<double>(length) / static_cast<double>(columns)));

    /* Build column-wise chunks */
    ::std::vector<::std::string> chunks(columns, ::std::string {});
    for (::std::uint32_t col = 0U; col < columns; ++col)
    {
        chunks[col].reserve(rows);
        for (::std::uint32_t row = 0U; row < rows; ++row)
        {
            const ::std::uint32_t index = ((row * columns) + col);
            if (index < length)
            {
                chunks[col].push_back(normalized[index]);
            }
            else
            {
                chunks[col].push_back(' ');
            }
        }
    }

    /* Join the chunks separated by a single space */
    ::std::string cipher_out {};
    cipher_out.reserve(((rows + 1U) * columns)); /* Rough upper bound including spaces */
    for (::std::uint32_t col = 0U; col < columns; ++col)
    {
        cipher_out.append(chunks[col]);
        if ((col + 1U) < columns)
        {
            cipher_out.push_back(' ');
        }
    }

    return cipher_out;
}

auto cipher(::std::string_view text) -> cipher
{
    return crypto_square::cipher{text};
}

}  // namespace crypto_square

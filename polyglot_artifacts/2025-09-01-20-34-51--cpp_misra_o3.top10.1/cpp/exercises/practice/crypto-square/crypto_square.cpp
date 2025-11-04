#include "crypto_square.h"

#include <cmath>
#include <locale>
#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

cipher::cipher(std::string_view input)
    : normalized_()
{
    const std::locale loc{};
    normalized_.reserve(input.size());

    for(char ch : input)
    {
        const unsigned char uch{static_cast<unsigned char>(ch)};

        if(::std::isalnum(uch, loc) != 0)
        {
            normalized_.push_back(
                static_cast<char>(::std::tolower(uch, loc)));
        }
    }
}

auto cipher::normalize_plain_text() const -> std::string
{
    return normalized_;
}

auto cipher::square_size() const -> std::size_t
{
    if(normalized_.empty())
    {
        return static_cast<std::size_t>(0U);
    }

    const std::size_t length{normalized_.length()};
    const double      sqrt_len{::std::sqrt(static_cast<double>(length))};

    return static_cast<std::size_t>(::std::ceil(sqrt_len));
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments{};

    if(normalized_.empty())
    {
        return segments;
    }

    const std::size_t length{normalized_.length()};
    const double      sqrt_len{::std::sqrt(static_cast<double>(length))};
    const std::size_t columns{static_cast<std::size_t>(::std::ceil(sqrt_len))};
    const std::size_t rows{
        (length + columns - static_cast<std::size_t>(1U)) / columns};

    segments.reserve(rows);

    for(std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row)
    {
        const std::size_t start{row * columns};
        segments.emplace_back(normalized_.substr(start, columns));
    }

    return segments;
}

auto cipher::ciphertext() const -> std::string
{
    if(normalized_.empty())
    {
        return std::string{};
    }

    const std::size_t length{normalized_.length()};
    const double      sqrt_len{::std::sqrt(static_cast<double>(length))};
    const std::size_t columns{static_cast<std::size_t>(::std::ceil(sqrt_len))};
    const std::size_t rows{
        (length + columns - static_cast<std::size_t>(1U)) / columns};

    std::string result{};
    result.reserve(length);

    for(std::size_t col = static_cast<std::size_t>(0U); col < columns; ++col)
    {
        for(std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row)
        {
            const std::size_t index{(row * columns) + col};

            if(index < length)
            {
                result.push_back(normalized_[index]);
            }
        }
    }

    return result;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    if(normalized_.empty())
    {
        return std::string{};
    }

    const std::size_t length{normalized_.length()};
    const double      sqrt_len{::std::sqrt(static_cast<double>(length))};
    const std::size_t columns{static_cast<std::size_t>(::std::ceil(sqrt_len))};
    const std::size_t rows{
        (length + columns - static_cast<std::size_t>(1U)) / columns};

    std::string result{};
    result.reserve(
        (columns * rows) + (columns - static_cast<std::size_t>(1U)));

    for(std::size_t col = static_cast<std::size_t>(0U); col < columns; ++col)
    {
        for(std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row)
        {
            const std::size_t index{(row * columns) + col};

            if(index < length)
            {
                result.push_back(normalized_[index]);
            }
            else
            {
                result.push_back(' ');
            }
        }

        if((col + static_cast<std::size_t>(1U)) < columns)
        {
            result.push_back(' ');
        }
    }

    return result;
}


auto cipher(std::string_view input) -> cipher
{
    return cipher{input};
}

}  // namespace crypto_square

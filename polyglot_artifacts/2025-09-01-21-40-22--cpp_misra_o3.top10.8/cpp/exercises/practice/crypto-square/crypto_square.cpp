#include "crypto_square.h"

#include <locale>
#include <cmath>
#include <algorithm>

namespace crypto_square {

auto normalize_plain_text(const std::string &plain_text) -> std::string
{
    const std::locale loc {};
    std::string normalized {};
    normalized.reserve(plain_text.size());

    for (char ch : plain_text)
    {
        if (std::isalnum(ch, loc) != 0)
        {
            normalized.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
        else
        {
            /* ignore non-alphanumeric characters */
        }
    }

    return normalized;
}

auto square_size(const std::string &plain_text) -> std::size_t
{
    const std::string normalized { normalize_plain_text(plain_text) };
    const std::size_t length { normalized.size() };

    if (length == static_cast<std::size_t>(0))
    {
        return static_cast<std::size_t>(0);
    }

    const double root { std::sqrt(static_cast<double>(length)) };
    const std::size_t columns { static_cast<std::size_t>(std::ceil(root)) };
    const std::size_t rows { (length + (columns - static_cast<std::size_t>(1))) / columns };

    if ((columns - rows) > static_cast<std::size_t>(1))
    {
        /* Adjust to satisfy the constraint c - r <= 1 */
        return columns + static_cast<std::size_t>(1);
    }

    return columns;
}

auto plain_text_segments(const std::string &plain_text) -> std::vector<std::string>
{
    const std::string normalized { normalize_plain_text(plain_text) };
    const std::size_t columns { square_size(plain_text) };

    std::vector<std::string> segments {};
    segments.reserve((normalized.size() + (columns - static_cast<std::size_t>(1))) / columns);

    for (std::size_t index { static_cast<std::size_t>(0) }; index < normalized.size(); index += columns)
    {
        segments.emplace_back(normalized.substr(index, columns));
    }

    return segments;
}

auto cipher_text(const std::string &plain_text) -> std::string
{
    const std::vector<std::string> segments { plain_text_segments(plain_text) };

    if (segments.empty())
    {
        return std::string {};
    }

    const std::size_t rows { segments.size() };
    const std::size_t columns { segments.front().size() };

    std::string cipher {};
    cipher.reserve(rows * columns);

    for (std::size_t col { static_cast<std::size_t>(0) }; col < columns; ++col)
    {
        for (std::size_t row { static_cast<std::size_t>(0) }; row < rows; ++row)
        {
            if (col < segments[row].size())
            {
                cipher.push_back(segments[row][col]);
            }
            else
            {
                /* no character in this row/column */
            }
        }
    }

    return cipher;
}

auto normalized_cipher_text(const std::string &plain_text) -> std::string
{
    const std::vector<std::string> segments { plain_text_segments(plain_text) };

    if (segments.empty())
    {
        return std::string {};
    }

    const std::size_t rows { segments.size() };
    const std::size_t columns { square_size(plain_text) };

    std::string output {};
    output.reserve(rows * (columns + static_cast<std::size_t>(1))); /* plus spaces */

    for (std::size_t col { static_cast<std::size_t>(0) }; col < columns; ++col)
    {
        if (col != static_cast<std::size_t>(0))
        {
            output.push_back(' ');
        }

        for (std::size_t row { static_cast<std::size_t>(0) }; row < rows; ++row)
        {
            if (col < segments[row].size())
            {
                output.push_back(segments[row][col]);
            }
            else
            {
                output.push_back(' ');
            }
        }
    }

    return output;
}

/*------------------------------------------------------------------------------*
 *  class cipher implementation                                                 *
 *------------------------------------------------------------------------------*/
cipher::cipher(const std::string &text)
    : normalized_{ normalize_plain_text(text) }
{
    columns_ = square_size(text);

    if (columns_ != static_cast<std::size_t>(0))
    {
        rows_ = (normalized_.size() + (columns_ - static_cast<std::size_t>(1))) / columns_;
    }
    else
    {
        rows_ = static_cast<std::size_t>(0);
    }
}

auto cipher::normalize_plain_text() const -> std::string
{
    return normalized_;
}

auto cipher::size() const -> std::size_t
{
    return columns_;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments {};
    segments.reserve(rows_);

    for (std::size_t index { static_cast<std::size_t>(0) };
         index < normalized_.size();
         index += columns_)
    {
        segments.emplace_back(normalized_.substr(index, columns_));
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    const std::vector<std::string> segments { plain_text_segments() };

    if (segments.empty())
    {
        return std::string {};
    }

    std::string cipher_out {};
    cipher_out.reserve(rows_ * columns_);

    for (std::size_t col { static_cast<std::size_t>(0) }; col < columns_; ++col)
    {
        for (std::size_t row { static_cast<std::size_t>(0) }; row < rows_; ++row)
        {
            if (col < segments[row].size())
            {
                cipher_out.push_back(segments[row][col]);
            }
        }
    }

    return cipher_out;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    const std::vector<std::string> segments { plain_text_segments() };

    if (segments.empty())
    {
        return std::string {};
    }

    std::string output {};
    output.reserve(rows_ * (columns_ + static_cast<std::size_t>(1)));

    for (std::size_t col { static_cast<std::size_t>(0) }; col < columns_; ++col)
    {
        if (col != static_cast<std::size_t>(0))
        {
            output.push_back(' ');
        }

        for (std::size_t row { static_cast<std::size_t>(0) }; row < rows_; ++row)
        {
            if (col < segments[row].size())
            {
                output.push_back(segments[row][col]);
            }
            else
            {
                output.push_back(' ');
            }
        }
    }

    return output;
}

}  // namespace crypto_square

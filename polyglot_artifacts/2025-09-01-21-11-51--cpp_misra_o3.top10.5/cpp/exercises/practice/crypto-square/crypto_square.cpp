#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& input)
{
    const std::locale loc {};
    normalized_.reserve(input.size());

    for (char ch : input)
    {
        if (std::isalnum(ch, loc) != 0)
        {
            normalized_.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    const std::size_t length { normalized_.length() };

    if (length == static_cast<std::size_t>(0U))
    {
        columns_ = static_cast<std::size_t>(0U);
        rows_ = static_cast<std::size_t>(0U);
        return;
    }

    const double root { std::sqrt(static_cast<double>(length)) };
    columns_ = static_cast<std::size_t>(std::ceil(root));
    rows_ =
        static_cast<std::size_t>((length + columns_ - static_cast<std::size_t>(1U)) / columns_);

    /* store plain-text segments row-wise */
    segments_.assign(rows_, std::string {});
    segments_.shrink_to_fit();

    /* build the row segments */
    for (std::size_t idx { 0U }; idx < length; ++idx)
    {
        const std::size_t row { idx / columns_ };
        segments_[row].push_back(normalized_[idx]);
    }
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return normalized_;
}

auto cipher::cipher_text() const -> std::string
{
    if (normalized_.empty())
    {
        return std::string {};
    }

    /* build the cipher text: read down the columns, left-to-right             */
    std::string encoded {};
    encoded.reserve((rows_ + static_cast<std::size_t>(1U)) * columns_);

    for (std::size_t col { 0U }; col < columns_; ++col)
    {
        if (col != static_cast<std::size_t>(0U))
        {
            encoded.push_back(' ');
        }

        for (const auto& row_seg : segments_)
        {
            if (col < row_seg.length())
            {
                encoded.push_back(row_seg[col]);
            }
            else
            {
                encoded.push_back(' ');
            }
        }
    }

    return encoded;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    return segments_;
}

}  // namespace crypto_square

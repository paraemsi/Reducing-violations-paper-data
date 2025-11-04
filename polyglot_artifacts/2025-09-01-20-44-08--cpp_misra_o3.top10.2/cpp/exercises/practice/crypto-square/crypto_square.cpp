#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <string>
#include <vector>
#include <utility>

namespace crypto_square {

namespace {

/* Determine the rectangle dimensions (rows r, columns c) */
[[nodiscard]] auto compute_dimensions(const std::size_t length) -> std::pair<std::size_t, std::size_t>
{
    if(length == static_cast<std::size_t>(0U))
    {
        return {0U, 0U};
    }

    const double root {std::sqrt(static_cast<double>(length))};
    std::size_t c {static_cast<std::size_t>(std::ceil(root))};
    std::size_t r {static_cast<std::size_t>(std::floor(root))};

    if((r * c) < length)
    {
        ++r;
    }

    /* Guarantee c >= r and c − r ≤ 1 as required */
    if(c < r)
    {
        std::swap(c, r);
    }

    return {r, c};
}

/* Normalize the input string: keep alphanumerics and convert to lowercase */
[[nodiscard]] auto normalize(const std::string& text) -> std::string
{
    const std::locale loc {};
    std::string normalised {};
    normalised.reserve(text.size());

    for(const char ch : text)
    {
        if(std::isalnum(ch, loc) != 0)
        {
            normalised.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }
    return normalised;
}

} // namespace

auto encode(const std::string& text) -> std::string
{
    const std::string normalized {normalize(text)};
    const std::size_t length {normalized.length()};

    const auto [rows, cols] {compute_dimensions(length)};

    if(length == static_cast<std::size_t>(0U))
    {
        return {};
    }

    /* Build the rectangle row-wise, padding the final row with spaces */
    std::vector<std::string> rectangle(rows, std::string(cols, ' '));

    for(std::size_t i {0U}; i < length; ++i)
    {
        const std::size_t row {(i / cols)};
        const std::size_t col {(i % cols)};
        rectangle[row][col] = normalized[i];
    }

    /* Read down the columns, forming chunks of length rows */
    std::string output {};
    output.reserve(length + (cols - 1U)); /* spaces between chunks */

    for(std::size_t col {0U}; col < cols; ++col)
    {
        std::string chunk {};
        chunk.reserve(rows);

        for(std::size_t row {0U}; row < rows; ++row)
        {
            chunk.push_back(rectangle[row][col]);
        }


        if(col != static_cast<std::size_t>(0U))
        {
            output.push_back(' ');
        }

        output.append(chunk);
    }

    return output;
}

/* Implementation of the cipher class */

cipher::cipher(const std::string& text_in)
    : normalized_{normalize(text_in)}
    , rows_{0U}
    , cols_{0U}
    , rectangle_{}
{
    const std::size_t length {normalized_.length()};
    const auto        dims   {compute_dimensions(length)};
    rows_ = dims.first;
    cols_ = dims.second;

    if(rows_ == static_cast<std::size_t>(0U))
    {
        return;
    }

    rectangle_.assign(rows_, std::string(cols_, ' '));

    for(std::size_t i {0U}; i < length; ++i)
    {
        const std::size_t row {(i / cols_)};
        const std::size_t col {(i % cols_)};
        rectangle_[row][col] = normalized_[i];
    }
}

auto cipher::normalize_plain_text() const -> std::string
{
    return normalized_;
}

auto cipher::size() const -> std::size_t
{
    return cols_;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments {};

    if(rows_ == static_cast<std::size_t>(0U))
    {
        return segments;
    }

    segments.reserve(rows_);

    for(std::size_t row {0U}; row < rows_; ++row)
    {
        std::string segment {rectangle_[row]};

        while((!segment.empty()) && (segment.back() == ' '))
        {
            segment.pop_back();
        }

        segments.push_back(segment);
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    std::string output {};
    output.reserve(normalized_.length());

    for(std::size_t col {0U}; col < cols_; ++col)
    {
        for(std::size_t row {0U}; row < rows_; ++row)
        {
            const char ch {rectangle_[row][col]};
            if(ch != ' ')
            {
                output.push_back(ch);
            }
        }
    }
    return output;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    if(cols_ == static_cast<std::size_t>(0U))
    {
        return {};
    }

    std::string output {};
    output.reserve(normalized_.length() + (cols_ - 1U));

    for(std::size_t col {0U}; col < cols_; ++col)
    {
        std::string chunk {};
        chunk.reserve(rows_);

        for(std::size_t row {0U}; row < rows_; ++row)
        {
            chunk.push_back(rectangle_[row][col]);
        }


        if(col != static_cast<std::size_t>(0U))
        {
            output.push_back(' ');
        }

        output.append(chunk);
    }

    return output;
}

}  // namespace crypto_square

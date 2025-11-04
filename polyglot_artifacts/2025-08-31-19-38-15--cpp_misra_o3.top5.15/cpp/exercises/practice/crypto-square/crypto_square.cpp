#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cstdint>
#include <cstddef>

namespace crypto_square {

namespace
{

auto normalize(const std::string& input) -> std::string
{
    std::string output {};
    output.reserve(input.size());

    for(char ch : input)
    {
        if(std::isalnum(static_cast<unsigned char>(ch)) != 0)
        {
            output.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    return output;
}

auto calculate_dimensions(std::uint32_t length) -> std::pair<std::uint32_t, std::uint32_t>
{
    const double root { std::sqrt(static_cast<double>(length)) };
    std::uint32_t rows { static_cast<std::uint32_t>(std::floor(root)) };
    std::uint32_t cols { static_cast<std::uint32_t>(std::ceil(root)) };

    if((rows * cols) < length)
    {
        ++rows;
    }

    return { rows, cols };
}

} // unnamed namespace

std::string cipher_text(const std::string& input)
{
    const std::string normalized { normalize(input) };
    const std::uint32_t length { static_cast<std::uint32_t>(normalized.size()) };

    if(length == 0U)
    {
        return std::string {};
    }

    const auto [rows, cols] { calculate_dimensions(length) };

    std::vector<std::string> columns(cols, std::string {});
    for(std::uint32_t col { 0U }; col < cols; ++col)
    {
        columns[col].reserve(rows);
    }

    for(std::uint32_t idx { 0U }; idx < length; ++idx)
    {
        const std::uint32_t col { idx % cols };
        columns[col].push_back(normalized[idx]);
    }

    for(std::uint32_t col { 0U }; col < cols; ++col)
    {
        while(columns[col].size() < rows)
        {
            columns[col].push_back(' ');
        }
    }

    std::ostringstream oss {};
    for(std::uint32_t col { 0U }; col < cols; ++col)
    {
        if(col != 0U)
        {
            oss << ' ';
        }
        oss << columns[col];
    }

    return oss.str();
}

/*---------------------------------------------------------------------------*/
/*--- cipher class definitions ---------------------------------------------*/
/*---------------------------------------------------------------------------*/

cipher::cipher(const std::string& text) : normalized_(normalize(text))
{
}

std::string cipher::normalize_plain_text() const
{
    return normalized_;
}

std::size_t cipher::size() const
{
    const std::size_t len { normalized_.size() };

    if(len == 0U)
    {
        return 0U;
    }

    const double root { std::sqrt(static_cast<double>(len)) };

    return static_cast<std::size_t>(std::ceil(root));
}

std::vector<std::string> cipher::plain_text_segments() const
{
    const std::size_t col { size() };

    if(col == 0U)
    {
        return {};
    }

    std::vector<std::string> segments {};
    segments.reserve((normalized_.size() + col - 1U) / col);

    for(std::size_t idx { 0U }; idx < normalized_.size(); idx += col)
    {
        segments.push_back(normalized_.substr(idx, col));
    }

    return segments;
}

std::string cipher::cipher_text() const
{
    const std::size_t col { size() };
    const std::size_t len { normalized_.size() };

    if(col == 0U)
    {
        return {};
    }

    const std::size_t rows { (len + col - 1U) / col };
    std::string result {};
    result.reserve(len);

    for(std::size_t c { 0U }; c < col; ++c)
    {
        for(std::size_t r { 0U }; r < rows; ++r)
        {
            const std::size_t idx { (r * col) + c };
            if(idx < len)
            {
                result.push_back(normalized_[idx]);
            }
        }
    }

    return result;
}

std::string cipher::normalized_cipher_text() const
{
    const std::size_t col { size() };
    const std::size_t len { normalized_.size() };

    if(col == 0U)
    {
        return {};
    }

    const std::size_t rows { (len + col - 1U) / col };

    std::string result {};
    result.reserve(len + col - 1U);

    for(std::size_t c { 0U }; c < col; ++c)
    {
        if(c != 0U)
        {
            result.push_back(' ');
        }

        for(std::size_t r { 0U }; r < rows; ++r)
        {
            const std::size_t idx { (r * col) + c };
            if(idx < len)
            {
                result.push_back(normalized_[idx]);
            }
            else
            {
                result.push_back(' ');
            }
        }
    }

    return result;
}


}  // namespace crypto_square

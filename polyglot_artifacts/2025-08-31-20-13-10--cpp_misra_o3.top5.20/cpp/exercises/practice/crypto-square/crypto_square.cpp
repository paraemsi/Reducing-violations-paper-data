#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <locale>
#include <string>
#include <string_view>
#include <vector>

namespace {

/* Normalize text : keep only alpha-numerics, convert to lowercase */
[[nodiscard]] auto normalize(std::string_view text) -> std::string
{
    std::string result {};
    result.reserve(text.size());

    const std::locale loc {};
    for(char ch : text)
    {
        if(std::isalnum(ch, loc))
        {
            result.push_back(std::tolower(ch, loc));
        }
    }
    return result;
}

/* Compute rows (r) and columns (c) as per exercise rules                    */
[[nodiscard]] auto rectangle_dimensions(std::uint32_t len) -> std::pair<std::uint32_t, std::uint32_t>
{
    if(len == static_cast<std::uint32_t>(0U))
    {
        return {0U, 0U};
    }

    const double root     = std::sqrt(static_cast<double>(len));
    std::uint32_t columns = static_cast<std::uint32_t>(std::ceil(root));
    std::uint32_t rows    = static_cast<std::uint32_t>(std::floor(root));

    if((rows * columns) < len)
    {
        ++rows;
    }
    return {rows, columns};
}

} // unnamed namespace

namespace crypto_square {

/*======================================================================*/
/*  cipher_result – returned by factory function ‘cipher’               */
/*======================================================================*/
cipher_result::cipher_result(std::string_view text) : m_normalized{::normalize(text)}
{
}

auto cipher_result::normalized_cipher_text() const -> std::string
{
    return m_normalized;
}

auto cipher_result::cipher_text() const -> std::string
{
    const std::uint32_t len { static_cast<std::uint32_t>(m_normalized.size()) };
    if(len == static_cast<std::uint32_t>(0U))
    {
        return {};
    }

    auto [rows, columns] = ::rectangle_dimensions(len);

    std::vector<std::string> matrix(rows, std::string(columns, ' '));

    std::uint32_t idx { 0U };
    for(std::uint32_t r { 0U }; r < rows; ++r)
    {
        for(std::uint32_t c { 0U }; c < columns; ++c)
        {
            if(idx < len)
            {
                matrix[r][c] = m_normalized[idx];
                ++idx;
            }
        }
    }

    std::string result {};
    for(std::uint32_t c { 0U }; c < columns; ++c)
    {
        if(c != static_cast<std::uint32_t>(0U))
        {
            result.push_back(' ');
        }

        for(std::uint32_t r { 0U }; r < rows; ++r)
        {
            result.push_back(matrix[r][c]);
        }
    }
    return result;
}

/*--------------------------------------------------------------*/
/*  compatibility alias                                         */
/*--------------------------------------------------------------*/
auto cipher_result::ciphertext() const -> std::string
{
    return cipher_text();
}

/*======================================================================*/
/*  Factory function                                                    */
/*======================================================================*/
[[nodiscard]] auto cipher(std::string_view text) -> cipher_result
{
    return cipher_result{text};
}

} // namespace crypto_square

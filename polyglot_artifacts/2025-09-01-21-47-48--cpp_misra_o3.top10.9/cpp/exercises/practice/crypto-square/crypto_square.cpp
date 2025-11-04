#include "crypto_square.h"

#include <vector>
#include <locale>
#include <cmath>
#include <cstdint>
#include <utility>

namespace crypto_square {

namespace {

/* Normalize text: keep alphanumeric characters, convert to lower-case. */
auto normalize(const std::string& input) -> std::string
{
    std::string result {};
    const std::locale loc {};

    for(const char ch : input)
    {
        /* std::isalnum / std::tolower from <locale> comply with the rules. */
        if(std::isalnum(ch, loc) != 0)
        {
            result.push_back(std::tolower(ch, loc));
        }
    }

    return result;
}

/* Compute rectangle dimensions (rows, columns) given the text length. */
auto dimensions(const std::size_t length) -> std::pair<std::size_t, std::size_t>
{
    if(length == static_cast<std::size_t>(0U))
    {
        return {0U, 0U};
    }

    const double len_d = static_cast<double>(length);
    const std::size_t columns =
        static_cast<std::size_t>(std::ceil(std::sqrt(len_d)));
    const std::size_t rows =
        static_cast<std::size_t>((length + columns - 1U) / columns);

    return {rows, columns};
}

} // anonymous namespace

static auto compute_cipher_text(const std::string& input) -> std::string
{
    const std::string normalized_text = normalize(input);
    const std::size_t length = normalized_text.length();

    if(length == static_cast<std::size_t>(0U))
    {
        return std::string {};
    }

    const auto [rows, columns] = dimensions(length);

    /* Break the text into row-wise segments of length `columns`. */
    std::vector<std::string> segments {};
    segments.reserve(rows);
    for(std::size_t idx = 0U; idx < length; idx += columns)
    {
        segments.push_back(normalized_text.substr(idx, columns));
    }

    /* Read down the columns to build the cipher text (no spaces). */
    std::string cipher {};
    cipher.reserve(length);

    for(std::size_t col = 0U; col < columns; ++col)
    {
        for(const std::string& seg : segments)
        {
            if(col < seg.length())
            {
                cipher.push_back(seg[col]);
            }
        }
    }

    return cipher;
}

static auto compute_normalized_cipher_text(const std::string& input) -> std::string
{
    const std::string normalized_text = normalize(input);
    const std::size_t length = normalized_text.length();

    if(length == static_cast<std::size_t>(0U))
    {
        return std::string {};
    }

    const auto [rows, columns] = dimensions(length);

    /* Re-use row-wise segments of the plain text. */
    std::vector<std::string> segments {};
    segments.reserve(rows);
    for(std::size_t idx = 0U; idx < length; idx += columns)
    {
        segments.push_back(normalized_text.substr(idx, columns));
    }

    /* Build column-wise chunks padded with spaces to length `rows`. */
    std::string result {};
    result.reserve((rows + 1U) * columns); /* space after each chunk except last */

    for(std::size_t col = 0U; col < columns; ++col)
    {
        for(std::size_t row = 0U; row < rows; ++row)
        {
            const std::string& seg = segments[row];
            if(col < seg.length())
            {
                result.push_back(seg[col]);
            }
            else
            {
                result.push_back(' ');
            }
        }

        if((col + 1U) < columns)
        {
            result.push_back(' ');
        }
    }

    return result;
}

/* ------------------------------------------------------------------ */
/*  cipher facade object – satisfies the unit-test API expectations   */
/* ------------------------------------------------------------------ */

cipher_result::cipher_result(std::string input) : original_text_(std::move(input)) {}

auto cipher_result::cipher_text() const -> std::string
{
    return compute_cipher_text(original_text_);
}

auto cipher_result::normalized_cipher_text() const -> std::string
{
    return compute_normalized_cipher_text(original_text_);
}

[[nodiscard]] auto cipher(const std::string& input) -> cipher_result
{
    return cipher_result{input};
}


}  // namespace crypto_square

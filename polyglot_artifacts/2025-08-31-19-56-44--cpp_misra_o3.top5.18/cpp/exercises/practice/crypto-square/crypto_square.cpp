#include "crypto_square.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

namespace {

/* helper : produce normalised, lower-case alpha-numeric text */
auto normalised(const std::string & text) -> std::string
{
    std::string result {};
    result.reserve(text.size());

    for(char ch : text)
    {
        const int int_val { ::std::char_traits<char>::to_int_type(ch) };

        if(::std::isalnum(int_val) != 0)
        {
            const int lower_int { ::std::tolower(int_val) };
            result.push_back(::std::char_traits<char>::to_char_type(lower_int));
        }
        else
        {
            /* ignore non-alphanumeric characters */
        }
    }

    return result;
}

} // unnamed namespace

namespace crypto_square {

/* public API ------------------------------------------------------------- */
auto normalize_plain_text(const std::string & text) -> std::string
{
    return normalised(text);
}

auto square_size(const std::string & text) -> std::size_t
{
    const std::size_t len { normalised(text).size() };

    std::size_t c { static_cast<std::size_t>(0U) };
    while((c * c) < len)
    {
        ++c;
    }

    return c; /* number of columns (width) as per exercise constraints */
}

auto plain_text_segments(const std::string & text) -> std::vector<std::string>
{
    const std::string norm { normalised(text) };
    const std::size_t width { square_size(text) };

    std::vector<std::string> segments {};

    if(width == static_cast<std::size_t>(0U))
    {
        return segments;
    }

    for(std::size_t idx { static_cast<std::size_t>(0U) }; idx < norm.size(); idx += width)
    {
        const std::size_t len { (idx + width <= norm.size()) ? width
                                                             : static_cast<std::size_t>(norm.size() - idx) };
        segments.emplace_back(norm.substr(idx, len));
    }

    return segments;
}

auto cipher_text(const std::string & text) -> std::string
{
    const std::vector<std::string> rows { plain_text_segments(text) };
    if(rows.empty())
    {
        return std::string {};
    }

    const std::size_t width { square_size(text) };
    const std::size_t height { rows.size() };

    std::string encoded {};
    encoded.reserve(width * height);

    for(std::size_t col { static_cast<std::size_t>(0U) }; col < width; ++col)
    {
        for(const std::string & row : rows)
        {
            if(col < row.size())
            {
                encoded.push_back(row[col]);
            }
            else
            {
                /* missing character – skip (implicitly pads later) */
            }
        }
    }

    return encoded;
}

auto normalized_cipher_text(const std::string & text) -> std::string
{
    const std::string encoded { cipher_text(text) };

    const std::size_t width { square_size(text) };
    if(width == static_cast<std::size_t>(0U))
    {
        return std::string {};
    }

    const std::size_t height { (encoded.size() + width - static_cast<std::size_t>(1U)) / width };
    const std::size_t padded_len { width * height };

    std::string padded { encoded };
    padded.resize(padded_len, ' '); /* pad with spaces as required */

    std::string result {};
    for(std::size_t col { static_cast<std::size_t>(0U) }; col < width; ++col)
    {
        if(col != static_cast<std::size_t>(0U))
        {
            result.push_back(' ');
        }

        result.append(padded.substr(col * height, height));
    }

    return result;
}

cipher::cipher(const std::string & text) : m_text{text}
{
    /* constructor body intentionally left empty */
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalized_cipher_text(m_text);
}

auto cipher(const std::string & text) -> cipher
{
    return crypto_square::cipher{text}; /* construct façade object */
}


}  // namespace crypto_square

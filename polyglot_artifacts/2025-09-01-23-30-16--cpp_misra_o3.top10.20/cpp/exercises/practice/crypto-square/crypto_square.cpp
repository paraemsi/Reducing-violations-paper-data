#include "crypto_square.h"

#include <cstdint>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

using size_type = std::uint64_t;

cipher::cipher(const std::string& input)
{
    const std::locale loc {};
    std::string normalized {};
    normalized.reserve(input.size());

    for (char ch : input)
    {
        /*  Convert to unsigned to satisfy MISRA rule that prohibits
            relying on the signedness of plain `char` when passing to
            character classification functions. */
        const unsigned char uch { static_cast<unsigned char>(ch) };

        if (std::isalnum(uch, loc) != 0)
        {
            normalized.push_back(static_cast<char>(std::tolower(uch, loc)));
        }
    }

    const size_type n = static_cast<size_type>(normalized.size());
    if (n == static_cast<size_type>(0U))
    {
        /*  No alpha-numeric characters in the input.  */
        m_normalized_cipher_text.clear();
        m_cipher_text.clear();
        return;
    }

    size_type rows = static_cast<size_type>(1U);
    size_type cols = static_cast<size_type>(0U);

    for (;; ++rows)
    {
        cols = rows;
        if ((static_cast<size_type>(cols * rows)) < n)
        {
            ++cols;
        }

        if (((cols * rows) >= n) && ((cols - rows) <= static_cast<size_type>(1U)))
        {
            break;
        }
    }

    std::vector<std::string> chunks {};
    chunks.reserve(cols);

    for (size_type col = static_cast<size_type>(0U); col < cols; ++col)
    {
        std::string chunk {};
        chunk.reserve(rows);

        for (size_type row = static_cast<size_type>(0U); row < rows; ++row)
        {
            const size_type idx = ((row * cols) + col);
            if (idx < n)
            {
                chunk.push_back(normalized[idx]);
            }
            else
            {
                chunk.push_back(' ');
            }
        }
        chunks.push_back(chunk);
    }

    std::string encoded {};
    encoded.reserve((cols * rows) + (cols - static_cast<size_type>(1U)));

    for (size_type i = static_cast<size_type>(0U); i < cols; ++i)
    {
        encoded += chunks[i];
        if (i != (cols - static_cast<size_type>(1U)))
        {
            encoded.push_back(' ');
        }
    }

    /*  Store results in the data members.  */
    m_normalized_cipher_text = normalized;
    m_cipher_text            = encoded;
}

}  // namespace crypto_square
auto cipher::normalized_cipher_text() const -> std::string
{
    return m_normalized_cipher_text;
}

auto cipher::cipher_text() const -> std::string
{
    return m_cipher_text;
}

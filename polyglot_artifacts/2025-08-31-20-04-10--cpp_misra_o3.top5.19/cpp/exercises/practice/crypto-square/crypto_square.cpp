#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

    auto normalize_plain_text(const std::string &text) -> std::string
    {
        std::string normalized {};
        normalized.reserve(text.length());

        for(char ch : text)
        {
            if(std::isalnum(static_cast<unsigned char>(ch)) != 0)
            {
                char lower_ch {static_cast<char>(std::tolower(static_cast<unsigned char>(ch)))};
                normalized.push_back(lower_ch);
            }
        }

        return normalized;
    }

    auto size(const std::string &text) -> index_t
    {
        const std::string normalized {normalize_plain_text(text)};
        const index_t len {normalized.length()};

        if(len == 0U)
        {
            return 0U;
        }

        const double root {std::sqrt(static_cast<double>(len))};

        index_t columns {static_cast<index_t>(std::ceil(root))};
        index_t rows {static_cast<index_t>(std::floor(root))};

        if(((rows * columns) < len))
        {
            ++rows;
        }

        return columns;
    }

    auto plain_text_segments(const std::string &text) -> std::vector<std::string>
    {
        const std::string normalized {normalize_plain_text(text)};
        const index_t columns {size(text)};

        std::vector<std::string> segments {};
        for(index_t idx {0U}; idx < normalized.length(); idx += columns)
        {
            segments.emplace_back(normalized.substr(idx, columns));
        }

        return segments;
    }

    auto cipher_text(const std::string &text) -> std::string
    {
        const std::string normalized {normalize_plain_text(text)};
        const index_t columns {size(text)};

        if(columns == 0U)
        {
            return std::string();
        }

        const index_t rows {(normalized.length() + columns - 1U) / columns};

        std::string cipher {};
        cipher.reserve(normalized.length());

        for(index_t c {0U}; c < columns; ++c)
        {
            for(index_t r {0U}; r < rows; ++r)
            {
                const index_t index_val {(r * columns) + c};
                if(index_val < normalized.length())
                {
                    cipher.push_back(normalized[index_val]);
                }
            }
        }

        return cipher;
    }

    auto normalize_cipher_text(const std::string &text) -> std::string
    {
        const std::string cipher {cipher_text(text)};

        const index_t columns {size(text)};
        if(columns == 0U)
        {
            return std::string();
        }
        const index_t rows {(cipher.length() + columns - 1U) / columns};

        std::string output {};
        for(index_t c {0U}; c < columns; ++c)
        {
            const index_t start {(c * rows)};
            index_t length {rows};

            if((start + length) > cipher.length())
            {
                length = cipher.length() - start;
            }

            std::string chunk {cipher.substr(start, length)};

            if(chunk.length() < rows)
            {
                chunk.append(rows - chunk.length(), ' ');
            }

            output += chunk;

            if((c + 1U) < columns)
            {
                output.push_back(' ');
            }
        }

        return output;
    }

    // ------------------------------------------------------------------
    // cipher façade implementation
    // ------------------------------------------------------------------

    cipher::cipher(const std::string &source) : m_source {source} {}

    auto cipher::size() const -> index_t
    {
        return crypto_square::size(m_source);
    }

    auto cipher::normalized_plain_text() const -> std::string
    {
        return crypto_square::normalize_plain_text(m_source);
    }

    auto cipher::plain_text_segments() const -> std::vector<std::string>
    {
        return crypto_square::plain_text_segments(m_source);
    }

    auto cipher::cipher_text() const -> std::string
    {
        return crypto_square::cipher_text(m_source);
    }

    auto cipher::normalized_cipher_text() const -> std::string
    {
        return crypto_square::normalize_cipher_text(m_source);
    }

}  // namespace crypto_square

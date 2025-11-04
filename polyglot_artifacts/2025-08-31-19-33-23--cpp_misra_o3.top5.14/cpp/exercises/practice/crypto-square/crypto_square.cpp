#include "crypto_square.h"
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

namespace crypto_square
{

namespace
{

auto normalize(const std::string& input) -> std::string
{
    std::string output {};
    output.reserve(input.size());

    for (char ch : input)
    {
        /* Promote to unsigned char before calling <cctype> functions */
        unsigned char const uch {static_cast<unsigned char>(ch)};

        if ((std::isalnum(uch) != 0))
        {
            char const lowercase {static_cast<char>(std::tolower(uch))};
            output.push_back(lowercase);
        }
        else
        {
            /* Non-alphanumeric characters are ignored */
        }
    }

    return output;
}

} // unnamed namespace

auto cipher_text(const std::string& input) -> std::string
{
    const std::string normalized {normalize(input)};
    const std::size_t len {normalized.length()};

    if (len == static_cast<std::size_t>(0U))
    {
        return std::string {};
    }

    const double root {std::sqrt(static_cast<double>(len))};

    std::size_t rows {static_cast<std::size_t>(std::floor(root))};
    std::size_t cols {static_cast<std::size_t>(std::ceil(root))};

    if ((rows * cols) < len)
    {
        ++rows;
    }

    std::vector<std::string> chunks {};
    chunks.reserve(cols);

    for (std::size_t col = static_cast<std::size_t>(0U); col < cols; ++col)
    {
        std::string chunk {};
        chunk.reserve(rows);

        for (std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row)
        {
            const std::size_t index {(row * cols) + col};

            if (index < len)
            {
                chunk.push_back(normalized[index]);
            }
            else
            {
                chunk.push_back(' ');
            }
        }
        chunks.push_back(chunk);
    }

    std::ostringstream oss {};

    for (std::size_t i = static_cast<std::size_t>(0U); i < chunks.size(); ++i)
    {
        if (i != static_cast<std::size_t>(0U))
        {
            oss << ' ';
        }
        oss << chunks[i];
    }

    return oss.str();
}

/* -------------------------------------------------------------------------- */
/*                         cipher class implementation                        */
/* -------------------------------------------------------------------------- */

cipher::cipher(const std::string& text)
    : normalized_{normalize(text)},
      rows_{static_cast<std::size_t>(0U)},
      cols_{static_cast<std::size_t>(0U)}
{
    const std::size_t len {normalized_.length()};

    if (len != static_cast<std::size_t>(0U))
    {
        const double root {std::sqrt(static_cast<double>(len))};

        rows_ = static_cast<std::size_t>(std::floor(root));
        cols_ = static_cast<std::size_t>(std::ceil(root));

        if ((rows_ * cols_) < len)
        {
            ++rows_;
        }
    }
}

auto cipher::normalize_plain_text() const -> std::string
{
    return normalized_;
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments {};

    if (cols_ == static_cast<std::size_t>(0U))
    {
        return segments;
    }

    for (std::size_t start {static_cast<std::size_t>(0U)};
         start < normalized_.length();
         start += cols_)
    {
        segments.push_back(normalized_.substr(start, cols_));
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    std::string output {};
    output.reserve(normalized_.length());

    if (cols_ == static_cast<std::size_t>(0U))
    {
        return output;
    }

    for (std::size_t col {static_cast<std::size_t>(0U)}; col < cols_; ++col)
    {
        for (std::size_t row {static_cast<std::size_t>(0U)}; row < rows_; ++row)
        {
            const std::size_t index {(row * cols_) + col};

            if (index < normalized_.length())
            {
                output.push_back(normalized_[index]);
            }
        }
    }

    return output;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    if (normalized_.empty())
    {
        return std::string {};
    }

    std::ostringstream oss {};

    for (std::size_t col {static_cast<std::size_t>(0U)}; col < cols_; ++col)
    {
        if (col != static_cast<std::size_t>(0U))
        {
            oss << ' ';
        }

        for (std::size_t row {static_cast<std::size_t>(0U)}; row < rows_; ++row)
        {
            const std::size_t index {(row * cols_) + col};

            if (index < normalized_.length())
            {
                oss << normalized_[index];
            }
            else
            {
                oss << ' ';
            }
        }
    }

    return oss.str();
}

} // namespace crypto_square

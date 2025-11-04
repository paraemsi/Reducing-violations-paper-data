#include "crypto_square.h"

#include <cstddef>
#include <cctype>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

namespace {
    std::string normalize(const std::string& in)
    {
        const std::locale loc {};
        std::string out {};
        out.reserve(in.size());
        for (std::string::const_reference ch : in) {
            if (std::isalnum(ch, loc)) {
                out.push_back(std::tolower(ch, loc));
            } else {
                // skip non-alphanumeric
            }
        }
        return out;
    }

    void compute_grid_dimensions(std::size_t len, std::size_t& rows, std::size_t& cols)
    {
        cols = static_cast<std::size_t>(0U);
        while (((cols * cols) < len)) {
            cols = (cols + static_cast<std::size_t>(1U));
        }

        if (cols == static_cast<std::size_t>(0U)) {
            rows = static_cast<std::size_t>(0U);
        } else {
            if ((((cols - static_cast<std::size_t>(1U)) * cols) >= len)) {
                rows = (cols - static_cast<std::size_t>(1U));
            } else {
                rows = cols;
            }
        }
    }
}  // namespace

cipher::cipher(const std::string& text) noexcept
    : input_(text)
{
}

std::string cipher::normalize_plain_text() const
{
    return normalize(input_);
}

std::vector<std::string> cipher::plain_text_segments() const
{
    const std::string norm { normalize(input_) };
    const std::size_t len { norm.size() };

    std::size_t rows { static_cast<std::size_t>(0U) };
    std::size_t cols { static_cast<std::size_t>(0U) };
    compute_grid_dimensions(len, rows, cols);

    std::vector<std::string> segments {};
    if (cols == static_cast<std::size_t>(0U)) {
        return segments;
    } else {
        segments.reserve(rows);
        for (std::size_t r { static_cast<std::size_t>(0U) }; r < rows; r = (r + static_cast<std::size_t>(1U))) {
            const std::size_t start { (r * cols) };
            const std::size_t remaining { (len - ((start < len) ? start : len)) };
            const std::size_t count { (remaining < cols) ? remaining : cols };
            segments.push_back(norm.substr(start, count));
        }
        return segments;
    }
}

std::string cipher::ciphertext() const
{
    const std::string norm { normalize(input_) };
    const std::size_t len { norm.size() };

    std::size_t rows { static_cast<std::size_t>(0U) };
    std::size_t cols { static_cast<std::size_t>(0U) };
    compute_grid_dimensions(len, rows, cols);

    std::string out {};
    out.reserve(len);

    for (std::size_t c { static_cast<std::size_t>(0U) }; c < cols; c = (c + static_cast<std::size_t>(1U))) {
        for (std::size_t r { static_cast<std::size_t>(0U) }; r < rows; r = (r + static_cast<std::size_t>(1U))) {
            const std::size_t idx { ((r * cols) + c) };
            if (idx < len) {
                out.push_back(norm[idx]);
            } else {
                // skip padding
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const
{
    const std::string norm { normalize(input_) };
    const std::size_t len { norm.size() };

    std::size_t rows { static_cast<std::size_t>(0U) };
    std::size_t cols { static_cast<std::size_t>(0U) };
    compute_grid_dimensions(len, rows, cols);

    if (cols == static_cast<std::size_t>(0U)) {
        return std::string {};
    } else {
        std::string out {};
        // Each chunk will have length 'rows', and there are 'cols' chunks plus (cols-1) spaces.
        out.reserve((rows * cols) + (cols - static_cast<std::size_t>(1U)));

        for (std::size_t c { static_cast<std::size_t>(0U) }; c < cols; c = (c + static_cast<std::size_t>(1U))) {
            if (c != static_cast<std::size_t>(0U)) {
                out.push_back(' ');
            } else {
                // first chunk: no leading space
            }
            for (std::size_t r { static_cast<std::size_t>(0U) }; r < rows; r = (r + static_cast<std::size_t>(1U))) {
                const std::size_t idx { ((r * cols) + c) };
                if (idx < len) {
                    out.push_back(norm[idx]);
                } else {
                    out.push_back(' ');
                }
            }
        }
        return out;
    }
}

}  // namespace crypto_square

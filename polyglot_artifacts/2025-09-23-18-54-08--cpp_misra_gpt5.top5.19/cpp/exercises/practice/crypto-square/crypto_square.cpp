#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <locale>
#include <string>
#include <vector>

namespace
{
    // Compute rows (r) and columns (c) for the rectangle subject to:
    // r * c >= n, c >= r, and c - r <= 1
    static void compute_rectangle(std::size_t n, std::size_t& rows, std::size_t& cols)
    {
        cols = 0U;
        while (((cols * cols) < n)) {
            cols += 1U;
        }

        if (cols == 0U) {
            rows = 0U;
        } else {
            rows = ((n + (cols - 1U)) / cols);
        }
    }
}  // unnamed namespace

namespace crypto_square {

cipher::cipher(const std::string& text) : normalized_()
{
    const std::locale loc{};
    normalized_.reserve(text.size());
    for (const char ch : text) {
        if (std::isalnum(ch, loc)) {
            normalized_.push_back(std::tolower(ch, loc));
        } else {
            // ignore non-alphanumeric
        }
    }
}

std::string cipher::normalize_plain_text() const
{
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const
{
    std::vector<std::string> segments{};
    const std::size_t n = normalized_.size();

    std::size_t rows = 0U;
    std::size_t cols = 0U;
    compute_rectangle(n, rows, cols);

    if (n == 0U) {
        return segments;
    }

    segments.reserve(rows);
    for (std::size_t r = 0U; r < rows; ++r) {
        const std::size_t start = (r * cols);
        const std::size_t len = std::min(cols, (n - start));
        segments.emplace_back(normalized_.substr(start, len));
    }

    return segments;
}

std::string cipher::cipher_text() const
{
    const std::size_t n = normalized_.size();

    std::size_t rows = 0U;
    std::size_t cols = 0U;
    compute_rectangle(n, rows, cols);

    std::string out{};
    out.reserve(n);

    for (std::size_t c = 0U; c < cols; ++c) {
        for (std::size_t r = 0U; r < rows; ++r) {
            const std::size_t idx = ((r * cols) + c);
            if (idx < n) {
                out.push_back(normalized_[idx]);
            } else {
                // beyond end; skip
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const
{
    const std::size_t n = normalized_.size();

    std::size_t rows = 0U;
    std::size_t cols = 0U;
    compute_rectangle(n, rows, cols);

    if (n == 0U) {
        return std::string{};
    }

    // c chunks of length r, separated by spaces; pad trailing spaces in last (r*c - n) chunks
    std::string out{};
    out.reserve(((cols * rows) + (cols - 1U)));

    for (std::size_t c = 0U; c < cols; ++c) {
        if (c > 0U) {
            out.push_back(' ');
        } else {
            // first chunk - no leading space
        }

        for (std::size_t r = 0U; r < rows; ++r) {
            const std::size_t idx = ((r * cols) + c);
            if (idx < n) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }

    return out;
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <cctype>
#include <cstdint>
#include <string>
#include <vector>
#include <utility>

namespace crypto_square {

namespace {
    // Normalize text: keep only alphanumeric, downcase letters.
    std::string normalize(const std::string& text)
    {
        std::string out{};
        out.reserve(text.size());
        for (char ch : text) {
            const int ich = std::char_traits<char>::to_int_type(ch);
            if (std::isalnum(ich) != 0) {
                const int lower = std::tolower(ich);
                const char cl = std::char_traits<char>::to_char_type(lower);
                out.push_back(cl);
            } else {
                // skip non-alnum
            }
        }
        return out;
    }

    // Compute columns and rows satisfying:
    // r * c >= n, c >= r, c - r <= 1
    // Strategy: smallest c with c*c >= n, then r = ceil(n / c)
    std::pair<std::size_t, std::size_t> compute_dims(std::size_t n)
    {
        if (n == 0U) {
            return std::make_pair(0U, 0U);
        }

        std::size_t c = 1U;
        while (((c * c) < n)) {
            ++c;
        }
        const std::size_t r = ((n + (c - 1U)) / c);
        return std::make_pair(r, c);
    }
} // namespace

cipher::cipher(const std::string& text)
{
    normalized_ = normalize(text);
    const std::size_t n = normalized_.size();
    const auto dims = compute_dims(n);
    rows_ = dims.first;
    cols_ = dims.second;
}

std::string cipher::normalize_plain_text() const
{
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const
{
    std::vector<std::string> segments{};
    if (normalized_.empty()) {
        return segments;
    }

    segments.reserve(((normalized_.size() + (cols_ - 1U)) / cols_));
    for (std::size_t i = 0U; i < normalized_.size(); i += cols_) {
        const std::size_t remaining = normalized_.size() - i;
        const std::size_t take = (remaining < cols_) ? remaining : cols_;
        segments.emplace_back(normalized_.substr(i, take));
    }
    return segments;
}

std::string cipher::ciphertext() const
{
    if (normalized_.empty()) {
        return std::string{};
    }

    std::string out{};
    out.reserve(normalized_.size());

    const std::size_t n = normalized_.size();
    for (std::size_t col = 0U; col < cols_; ++col) {
        for (std::size_t row = 0U; row < rows_; ++row) {
            const std::size_t pos = ((row * cols_) + col);
            if ((pos < n)) {
                out.push_back(normalized_[pos]);
            } else {
                // no padding in raw ciphertext
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const
{
    if (normalized_.empty()) {
        return std::string{};
    }

    const std::size_t n = normalized_.size();
    std::string out{};
    // Each of the c chunks has length r, plus (c - 1) spaces between chunks.
    out.reserve((rows_ * cols_) + (cols_ - 1U));

    for (std::size_t col = 0U; col < cols_; ++col) {
        for (std::size_t row = 0U; row < rows_; ++row) {
            const std::size_t pos = ((row * cols_) + col);
            if ((pos < n)) {
                out.push_back(normalized_[pos]);
            } else {
                out.push_back(' ');
            }
        }
        if ((col + 1U) < cols_) {
            out.push_back(' ');
        }
    }
    return out;
}

}  // namespace crypto_square

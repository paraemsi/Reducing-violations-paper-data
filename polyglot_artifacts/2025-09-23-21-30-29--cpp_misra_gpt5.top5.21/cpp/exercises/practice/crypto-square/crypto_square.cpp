#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

namespace crypto_square {

namespace {
std::string normalize_text(const std::string& text)
{
    std::string out{};
    out.reserve(text.size());
    for (char ch : text) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            const char lowered = std::char_traits<char>::to_char_type(std::tolower(static_cast<unsigned char>(ch)));
            out.push_back(lowered);
        } else {
            // skip non-alphanumeric
        }
    }
    return out;
}

void compute_dimensions(std::size_t len, std::size_t& rows, std::size_t& cols)
{
    if (len == 0U) {
        rows = 0U;
        cols = 0U;
        return;
    }

    cols = 0U;
    while (((cols * cols) < len)) {
        ++cols;
    }
    rows = (len + (cols - 1U)) / cols;
}
}  // namespace

cipher::cipher(const std::string& text)
    : normalized_{normalize_text(text)}
    , rows_{0U}
    , cols_{0U}
{
    compute_dimensions(normalized_.size(), rows_, cols_);
}

std::string cipher::normalized_plain_text() const
{
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const
{
    std::vector<std::string> segments{};
    const std::size_t len = normalized_.size();

    if (len == 0U) {
        return segments;
    }

    segments.reserve(rows_);
    for (std::size_t r = 0U; r < rows_; ++r) {
        const std::size_t start = (r * cols_);
        const std::size_t remaining = (len - start);
        const std::size_t take = (remaining < cols_) ? remaining : cols_;
        segments.emplace_back(normalized_.substr(start, take));
    }

    return segments;
}

std::string cipher::cipher_text() const
{
    const std::size_t len = normalized_.size();
    if (len == 0U) {
        return std::string{};
    }

    std::string out{};
    out.reserve(len);

    for (std::size_t c = 0U; c < cols_; ++c) {
        for (std::size_t r = 0U; r < rows_; ++r) {
            const std::size_t idx = (r * cols_) + c;
            if (idx < len) {
                out.push_back(normalized_[idx]);
            } else {
                // skip padding positions for compact ciphertext
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const
{
    const std::size_t len = normalized_.size();
    if (len == 0U) {
        return std::string{};
    }

    std::string out{};
    // c chunks, each of length r, plus (c - 1) spaces
    out.reserve((cols_ * rows_) + (cols_ - 1U));

    for (std::size_t c = 0U; c < cols_; ++c) {
        for (std::size_t r = 0U; r < rows_; ++r) {
            const std::size_t idx = (r * cols_) + c;
            if (idx < len) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
        if ((c + 1U) < cols_) {
            out.push_back(' ');
        }
    }

    return out;
}

}  // namespace crypto_square

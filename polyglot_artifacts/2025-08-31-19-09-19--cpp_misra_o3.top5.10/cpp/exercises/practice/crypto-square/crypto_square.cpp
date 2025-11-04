#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>
#include <vector>

namespace {

/* Helper : return true for ASCII letter or decimal digit (locale-independent) */
auto is_alpha_numeric(char ch) noexcept -> bool
{
    /*  Using the <cctype> classification function avoids direct
     *  numerical comparisons on the character value, thus respecting
     *  the MISRA guideline that forbids relational use of character
     *  operands.
     */
    return (std::isalnum(static_cast<unsigned char>(ch)) != 0);
}

/* Helper : lower-case ASCII letter, leave others unchanged (digits) */
auto to_lower_ascii(char ch) noexcept -> char
{
    /*  std::tolower returns an int; cast back to char after the call.
     *  The classification function operates on unsigned char values,
     *  preventing any undefined behaviour for negative plain-char.
     */
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

/* Helper : normalize input (filter + lower-case) */
auto normalize(const std::string& text) -> std::string
{
    std::string out {};
    out.reserve(text.size());

    for (char ch : text) {
        if (is_alpha_numeric(ch)) {
            out.push_back(to_lower_ascii(ch));
        }
    }
    return out;
}

/* Helper : decide rectangle dimensions (rows r, columns c) */
auto choose_rectangle(std::uint32_t n) noexcept -> std::pair<std::uint32_t, std::uint32_t>
{
    if (n == static_cast<std::uint32_t>(0U)) {
        return {0U, 0U};
    }

    const double n_d {static_cast<double>(n)};
    std::uint32_t c {static_cast<std::uint32_t>(std::ceil(std::sqrt(n_d)))};
    std::uint32_t r {static_cast<std::uint32_t>(std::floor(std::sqrt(n_d)))};

    if ((r * c) < n) {
        ++r;
    }
    /* Post-condition guarantees: c >= r, c - r <= 1 */
    if (r > c) {
        std::swap(r, c);
    }
    return {r, c};
}

}  // anonymous namespace

namespace crypto_square {

/* ==== cipher class implementation ====================================== */
cipher::cipher(const std::string& text)
    : normalized_{normalize(text)}
{
    const auto dims {choose_rectangle(static_cast<std::uint32_t>(normalized_.size()))};
    rows_ = dims.first;
    cols_ = dims.second;
}

auto cipher::normalize_plain_text() const -> std::string
{
    return normalized_;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments {};
    if (cols_ == static_cast<std::uint32_t>(0U)) {
        return segments;
    }

    for (std::uint32_t start {0U}; start < static_cast<std::uint32_t>(normalized_.size()); start += cols_) {
        segments.emplace_back(normalized_.substr(start, cols_));
    }
    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    std::string out {};
    out.reserve(normalized_.size());

    for (std::uint32_t col {0U}; col < cols_; ++col) {
        for (std::uint32_t row {0U}; row < rows_; ++row) {
            const std::uint32_t index {(row * cols_) + col};
            if (index < static_cast<std::uint32_t>(normalized_.size())) {
                out.push_back(normalized_[index]);
            }
        }
    }
    return out;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    const std::string raw_cipher {cipher_text()};

    std::ostringstream oss {};
    std::uint32_t pos {0U};
    for (std::uint32_t col {0U}; col < cols_; ++col) {
        if (col != static_cast<std::uint32_t>(0U)) {
            oss << ' ';
        }

        std::string chunk {raw_cipher.substr(pos, rows_)};
        pos += rows_;

        if (chunk.size() < rows_) {
            chunk.append(rows_ - static_cast<std::uint32_t>(chunk.size()), ' ');
        }
        oss << chunk;
    }
    return oss.str();
}
/* ======================================================================= */

auto cipher_text(const std::string& input) -> std::string
{
    const std::string normalised {normalize(input)};
    const std::uint32_t n {static_cast<std::uint32_t>(normalised.size())};

    const auto [r, c] = choose_rectangle(n);

    if (n == static_cast<std::uint32_t>(0U)) {
        return std::string {};
    }

    /* Build encoded columns */
    std::vector<std::string> columns;
    columns.reserve(c);

    for (std::uint32_t col = 0U; col < c; ++col) {
        std::string chunk {};
        chunk.reserve(r);

        for (std::uint32_t row = 0U; row < r; ++row) {
            const std::uint32_t index {(row * c) + col};
            if (index < n) {
                chunk.push_back(normalised[index]);
            } else {
                chunk.push_back(' ');
            }
        }
        columns.push_back(chunk);
    }

    /* Join with single spaces */
    std::ostringstream oss;
    for (std::uint32_t i = 0U; i < c; ++i) {
        if (i != static_cast<std::uint32_t>(0U)) {
            oss << ' ';
        }
        oss << columns[i];
    }
    return oss.str();
}

}  // namespace crypto_square

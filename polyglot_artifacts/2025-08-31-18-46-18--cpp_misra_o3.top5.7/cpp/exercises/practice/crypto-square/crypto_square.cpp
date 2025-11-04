#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace {

/* Return a new string containing only the lower-cased alpha-numeric
 * characters of the input.
 */
auto normalize(std::string const & in) -> std::string
{
    std::string out {};
    out.reserve(in.size());

    for(char const ch : in) {
        if(std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    return out;
}

/* Compute (rows, cols) according to the specification. */
auto rectangle_dimensions(std::size_t len) -> std::pair<std::size_t, std::size_t>
{
    if(len == static_cast<std::size_t>(0)) {
        return {0U, 0U};
    }

    double const root_d {std::sqrt(static_cast<double>(len))};
    std::size_t const root {static_cast<std::size_t>(root_d)};

    std::size_t rows {root};
    std::size_t cols {root};

    if((rows * cols) < len) {
        cols = root + 1U;
    }
    if((rows * cols) < len) {
        rows = root + 1U;
    }

    return {rows, cols};
}

} // namespace

namespace crypto_square {

cipher::cipher(std::string const & text)
    : m_normalized {normalize(text)}
{
    auto const dims {rectangle_dimensions(m_normalized.size())};
    m_rows = dims.first;
    m_cols = dims.second;
}

auto cipher::normalize_plain_text() const -> std::string
{
    return m_normalized;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    std::vector<std::string> segments {};
    segments.reserve(m_rows);

    for(std::size_t r {0U}; r < m_rows; ++r) {
        std::size_t const start {(r * m_cols)};
        if(start >= m_normalized.size()) {
            segments.emplace_back("");
        } else {
            std::size_t const remaining {m_normalized.size() - start};
            std::size_t const len {std::min(m_cols, remaining)};
            segments.emplace_back(m_normalized.substr(start, len));
        }
    }

    return segments;
}

auto cipher::cipher_text() const -> std::string
{
    if(m_normalized.empty()) {
        return std::string {};
    }

    std::string encoded {};
    encoded.reserve(m_normalized.size());

    for(std::size_t c {0U}; c < m_cols; ++c) {
        for(std::size_t r {0U}; r < m_rows; ++r) {
            std::size_t const idx {(r * m_cols) + c};
            if(idx < m_normalized.size()) {
                encoded.push_back(m_normalized[idx]);
            }
        }
    }

    return encoded;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    if(m_normalized.empty()) {
        return std::string {};
    }

    std::string encoded {};
    encoded.reserve(m_normalized.size() + m_cols - 1U);

    for(std::size_t c {0U}; c < m_cols; ++c) {
        if(c != static_cast<std::size_t>(0)) {
            encoded.push_back(' ');
        }

        for(std::size_t r {0U}; r < m_rows; ++r) {
            std::size_t const idx {(r * m_cols) + c};
            if(idx < m_normalized.size()) {
                encoded.push_back(m_normalized[idx]);
            } else {
                encoded.push_back(' ');
            }
        }
    }

    return encoded;
}

}  // namespace crypto_square

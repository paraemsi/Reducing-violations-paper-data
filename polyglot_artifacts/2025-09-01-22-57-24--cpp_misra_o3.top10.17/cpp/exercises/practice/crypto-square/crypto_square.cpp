#include "crypto_square.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <locale>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

/* Determine the rectangle dimensions (rows r, columns c). */
auto dimensions(std::uint32_t len) -> std::pair<std::uint32_t, std::uint32_t>
{
    if (len == 0U)
    {
        return {0U, 0U};
    }

    const double root{std::sqrt(static_cast<double>(len))};
    std::uint32_t c{static_cast<std::uint32_t>(std::ceil(root))};
    std::uint32_t r{c};

    if (((c - 1U) * c) >= len)
    {
        r = c - 1U;
    }

    return {r, c};
}

} // unnamed namespace

namespace crypto_square {

auto normalize_plain_text(const std::string& input) -> std::string
{
    std::string output{};
    const std::locale loc{};

    output.reserve(input.size());

    for (char ch : input)
    {
        if (std::isalnum(ch, loc) != 0)
        {
            output.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    return output;
}

auto plain_text_segments(const std::string& input) -> std::vector<std::string>
{
    const std::string normalized{normalize_plain_text(input)};
    const std::uint32_t len{static_cast<std::uint32_t>(normalized.size())};

    const auto [r, c] = dimensions(len);

    std::vector<std::string> segments{};
    segments.reserve(r);

    for (std::uint32_t index{0U}; index < len; index += c)
    {
        const std::uint32_t remaining{len - index};
        const std::uint32_t take{(remaining < c) ? remaining : c};

        std::string segment{normalized.substr(index, take)};
        if (segment.size() < c)
        {
            segment.append(c - segment.size(), ' ');
        }

        segments.push_back(segment);
    }

    /* In rare case where rows exceed produced segments (when len is multiple of c)
       pad with fully blank rows to reach r rows. */
    while (segments.size() < static_cast<std::size_t>(r))
    {
        segments.emplace_back(c, ' ');
    }

    return segments;
}

auto cipher_text(const std::string& input) -> std::string
{
    const std::vector<std::string> rows{plain_text_segments(input)};
    if (rows.empty())
    {
        return {};
    }

    const std::uint32_t r{static_cast<std::uint32_t>(rows.size())};
    const std::uint32_t c{static_cast<std::uint32_t>(rows.front().size())};

    std::string result{};
    result.reserve(r * c);

    for (std::uint32_t col{0U}; col < c; ++col)
    {
        for (std::uint32_t row{0U}; row < r; ++row)
        {
            const char ch{rows[row][col]};
            if (ch != ' ')
            {
                result.push_back(ch);
            }
        }
    }

    return result;
}

auto normalized_cipher_text(const std::string& input) -> std::string
{
    const std::vector<std::string> rows{plain_text_segments(input)};
    if (rows.empty())
    {
        return {};
    }

    const std::uint32_t r{static_cast<std::uint32_t>(rows.size())};
    const std::uint32_t c{static_cast<std::uint32_t>(rows.front().size())};

    std::ostringstream oss{};

    for (std::uint32_t col{0U}; col < c; ++col)
    {
        if (col != 0U)
        {
            oss << ' ';
        }

        for (std::uint32_t row{0U}; row < r; ++row)
        {
            oss << rows[row][col];
        }
    }

    return oss.str();
}

// close helper-function section and provide class implementation
}  // namespace crypto_square

namespace crypto_square {

cipher::cipher(const std::string& text) : m_text{text} { }

auto cipher::normalize_plain_text() const -> std::string
{
    return crypto_square::normalize_plain_text(m_text);
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    return crypto_square::plain_text_segments(m_text);
}

auto cipher::cipher_text() const -> std::string
{
    return crypto_square::cipher_text(m_text);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return crypto_square::normalized_cipher_text(m_text);
}

}  // namespace crypto_square

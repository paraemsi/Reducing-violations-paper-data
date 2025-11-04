#include "crypto_square.h"

#include <cmath>
#include <locale>
#include <utility>     // for std::pair

namespace crypto_square {

namespace {
/* Helper to compute rows and columns that satisfy:
 *  - r * c >= len
 *  - c >= r
 *  - c - r <= 1
 */
[[nodiscard]] std::pair<std::size_t, std::size_t> compute_rectangle(std::size_t len)
{
    const double root { std::sqrt(static_cast<double>(len)) };

    std::size_t r { static_cast<std::size_t>(std::floor(root)) };
    std::size_t c { static_cast<std::size_t>(std::ceil(root)) };

    if ((r * c) < len) {
        ++r;
    }

    return { r, c };
}
} // namespace

cipher::cipher(const std::string& text) : m_normalized { normalize(text) }
{
}

std::string cipher::normalize_plain_text() const
{
    return m_normalized;
}

std::vector<std::string> cipher::plaintext_segments() const
{
    const std::size_t len { m_normalized.length() };
    const auto [r, c] = compute_rectangle(len);

    std::vector<std::string> segments;
    segments.reserve(r);

    for (std::size_t row { 0U }; row < r; ++row) {
        const std::size_t start { row * c };
        if (start >= len) {
            segments.emplace_back("");
        } else {
            segments.emplace_back(m_normalized.substr(start, c));
        }
    }

    return segments;
}

std::string cipher::cipher_text() const
{
    const std::size_t len { m_normalized.length() };
    const auto [r, c] = compute_rectangle(len);

    std::string result;
    result.reserve(len);

    for (std::size_t col { 0U }; col < c; ++col) {
        for (std::size_t row { 0U }; row < r; ++row) {
            const std::size_t idx { (row * c) + col };
            if (idx < len) {
                result.push_back(m_normalized[idx]);
            }
        }
    }

    return result;
}

std::string cipher::normalized_cipher_text() const
{
    const std::size_t len { m_normalized.length() };
    const auto [r, c] = compute_rectangle(len);

    std::string result;
    result.reserve((r + 1U) * c);    // each chunk plus a space

    for (std::size_t col { 0U }; col < c; ++col) {
        for (std::size_t row { 0U }; row < r; ++row) {
            const std::size_t idx { (row * c) + col };
            if ((idx < len)) {
                result.push_back(m_normalized[idx]);
            } else {
                result.push_back(' ');
            }
        }

        if ((col + 1U) < c) {
            result.push_back(' ');
        }
    }

    return result;
}

std::string cipher::normalize(const std::string& text)
{
    std::locale loc {};
    std::string normalized;
    normalized.reserve(text.length());

    for (char ch : text) {
        if (std::isalnum(ch, loc) != 0) {
            normalized.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    return normalized;
}

}  // namespace crypto_square

#include "crypto_square.h"

#include <locale>
#include <vector>

namespace crypto_square {

auto cipher_text(std::string_view input) -> std::string
{
    /* ---------------------------------------------------------------------
     * 1. Normalise the input: keep only alpha-numeric characters and lower-case
     * ------------------------------------------------------------------- */
    const std::locale loc {};
    std::string normalised {};
    normalised.reserve(input.size());

    for (char ch : input) {
        if (std::isalnum(ch, loc) != 0) {
            normalised.push_back(static_cast<char>(std::tolower(ch, loc)));
        }
    }

    const std::size_t len { normalised.length() };
    if (len == static_cast<std::size_t>(0U)) {
        return std::string {};
    }

    /* ---------------------------------------------------------------------
     * 2. Determine rectangle dimensions (rows r, columns c)
     *    Compute using integer arithmetic to avoid narrowing conversions.
     * ------------------------------------------------------------------- */
    std::size_t c { static_cast<std::size_t>(0U) };
    while ((c * c) < len) {
        ++c;
    }

    const std::size_t r {
        (len + c - static_cast<std::size_t>(1U)) / c
    };

    /* ---------------------------------------------------------------------
     * 3. Break the text into rows of length c
     * ------------------------------------------------------------------- */
    std::vector<std::string> rows {};
    rows.reserve(r);
    for (std::size_t row { static_cast<std::size_t>(0U) }; row < r; ++row) {
        const std::size_t start { row * c };
        std::string part {};
        if (start < len) {
            const std::size_t end {
                (start + c <= len) ? (start + c) : len
            };
            part = normalised.substr(start, end - start);
        }
        rows.emplace_back(std::move(part));
    }

    /* ---------------------------------------------------------------------
     * 4. Read down the columns and build the output string
     * ------------------------------------------------------------------- */
    std::string output {};
    for (std::size_t col { static_cast<std::size_t>(0U) }; col < c; ++col) {
        if (col > static_cast<std::size_t>(0U)) {
            output.push_back(' ');
        }

        for (std::size_t row { static_cast<std::size_t>(0U) }; row < r; ++row) {
            if (col < rows[row].length()) {
                output.push_back(rows[row][col]);
            } else {
                output.push_back(' ');
            }
        }
    }

    return output;
}

/* -------------------------------------------------------------------------
 *  Class cipher : implementation
 * --------------------------------------------------------------------- */
namespace
{
    /* helper – reuse the same normalisation logic everywhere */
    auto normalise(std::string_view input) -> std::string
    {
        const std::locale loc {};
        std::string result {};
        result.reserve(input.size());

        for (char ch : input) {
            if (std::isalnum(ch, loc) != 0) {
                result.push_back(static_cast<char>(std::tolower(ch, loc)));
            }
        }

        return result;
    }
}  // unnamed namespace


/* -------------------------------------------------------------------------
 *  cipher member definitions
 * --------------------------------------------------------------------- */
cipher::cipher(std::string_view text) :
    m_plain(text),
    m_normalised(normalise(text))
{
    const std::size_t len { m_normalised.length() };

    if (len == static_cast<std::size_t>(0U)) {
        m_cols = static_cast<std::size_t>(0U);
        m_rows = static_cast<std::size_t>(0U);
        return;
    }

    while ((m_cols * m_cols) < len) {
        ++m_cols;
    }

    m_rows = (len + m_cols - static_cast<std::size_t>(1U)) / m_cols;

    calculate_segments();
}

void cipher::calculate_segments()
{
    m_segments.clear();
    m_segments.reserve(m_rows);

    const std::size_t len { m_normalised.length() };

    for (std::size_t row { static_cast<std::size_t>(0U) }; row < m_rows; ++row) {
        const std::size_t start { row * m_cols };
        if (start >= len) {
            m_segments.emplace_back(std::string {});
            continue;
        }

        const std::size_t end {
            (start + m_cols <= len) ? (start + m_cols) : len
        };
        m_segments.emplace_back(m_normalised.substr(start, end - start));
    }
}

auto cipher::size() const -> std::size_t
{
    return m_cols;
}

auto cipher::normalize_plain_text() const -> std::string
{
    return m_normalised;
}

auto cipher::normalize_plaintext() const -> std::string
{
    return normalize_plain_text();
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    return m_segments;
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    return plaintext_segments();
}

auto cipher::cipher_text() const -> std::string
{
    std::string output {};

    for (std::size_t col { static_cast<std::size_t>(0U) }; col < m_cols; ++col) {
        for (std::size_t row { static_cast<std::size_t>(0U) }; row < m_rows; ++row) {
            if (col < m_segments[row].length()) {
                output.push_back(m_segments[row][col]);
            }
        }
    }

    return output;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    std::string output {};

    for (std::size_t col { static_cast<std::size_t>(0U) }; col < m_cols; ++col) {
        if (col > static_cast<std::size_t>(0U)) {
            output.push_back(' ');
        }

        for (std::size_t row { static_cast<std::size_t>(0U) }; row < m_rows; ++row) {
            if (col < m_segments[row].length()) {
                output.push_back(m_segments[row][col]);
            } else {
                output.push_back(' ');
            }
        }
    }

    return output;
}

} // namespace crypto_square

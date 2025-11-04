#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text)
    : m_normalized()
    , m_rows(0U)
    , m_cols(0U) {
    m_normalized.reserve(text.size());

    for (const char ch : text) {
        const std::char_traits<char>::int_type cval = std::char_traits<char>::to_int_type(ch);
        if ((std::isalnum(cval)) != 0) {
            const std::char_traits<char>::int_type lower_i = std::tolower(cval);
            const char lower = std::char_traits<char>::to_char_type(lower_i);
            m_normalized.push_back(lower);
        }
    }

    const std::size_t len = m_normalized.size();
    if ((len == 0U)) {
        m_rows = 0U;
        m_cols = 0U;
        return;
    }

    std::size_t c = 0U;
    while (((c * c) < len)) {
        c += 1U;
    }

    std::size_t r = c;
    if ((((c - 1U) * c) >= len)) {
        r = (c - 1U);
    }

    m_rows = r;
    m_cols = c;
}

std::string cipher::normalize_plain_text() const {
    return m_normalized;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments{};
    const std::size_t len = m_normalized.size();

    std::size_t i = 0U;
    while ((i < len)) {
        const std::size_t remaining = (len - i);
        const std::size_t take = ((remaining < m_cols) ? remaining : m_cols);
        segments.emplace_back(m_normalized.substr(i, take));
        i += take;
    }

    return segments;
}

std::string cipher::cipher_text() const {
    std::string out{};
    const std::size_t len = m_normalized.size();
    out.reserve(len);

    if ((len == 0U)) {
        return out;
    }

    for (std::size_t col = 0U; (col < m_cols); col += 1U) {
        for (std::size_t row = 0U; (row < m_rows); row += 1U) {
            const std::size_t idx = ((row * m_cols) + col);
            if ((idx < len)) {
                out.push_back(m_normalized[idx]);
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const {
    std::string out{};
    const std::size_t len = m_normalized.size();

    if ((len == 0U)) {
        return out;
    }

    for (std::size_t col = 0U; (col < m_cols); col += 1U) {
        if ((col != 0U)) {
            out.push_back(' ');
        }
        for (std::size_t row = 0U; (row < m_rows); row += 1U) {
            const std::size_t idx = ((row * m_cols) + col);
            if ((idx < len)) {
                out.push_back(m_normalized[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }

    return out;
}

}  // namespace crypto_square

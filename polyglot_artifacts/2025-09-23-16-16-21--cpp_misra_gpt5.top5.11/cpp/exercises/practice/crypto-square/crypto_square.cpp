#include "crypto_square.h"

#include <cstddef>
#include <string>
#include <vector>
#include <locale>

namespace crypto_square {

cipher::cipher(const std::string& text)
    : m_normalized() {
    const std::locale loc{};
    m_normalized.reserve(text.size());
    for (const char ch : text) {
        if (std::isalnum(ch, loc)) {
            m_normalized.push_back(std::tolower(ch, loc));
        } else {
            // skip non-alphanumeric
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return m_normalized;
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::size_t len = m_normalized.size();
    std::vector<std::string> segments{};
    if ((len == 0U)) {
        return segments;
    }

    // Compute columns (c) as the smallest c with c*c >= len, then rows (r) = ceil(len / c)
    std::size_t c = 1U;
    while (((c * c) < len)) {
        ++c;
    }
    const std::size_t r = ((len + c) - 1U) / c;

    segments.reserve(r);
    for (std::size_t i = 0U; i < len; i += c) {
        const std::size_t remaining = len - i;
        const std::size_t take = (remaining < c) ? remaining : c;
        segments.emplace_back(m_normalized.substr(i, take));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const std::size_t len = m_normalized.size();
    if ((len == 0U)) {
        return std::string{};
    }

    // Recompute dimensions to avoid duplication issues
    std::size_t c = 1U;
    while (((c * c) < len)) {
        ++c;
    }
    const std::size_t r = ((len + c) - 1U) / c;

    const std::vector<std::string> rows = plain_text_segments();
    std::string out{};
    out.reserve(len);

    for (std::size_t col = 0U; col < c; ++col) {
        for (std::size_t row = 0U; row < r; ++row) {
            if ((row < rows.size())) {
                if ((col < rows[row].size())) {
                    out.push_back(rows[row][col]);
                } else {
                    // no character in this row/column position
                }
            } else {
                // extra safety; should not happen
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t len = m_normalized.size();
    if ((len == 0U)) {
        return std::string{};
    }

    // Compute dimensions
    std::size_t c = 1U;
    while (((c * c) < len)) {
        ++c;
    }
    const std::size_t r = ((len + c) - 1U) / c;

    const std::vector<std::string> rows = plain_text_segments();

    std::string out{};
    // Each chunk has length r, and there are c chunks, plus (c - 1) spaces between them
    out.reserve((r * c) + (c - 1U));

    for (std::size_t col = 0U; col < c; ++col) {
        if ((col != 0U)) {
            out.push_back(' ');
        }
        std::string chunk{};
        chunk.reserve(r);
        for (std::size_t row = 0U; row < r; ++row) {
            if ((row < rows.size()) && (col < rows[row].size())) {
                chunk.push_back(rows[row][col]);
            } else {
                // Pad with a single space when this cell is missing
                chunk.push_back(' ');
            }
        }
        out += chunk;
    }

    return out;
}

}  // namespace crypto_square

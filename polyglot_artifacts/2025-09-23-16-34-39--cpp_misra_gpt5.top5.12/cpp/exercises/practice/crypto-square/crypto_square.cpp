#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text)
    : m_normalized(normalize(text))
    , m_rows(0U)
    , m_cols(0U) {
    compute_dimensions(m_normalized.size(), m_rows, m_cols);
}

std::string cipher::normalize(const std::string& text) {
    std::string out;
    out.reserve(text.size());

    for (const char ch : text) {
        const int ich = std::char_traits<char>::to_int_type(ch);
        if ((std::isalnum(ich)) != 0) {
            if ((std::isalpha(ich)) != 0) {
                const int lower = std::tolower(ich);
                out.push_back(std::char_traits<char>::to_char_type(lower));
            } else {
                out.push_back(ch);
            }
        } else {
            // skip non-alphanumeric
        }
    }

    return out;
}

void cipher::compute_dimensions(std::size_t length, std::size_t& rows_out, std::size_t& cols_out) {
    std::size_t c = 0U;
    while (((c * c) < length)) {
        c = (c + 1U);
    }

    std::size_t r = c;
    if ((r != 0U) && (((r - 1U) * c) >= length)) {
        r = (r - 1U);
    }

    rows_out = r;
    cols_out = c;
}

std::string cipher::normalize_plain_text() const {
    return m_normalized;
}

std::vector<std::string> cipher::plaintext_segments() const {
    std::vector<std::string> segments;
    if (m_normalized.empty()) {
        return segments;
    }

    segments.reserve(m_rows);

    for (std::size_t row = 0U; (row < m_rows); row = (row + 1U)) {
        const std::size_t start = (row * m_cols);
        const std::size_t available = (m_normalized.size() > start) ? (m_normalized.size() - start) : 0U;
        const std::size_t seg_len = (available < m_cols) ? available : m_cols;
        segments.push_back(m_normalized.substr(start, seg_len));
    }

    return segments;
}

std::string cipher_text_from_normalized(const std::string& normalized, const std::size_t rows, const std::size_t cols) {
    if (normalized.empty()) {
        return std::string();
    }

    std::string result;
    result.reserve(normalized.size());

    for (std::size_t col = 0U; (col < cols); col = (col + 1U)) {
        for (std::size_t row = 0U; (row < rows); row = (row + 1U)) {
            const std::size_t idx = ((row * cols) + col);
            if ((idx < normalized.size())) {
                result.push_back(normalized[idx]);
            } else {
                // out of bounds, skip
            }
        }
    }

    return result;
}

std::string cipher::cipher_text() const {
    return cipher_text_from_normalized(m_normalized, m_rows, m_cols);
}

std::string cipher::normalized_cipher_text() const {
    if (m_normalized.empty()) {
        return std::string();
    }

    std::vector<std::string> chunks;
    chunks.reserve(m_cols);

    for (std::size_t col = 0U; (col < m_cols); col = (col + 1U)) {
        std::string chunk;
        chunk.reserve(m_rows);

        for (std::size_t row = 0U; (row < m_rows); row = (row + 1U)) {
            const std::size_t idx = ((row * m_cols) + col);
            if ((idx < m_normalized.size())) {
                chunk.push_back(m_normalized[idx]);
            } else {
                chunk.push_back(' ');
            }
        }

        chunks.push_back(std::move(chunk));
    }

    std::string joined;
    for (std::size_t i = 0U; (i < chunks.size()); i = (i + 1U)) {
        if ((i != 0U)) {
            joined.push_back(' ');
        }
        joined += chunks[i];
    }

    return joined;
}

}  // namespace crypto_square

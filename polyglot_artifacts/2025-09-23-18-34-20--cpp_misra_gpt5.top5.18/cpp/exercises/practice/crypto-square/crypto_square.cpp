#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(const std::string& text) : normalized_() {
    // Use locale-aware character classification and case conversion
    static const std::locale loc{};
    normalized_.reserve(text.size());
    for (const char ch : text) {
        if (std::isalnum(ch, loc)) {
            const char lowered = std::tolower(ch, loc);
            normalized_.push_back(lowered);
        } else {
            // skip non-alphanumeric characters
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::size_t cipher::size() const {
    const std::size_t len = normalized_.size();
    if (len == static_cast<std::size_t>(0)) {
        return static_cast<std::size_t>(0);
    }

    // Smallest c such that (c * c) >= len
    std::size_t c = static_cast<std::size_t>(0);
    while (((c * c) < len)) {
        ++c;
    }
    return c;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments{};
    const std::size_t c = size();
    const std::size_t len = normalized_.size();

    if (c == static_cast<std::size_t>(0)) {
        return segments;
    }

    const std::size_t estimated_rows = ((len + (c - static_cast<std::size_t>(1))) / c);
    segments.reserve(estimated_rows);

    std::size_t start = static_cast<std::size_t>(0);
    while ((start < len)) {
        const std::size_t remaining = (len - start);
        const std::size_t take = ((remaining < c) ? remaining : c);
        segments.push_back(normalized_.substr(start, take));
        start = (start + take);
    }

    return segments;
}

std::string cipher::ciphertext() const {
    const std::vector<std::string> rows = plain_text_segments();
    const std::size_t c = size();
    if (c == static_cast<std::size_t>(0)) {
        return std::string{};
    }

    std::string out{};
    out.reserve(normalized_.size());

    const std::size_t r = rows.size();

    for (std::size_t col = static_cast<std::size_t>(0); (col < c); ++col) {
        for (std::size_t row = static_cast<std::size_t>(0); (row < r); ++row) {
            const std::size_t row_len = rows[row].size();
            if (col < row_len) {
                out.push_back(rows[row][col]);
            } else {
                // no character in this row/column intersection
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::vector<std::string> rows = plain_text_segments();
    const std::size_t c = size();
    if (c == static_cast<std::size_t>(0)) {
        return std::string{};
    }
    const std::size_t r = rows.size();

    std::string out{};
    // Each of c groups will have length r (with possible trailing space padding)
    // Reserve for characters plus spaces between groups
    const std::size_t groups_total_len = (c * r);
    const std::size_t spaces_between = (c == static_cast<std::size_t>(0)) ? static_cast<std::size_t>(0) : (c - static_cast<std::size_t>(1));
    out.reserve(groups_total_len + spaces_between);

    for (std::size_t col = static_cast<std::size_t>(0); (col < c); ++col) {
        if (col != static_cast<std::size_t>(0)) {
            out.push_back(' ');
        }
        for (std::size_t row = static_cast<std::size_t>(0); (row < r); ++row) {
            const std::size_t row_len = rows[row].size();
            if (col < row_len) {
                out.push_back(rows[row][col]);
            } else {
                // pad to fill perfect rectangle
                out.push_back(' ');
            }
        }
    }

    return out;
}

}  // namespace crypto_square

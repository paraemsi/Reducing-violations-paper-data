#include "crypto_square.h"

#include <cstddef>
#include <locale>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

std::string normalize_text(const std::string& text) {
    std::string result{};
    result.reserve(text.size());
    const std::locale loc{};
    for (std::string::const_reference ch : text) {
        if (std::isalnum(ch, loc)) {
            result.push_back(std::tolower(ch, loc));
        } else {
            // skip non-alphanumeric characters
        }
    }
    return result;
}

static std::pair<std::size_t, std::size_t> dimensions(const std::string& normalized) {
    const std::size_t len = normalized.size();
    if (len == static_cast<std::size_t>(0U)) {
        return std::make_pair(static_cast<std::size_t>(0U), static_cast<std::size_t>(0U));
    } else {
        // c = smallest integer where (c * c) >= len
        std::size_t c = static_cast<std::size_t>(0U);
        while (((c * c) < len)) {
            ++c;
        }
        // r = ceil(len / c)
        const std::size_t r = (len + (c - static_cast<std::size_t>(1U))) / c;
        return std::make_pair(r, c);
    }
}

std::vector<std::string> plaintext_segments(const std::string& text) {
    const std::string normalized = normalize_text(text);
    std::vector<std::string> segments{};
    const std::pair<std::size_t, std::size_t> dims = dimensions(normalized);
    const std::size_t r = dims.first;
    const std::size_t c = dims.second;

    if (c == static_cast<std::size_t>(0U)) {
        return segments;
    } else {
        segments.reserve(r);
        for (std::size_t i = static_cast<std::size_t>(0U); i < normalized.size(); i += c) {
            const std::size_t remaining = normalized.size() - i;
            const std::size_t take = (remaining < c) ? remaining : c;
            segments.emplace_back(normalized.substr(i, take));
        }
        return segments;
    }
}

std::string ciphertext(const std::string& text) {
    const std::vector<std::string> rows = plaintext_segments(text);
    if (rows.empty()) {
        return std::string{};
    } else {
        const std::size_t r = rows.size();
        const std::size_t c = rows.front().size();
        std::string out{};
        out.reserve(c * r);
        for (std::size_t col = static_cast<std::size_t>(0U); col < c; ++col) {
            for (std::size_t row = static_cast<std::size_t>(0U); row < r; ++row) {
                if (col < rows[row].size()) {
                    out.push_back(rows[row][col]);
                } else {
                    // skip missing cells
                }
            }
        }
        return out;
    }
}

std::string normalized_ciphertext(const std::string& text) {
    const std::vector<std::string> rows = plaintext_segments(text);
    if (rows.empty()) {
        return std::string{};
    } else {
        const std::size_t r = rows.size();
        const std::size_t c = rows.front().size();
        std::string out{};
        for (std::size_t col = static_cast<std::size_t>(0U); col < c; ++col) {
            if (col != static_cast<std::size_t>(0U)) {
                out.push_back(' ');
            } else {
                // first chunk has no leading space
            }
            for (std::size_t row = static_cast<std::size_t>(0U); row < r; ++row) {
                if (col < rows[row].size()) {
                    out.push_back(rows[row][col]);
                } else {
                    out.push_back(' ');
                }
            }
        }
        return out;
    }
}

cipher::cipher(const std::string& text) : normalized_{normalize_text(text)} {
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments{};
    const std::pair<std::size_t, std::size_t> dims = dimensions(normalized_);
    const std::size_t r = dims.first;
    const std::size_t c = dims.second;

    if (c == static_cast<std::size_t>(0U)) {
        return segments;
    } else {
        segments.reserve(r);
        for (std::size_t i = static_cast<std::size_t>(0U); i < normalized_.size(); i += c) {
            const std::size_t remaining = normalized_.size() - i;
            const std::size_t take = (remaining < c) ? remaining : c;
            segments.emplace_back(normalized_.substr(i, take));
        }
        return segments;
    }
}

std::string cipher::cipher_text() const {
    const std::vector<std::string> rows = plain_text_segments();
    if (rows.empty()) {
        return std::string{};
    } else {
        const std::size_t r = rows.size();
        const std::size_t c = rows.front().size();
        std::string out{};
        out.reserve(c * r);
        for (std::size_t col = static_cast<std::size_t>(0U); col < c; ++col) {
            for (std::size_t row = static_cast<std::size_t>(0U); row < r; ++row) {
                if (col < rows[row].size()) {
                    out.push_back(rows[row][col]);
                } else {
                    // skip missing cells
                }
            }
        }
        return out;
    }
}

std::string cipher::normalized_cipher_text() const {
    const std::vector<std::string> rows = plain_text_segments();
    if (rows.empty()) {
        return std::string{};
    } else {
        const std::size_t r = rows.size();
        const std::size_t c = rows.front().size();
        std::string out{};
        for (std::size_t col = static_cast<std::size_t>(0U); col < c; ++col) {
            if (col != static_cast<std::size_t>(0U)) {
                out.push_back(' ');
            } else {
                // first chunk has no leading space
            }
            for (std::size_t row = static_cast<std::size_t>(0U); row < r; ++row) {
                if (col < rows[row].size()) {
                    out.push_back(rows[row][col]);
                } else {
                    out.push_back(' ');
                }
            }
        }
        return out;
    }
}

}  // namespace crypto_square

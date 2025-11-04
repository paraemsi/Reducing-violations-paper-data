#include "crypto_square.h"

#include <cstddef>
#include <locale>
#include <utility>

namespace crypto_square {

cipher::cipher(const std::string& text) : normalized_() {
    normalized_.reserve(text.size());

    const std::locale loc = std::locale::classic();
    for (char ch : text) {
        if (std::isalnum(ch, loc)) {
            normalized_.push_back(std::tolower(ch, loc));
        }
    }
}

std::string cipher::normalized_text() const {
    return normalized_;
}

std::pair<std::size_t, std::size_t> cipher::dimensions(std::size_t length) {
    if (length == static_cast<std::size_t>(0U)) {
        return std::make_pair(static_cast<std::size_t>(0U), static_cast<std::size_t>(0U));
    }

    std::size_t c = static_cast<std::size_t>(0U);
    while (((c * c) < length)) {
        c = c + static_cast<std::size_t>(1U);
    }

    std::size_t r = c;
    if (((r - static_cast<std::size_t>(1U)) * c) >= length) {
        r = r - static_cast<std::size_t>(1U);
    }

    // Now: (r * c) >= length, (c >= r), and ((c - r) <= 1)
    return std::make_pair(r, c);
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;

    const std::size_t length = normalized_.size();
    if (length == static_cast<std::size_t>(0U)) {
        return segments;
    }

    const std::pair<std::size_t, std::size_t> dims = dimensions(length);
    const std::size_t r = dims.first;
    const std::size_t c = dims.second;
    (void)r; // r is not needed here; keep to document intent

    segments.reserve((length + (c - static_cast<std::size_t>(1U))) / c);

    for (std::size_t pos = static_cast<std::size_t>(0U); pos < length; pos = pos + c) {
        const std::size_t remaining = length - pos;
        const std::size_t take = (remaining < c) ? remaining : c;
        segments.emplace_back(normalized_.substr(pos, take));
    }

    return segments;
}

std::string cipher::cipher_text() const {
    const std::size_t length = normalized_.size();
    if (length == static_cast<std::size_t>(0U)) {
        return std::string();
    }

    const std::pair<std::size_t, std::size_t> dims = dimensions(length);
    const std::size_t r = dims.first;
    const std::size_t c = dims.second;

    std::string out;
    out.reserve(length);

    for (std::size_t col = static_cast<std::size_t>(0U); col < c; col = col + static_cast<std::size_t>(1U)) {
        for (std::size_t row = static_cast<std::size_t>(0U); row < r; row = row + static_cast<std::size_t>(1U)) {
            const std::size_t idx = (row * c) + col;
            if (idx < length) {
                out.push_back(normalized_[idx]);
            } else {
                // no padding for cipher_text()
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::size_t length = normalized_.size();
    if (length == static_cast<std::size_t>(0U)) {
        return std::string();
    }

    const std::pair<std::size_t, std::size_t> dims = dimensions(length);
    const std::size_t r = dims.first;
    const std::size_t c = dims.second;

    std::string out;
    // Each of c chunks has length r, plus (c - 1) spaces between them.
    const std::size_t total_size = (c * r) + (c - static_cast<std::size_t>(1U));
    out.reserve(total_size);

    for (std::size_t col = static_cast<std::size_t>(0U); col < c; col = col + static_cast<std::size_t>(1U)) {
        if (col != static_cast<std::size_t>(0U)) {
            out.push_back(' ');
        }
        for (std::size_t row = static_cast<std::size_t>(0U); row < r; row = row + static_cast<std::size_t>(1U)) {
            const std::size_t idx = (row * c) + col;
            if (idx < length) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }

    return out;
}

}  // namespace crypto_square

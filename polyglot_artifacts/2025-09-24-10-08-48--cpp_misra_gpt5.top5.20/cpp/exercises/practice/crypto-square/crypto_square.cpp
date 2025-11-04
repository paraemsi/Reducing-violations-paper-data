#include "crypto_square.h"

#include <cstddef>
#include <cstdint>
#include <locale>
#include <string>
#include <utility>
#include <vector>

namespace {
using Dim = std::pair<std::size_t, std::size_t>;

Dim compute_dimensions(std::size_t n) {
    if (n == static_cast<std::size_t>(0U)) {
        return Dim{static_cast<std::size_t>(0U), static_cast<std::size_t>(0U)};
    } else {
        std::size_t c = static_cast<std::size_t>(0U);
        while (((c * c) < n)) {
            c = (c + static_cast<std::size_t>(1U));
        }
        std::size_t r = c;
        if ((((c - static_cast<std::size_t>(1U)) * c) >= n)) {
            r = (c - static_cast<std::size_t>(1U));
        }
        return Dim{r, c};
    }
}
}  // namespace

namespace crypto_square {

cipher::cipher(const std::string& text) : input_(text) {}

std::string cipher::normalize_plain_text() const {
    std::string out{};
    out.reserve(input_.size());
    std::locale loc{};
    const std::ctype<char>& facet = std::use_facet<std::ctype<char>>(loc);

    for (char ch : input_) {
        if (facet.is(std::ctype_base::alnum, ch)) {
            out.push_back(facet.tolower(ch));
        } else {
            // skip non-alphanumeric
        }
    }
    return out;
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::string normalized = normalize_plain_text();
    const std::size_t n = normalized.size();
    std::vector<std::string> segments{};
    if (n == static_cast<std::size_t>(0U)) {
        return segments;
    } else {
        const Dim dims = compute_dimensions(n);
        const std::size_t r = dims.first;
        const std::size_t c = dims.second;
        segments.reserve(r);
        for (std::size_t i = static_cast<std::size_t>(0U); i < r; i = (i + static_cast<std::size_t>(1U))) {
            const std::size_t start = (i * c);
            if (start >= n) {
                break;
            } else {
                const std::size_t remaining = (n - start);
                const std::size_t len = ((remaining < c) ? remaining : c);
                segments.push_back(normalized.substr(start, len));
            }
        }
        return segments;
    }
}

std::string cipher::ciphertext() const {
    const std::string normalized = normalize_plain_text();
    const std::size_t n = normalized.size();
    if (n == static_cast<std::size_t>(0U)) {
        return std::string{};
    } else {
        const Dim dims = compute_dimensions(n);
        const std::size_t r = dims.first;
        const std::size_t c = dims.second;
        std::string result{};
        result.reserve(n);
        for (std::size_t col = static_cast<std::size_t>(0U); col < c; col = (col + static_cast<std::size_t>(1U))) {
            for (std::size_t row = static_cast<std::size_t>(0U); row < r; row = (row + static_cast<std::size_t>(1U))) {
                const std::size_t idx = ((row * c) + col);
                if (idx < n) {
                    result.push_back(normalized[idx]);
                } else {
                    // skip padding
                }
            }
        }
        return result;
    }
}

std::string cipher::normalized_cipher_text() const {
    const std::string normalized = normalize_plain_text();
    const std::size_t n = normalized.size();
    if (n == static_cast<std::size_t>(0U)) {
        return std::string{};
    } else {
        const Dim dims = compute_dimensions(n);
        const std::size_t r = dims.first;
        const std::size_t c = dims.second;
        std::string result{};
        const std::size_t total_len =
            ((c == static_cast<std::size_t>(0U)) ? static_cast<std::size_t>(0U)
                                                 : ((c * r) + (c - static_cast<std::size_t>(1U))));
        result.reserve(total_len);
        for (std::size_t col = static_cast<std::size_t>(0U); col < c; col = (col + static_cast<std::size_t>(1U))) {
            if (col != static_cast<std::size_t>(0U)) {
                result.push_back(' ');
            } else {
                // first chunk - no leading space
            }
            for (std::size_t row = static_cast<std::size_t>(0U); row < r; row = (row + static_cast<std::size_t>(1U))) {
                const std::size_t idx = ((row * c) + col);
                if (idx < n) {
                    result.push_back(normalized[idx]);
                } else {
                    result.push_back(' ');
                }
            }
        }
        return result;
    }
}

}  // namespace crypto_square

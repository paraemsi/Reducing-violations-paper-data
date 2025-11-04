#include "crypto_square.h"

#include <cctype>
#include <string>

namespace crypto_square {

cipher::cipher(const std::string& input) {
    // Normalize: keep only alphanumeric, lower-case everything.
    normalized_.reserve(input.size());
    for (char ch : input) {
        // Use <cctype> utilities and std::char_traits to avoid direct numeric conversions.
        const std::char_traits<char>::int_type ch_int = std::char_traits<char>::to_int_type(ch);
        if (std::isalnum(ch_int) != 0) {
            const std::char_traits<char>::int_type lower_int = std::tolower(ch_int);
            const char lower_ch = std::char_traits<char>::to_char_type(lower_int);
            normalized_.push_back(lower_ch);
        }
    }
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) {
        return std::string{};
    }

    using size_type = std::string::size_type;

    const size_type len = normalized_.size();

    // Compute smallest c such that c*c >= len, without floating point.
    size_type c = static_cast<size_type>(0U);
    while ((c * c) < len) {
        ++c;
    }

    // Determine r such that r*c >= len, c >= r, and c - r <= 1.
    size_type r = c;
    if ((c > static_cast<size_type>(0U)) && ((c * (c - static_cast<size_type>(1U))) >= len)) {
        r = c - static_cast<size_type>(1U);
    }

    // Build output: c chunks of length r, separated by spaces.
    // Each chunk is built by reading down the rows for a given column.
    std::string out{};
    // Reserve approximate size: c * r + (c - 1) spaces
    out.reserve((c * r) + ((c == static_cast<size_type>(0U)) ? static_cast<size_type>(0U) : (c - static_cast<size_type>(1U))));

    for (size_type col = static_cast<size_type>(0U); col < c; ++col) {
        for (size_type row = static_cast<size_type>(0U); row < r; ++row) {
            const size_type idx = (row * c) + col;
            if (idx < len) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
        if ((col + static_cast<size_type>(1U)) < c) {
            out.push_back(' ');
        }
    }

    return out;
}

}  // namespace crypto_square

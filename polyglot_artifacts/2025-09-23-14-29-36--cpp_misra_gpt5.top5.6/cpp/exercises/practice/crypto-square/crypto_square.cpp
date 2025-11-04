#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

namespace crypto_square {

namespace {
    std::string normalize_text(const std::string& input) {
        std::string out;
        out.reserve(input.size());
        for (std::string::const_iterator it = input.begin(); it != input.end(); ++it) {
            using traits = std::char_traits<char>;
            const traits::int_type ch = traits::to_int_type(*it);
            if (std::isalnum(ch) != 0) {
                const traits::int_type lowered = std::tolower(ch);
                const char lowered_char = traits::to_char_type(lowered);
                out.push_back(lowered_char);
            }
        }
        return out;
    }

    std::size_t ceil_sqrt_size(std::size_t n) {
        if (n == static_cast<std::size_t>(0U)) {
            return static_cast<std::size_t>(0U);
        }
        std::size_t lo = static_cast<std::size_t>(1U);
        std::size_t hi = n;
        while (lo < hi) {
            const std::size_t mid = lo + ((hi - lo) / static_cast<std::size_t>(2U));
            const std::size_t div = (n / mid);
            if ((mid > div) || ((mid == div) && ((n % mid) == static_cast<std::size_t>(0U)))) {
                hi = mid;
            } else {
                lo = mid + static_cast<std::size_t>(1U);
            }
        }
        return lo;
    }

    void compute_dimensions(std::size_t len, std::size_t& rows, std::size_t& cols) {
        if (len == static_cast<std::size_t>(0U)) {
            rows = static_cast<std::size_t>(0U);
            cols = static_cast<std::size_t>(0U);
            return;
        }
        const std::size_t c = ceil_sqrt_size(len);
        std::size_t r = (len / c);
        if ((len % c) != static_cast<std::size_t>(0U)) {
            r = r + static_cast<std::size_t>(1U);
        }
        rows = r;
        cols = c;
    }
}

cipher::cipher(const std::string& text)
    : original_(text) {}

std::string cipher::normalize_plain_text() const {
    return normalize_text(original_);
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::string normalized = normalize_text(original_);
    const std::size_t n = normalized.size();
    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    compute_dimensions(n, rows, cols);

    std::vector<std::string> segments;
    if (n == static_cast<std::size_t>(0U)) {
        return segments;
    }

    segments.reserve(rows);
    for (std::size_t start = static_cast<std::size_t>(0U); start < n; start = start + cols) {
        const std::size_t len_remaining = n - start;
        const std::size_t take = (len_remaining < cols) ? len_remaining : cols;
        segments.push_back(normalized.substr(start, take));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    const std::string normalized = normalize_text(original_);
    const std::size_t n = normalized.size();
    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    compute_dimensions(n, rows, cols);

    std::string out;
    if (n == static_cast<std::size_t>(0U)) {
        return out;
    }
    out.reserve(n);
    for (std::size_t c = static_cast<std::size_t>(0U); c < cols; ++c) {
        for (std::size_t r = static_cast<std::size_t>(0U); r < rows; ++r) {
            const std::size_t idx = (r * cols) + c;
            if (idx < n) {
                out.push_back(normalized[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::string normalized = normalize_text(original_);
    const std::size_t n = normalized.size();
    std::size_t rows = static_cast<std::size_t>(0U);
    std::size_t cols = static_cast<std::size_t>(0U);
    compute_dimensions(n, rows, cols);

    if (n == static_cast<std::size_t>(0U)) {
        return std::string();
    }

    std::vector<std::string> chunks;
    chunks.reserve(cols);
    for (std::size_t c = static_cast<std::size_t>(0U); c < cols; ++c) {
        std::string col_str;
        col_str.reserve(rows);
        for (std::size_t r = static_cast<std::size_t>(0U); r < rows; ++r) {
            const std::size_t idx = (r * cols) + c;
            if (idx < n) {
                col_str.push_back(normalized[idx]);
            } else {
                col_str.push_back(' ');
            }
        }
        chunks.push_back(col_str);
    }

    std::string out;
    out.reserve((cols * rows) + (cols - static_cast<std::size_t>(1U)));
    for (std::size_t i = static_cast<std::size_t>(0U); i < chunks.size(); ++i) {
        if (i != static_cast<std::size_t>(0U)) {
            out.push_back(' ');
        }
        out += chunks[i];
    }
    return out;
}

}  // namespace crypto_square

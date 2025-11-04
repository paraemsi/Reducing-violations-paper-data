#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

namespace {
[[nodiscard]] std::size_t compute_columns(std::size_t n) {
    std::size_t c = 0U;
    while (((c * c) < n)) {
        c = c + 1U;
    }
    return c;
}

[[nodiscard]] std::size_t compute_rows(std::size_t n, std::size_t c) {
    if ((n == 0U)) {
        return 0U;
    }
    if ((c > 0U) && (((c - 1U) * c) >= n)) {
        return (c - 1U);
    }
    return c;
}
}  // namespace

cipher::cipher(const std::string& text) : m_text(text) {}

std::string cipher::normalized_plain_text() const {
    return ::crypto_square::normalized_plain_text(m_text);
}

std::vector<std::string> cipher::plaintext_segments() const {
    return ::crypto_square::plaintext_segments(m_text);
}

std::string cipher::ciphertext() const {
    return ::crypto_square::ciphertext(m_text);
}

std::string cipher::normalized_cipher_text() const {
    return ::crypto_square::normalized_cipher_text(m_text);
}

std::string normalized_plain_text(const std::string& text) {
    std::string out{};
    out.reserve(text.size());
    for (const char ch : text) {
        if ((std::isalnum(std::char_traits<char>::to_int_type(ch)) != 0)) {
            const std::char_traits<char>::int_type lowered_int =
                std::tolower(std::char_traits<char>::to_int_type(ch));
            const char lowered =
                std::char_traits<char>::to_char_type(lowered_int);
            out.push_back(lowered);
        }
    }
    return out;
}

std::vector<std::string> plaintext_segments(const std::string& text) {
    const std::string normalized = normalized_plain_text(text);
    const std::size_t n = normalized.size();
    const std::size_t c = compute_columns(n);

    std::vector<std::string> rows{};
    if ((c == 0U)) {
        return rows;
    }

    for (std::size_t i = 0U; i < n; i = i + c) {
        const std::size_t remaining = n - i;
        const std::size_t take = (remaining < c) ? remaining : c;
        rows.emplace_back(normalized.substr(i, take));
    }
    return rows;
}

std::string ciphertext(const std::string& text) {
    const std::string normalized = normalized_plain_text(text);
    const std::size_t n = normalized.size();
    const std::size_t c = compute_columns(n);
    const std::size_t r = compute_rows(n, c);

    if ((c == 0U) || (r == 0U)) {
        return std::string{};
    }

    std::string out{};
    out.reserve(n);
    for (std::size_t col = 0U; col < c; col = col + 1U) {
        for (std::size_t row = 0U; row < r; row = row + 1U) {
            const std::size_t idx = (row * c) + col;
            if (idx < n) {
                out.push_back(normalized[idx]);
            } else {
                { /* no-op: beyond end, no padding in raw ciphertext */ }
            }
        }
    }
    return out;
}

std::string normalized_cipher_text(const std::string& text) {
    const std::string normalized = normalized_plain_text(text);
    const std::size_t n = normalized.size();
    const std::size_t c = compute_columns(n);
    const std::size_t r = compute_rows(n, c);

    if ((c == 0U) || (r == 0U)) {
        return std::string{};
    }

    std::string result{};
    for (std::size_t col = 0U; col < c; col = col + 1U) {
        if (col != 0U) {
            result.push_back(' ');
        }
        for (std::size_t row = 0U; row < r; row = row + 1U) {
            const std::size_t idx = (row * c) + col;
            if (idx < n) {
                result.push_back(normalized[idx]);
            } else {
                result.push_back(' ');
            }
        }
    }
    return result;
}

}  // namespace crypto_square

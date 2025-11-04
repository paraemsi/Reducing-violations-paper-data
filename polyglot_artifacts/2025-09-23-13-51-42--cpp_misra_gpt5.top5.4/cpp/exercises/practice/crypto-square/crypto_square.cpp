#include "crypto_square.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

namespace crypto_square {

namespace {
std::string normalize_text(const std::string& text)
{
    std::string out;
    out.reserve(text.size());

    for (char ch : text) {
        const unsigned char uch = static_cast<unsigned char>(ch);
        const char safe_ch = static_cast<char>(uch);
        const std::char_traits<char>::int_type ich = std::char_traits<char>::to_int_type(safe_ch);
        if ((std::isalnum(ich) != 0)) {
            const std::char_traits<char>::int_type lch = std::tolower(ich);
            const char lowered = std::char_traits<char>::to_char_type(lch);
            out.push_back(lowered);
        }
    }

    return out;
}

std::size_t columns_for(std::size_t len)
{
    if ((len == 0U)) {
        return 0U;
    }

    std::size_t c = 1U;
    while (((c * c) < len)) {
        ++c;
    }
    return c;
}

std::size_t rows_for(std::size_t len, std::size_t c)
{
    if ((c == 0U)) {
        return 0U;
    }

    std::size_t r = (len / c);
    if (((r * c) < len)) {
        ++r;
    }
    return r;
}

} // namespace

cipher::cipher(const std::string& text)
    : normalized_(normalize_text(text))
{
}

std::string cipher::normalize_plain_text() const
{
    return normalized_;
}

std::vector<std::string> cipher::plaintext_segments() const
{
    const std::size_t len = normalized_.size();
    const std::size_t c = columns_for(len);
    const std::size_t r = rows_for(len, c);

    std::vector<std::string> segments;
    segments.reserve(r);

    for (std::size_t row = 0U; row < r; ++row) {
        const std::size_t start = (row * c);
        if ((start >= len)) {
            // Should not happen, but keep safe.
            segments.emplace_back();
        } else {
            const std::size_t remaining = (len - start);
            const std::size_t take = (remaining < c) ? remaining : c;
            segments.emplace_back(normalized_.substr(start, take));
        }
    }

    return segments;
}

std::string cipher::ciphertext() const
{
    const std::size_t len = normalized_.size();
    const std::size_t c = columns_for(len);
    const std::size_t r = rows_for(len, c);

    (void)r; // r is not strictly needed for this computation

    std::string out;
    out.reserve(len);

    for (std::size_t col = 0U; col < c; ++col) {
        for (std::size_t row = 0U; row < r; ++row) {
            const std::size_t idx = ((row * c) + col);
            if ((idx < len)) {
                out.push_back(normalized_[idx]);
            }
        }
    }

    return out;
}

std::string cipher::normalized_cipher_text() const
{
    const std::size_t len = normalized_.size();
    const std::size_t c = columns_for(len);
    const std::size_t r = rows_for(len, c);

    if ((c == 0U) || (r == 0U)) {
        return std::string();
    }

    std::vector<std::string> chunks;
    chunks.reserve(c);

    for (std::size_t col = 0U; col < c; ++col) {
        std::string chunk;
        chunk.reserve(r);
        for (std::size_t row = 0U; row < r; ++row) {
            const std::size_t idx = ((row * c) + col);
            if ((idx < len)) {
                chunk.push_back(normalized_[idx]);
            } else {
                chunk.push_back(' ');
            }
        }
        chunks.emplace_back(chunk);
    }

    // Join chunks with spaces
    std::string out;
    for (std::size_t i = 0U; i < chunks.size(); ++i) {
        if ((i != 0U)) {
            out.push_back(' ');
        }
        out += chunks[i];
    }

    return out;
}

// Free-function API implementations

std::string normalize_plain_text(const std::string& text)
{
    return cipher(text).normalize_plain_text();
}

std::vector<std::string> plaintext_segments(const std::string& text)
{
    return cipher(text).plaintext_segments();
}

std::string ciphertext(const std::string& text)
{
    return cipher(text).ciphertext();
}

std::string normalized_cipher_text(const std::string& text)
{
    return cipher(text).normalized_cipher_text();
}

}  // namespace crypto_square

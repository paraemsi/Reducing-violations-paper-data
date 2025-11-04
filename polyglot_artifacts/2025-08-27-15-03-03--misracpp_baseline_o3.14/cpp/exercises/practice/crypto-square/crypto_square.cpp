#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>

namespace crypto_square {

// ---------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------
static std::pair<std::size_t, std::size_t> dimensions(std::size_t len)
{
    if (len == 0) {
        return {0, 0};
    }

    std::size_t r = static_cast<std::size_t>(std::floor(std::sqrt(len)));
    std::size_t c = static_cast<std::size_t>(std::ceil(std::sqrt(len)));

    if (r * c < len) {
        ++r;
    }
    return {r, c};
}

// ---------------------------------------------------------------------
// public API
// ---------------------------------------------------------------------
std::string normalize_plain_text(const std::string& input)
{
    std::string out;
    out.reserve(input.size());
    for (unsigned char ch : input) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

std::vector<std::string> plain_text_segments(const std::string& input)
{
    const auto normalized = normalize_plain_text(input);
    const auto [rows, cols] = dimensions(normalized.size());

    std::vector<std::string> segments;
    if (cols == 0) {
        return segments;
    }

    for (std::size_t start = 0; start < normalized.size(); start += cols) {
        segments.push_back(normalized.substr(start, cols));
    }
    return segments;
}

std::string cipher_text(const std::string& input)
{
    const auto normalized = normalize_plain_text(input);
    const auto [rows, cols] = dimensions(normalized.size());

    if (cols == 0) {
        return {};
    }

    std::string cipher;
    cipher.reserve(rows * cols);

    for (std::size_t c = 0; c < cols; ++c) {
        for (std::size_t r = 0; r < rows; ++r) {
            const std::size_t idx = r * cols + c;
            if (idx < normalized.size()) {
                cipher.push_back(normalized[idx]);
            }
        }
    }
    return cipher;
}

std::string normalized_cipher_text(const std::string& input)
{
    const auto normalized = normalize_plain_text(input);
    const auto [rows, cols] = dimensions(normalized.size());

    if (cols == 0) {
        return {};
    }

    std::vector<std::string> chunks(cols, std::string(rows, ' '));

    for (std::size_t c = 0; c < cols; ++c) {
        for (std::size_t r = 0; r < rows; ++r) {
            const std::size_t idx = r * cols + c;
            if (idx < normalized.size()) {
                chunks[c][r] = normalized[idx];
            }
        }
    }

    std::ostringstream os;
    for (std::size_t i = 0; i < chunks.size(); ++i) {
        os << chunks[i];
        if (i + 1 < chunks.size()) {
            os << ' ';
        }
    }
    return os.str();
}

// ---------------------------------------------------------------------
// cipher class wrappers
// ---------------------------------------------------------------------
cipher::cipher(const std::string& text) : text_(text) {}

std::string cipher::normalize_plain_text() const
{
    return crypto_square::normalize_plain_text(text_);
}

std::vector<std::string> cipher::plain_text_segments() const
{
    return crypto_square::plain_text_segments(text_);
}

std::string cipher::cipher_text() const
{
    return crypto_square::cipher_text(text_);
}

std::string cipher::normalized_cipher_text() const
{
    return crypto_square::normalized_cipher_text(text_);
}

}  // namespace crypto_square

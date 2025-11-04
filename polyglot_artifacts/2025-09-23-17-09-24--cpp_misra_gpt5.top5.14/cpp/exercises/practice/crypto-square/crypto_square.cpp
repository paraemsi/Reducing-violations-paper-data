#include "crypto_square.h"

#include <cstddef>
#include <locale>
#include <string>
#include <vector>

namespace {

// Compute ceil(sqrt(n)) without floating-point and without overflow.
std::size_t ceil_sqrt(std::size_t n) {
    if (n <= 1U) {
        return n;
    }

    std::size_t low = 1U;
    std::size_t high = n;
    std::size_t ans = 1U;

    while (low <= high) {
        const std::size_t mid = low + ((high - low) / 2U);
        if (mid <= (n / mid)) {
            ans = mid;
            low = mid + 1U;
        } else {
            if (mid == 0U) {
                break;
            }
            high = mid - 1U;
        }
    }

    if (((ans * ans) == n)) {
        return ans;
    }
    return ans + 1U;
}

}  // unnamed namespace

namespace crypto_square {

std::string normalize_plain_text(const std::string& input) {
    const std::locale loc{};
    std::string out;
    out.reserve(input.size());

    for (const char ch : input) {
        if (std::isalnum(ch, loc)) {
            out.push_back(std::tolower(ch, loc));
        } else {
            // skip non-alphanumeric characters
        }
    }

    return out;
}

std::string cipher_text(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const std::size_t n = normalized.size();

    if (n == 0U) {
        return std::string{};
    }

    const std::size_t c = ceil_sqrt(n);
    const std::size_t r = (n + (c - 1U)) / c;

    std::string out;
    out.reserve(n);

    for (std::size_t j = 0U; j < c; ++j) {
        for (std::size_t i = 0U; i < r; ++i) {
            const std::size_t idx = ((i * c) + j);
            if (idx < n) {
                out.push_back(normalized[idx]);
            } else {
                // beyond message length: no padding for compact cipher_text
            }
        }
    }

    return out;
}

std::string ciphertext(const std::string& input) {
    return cipher_text(input);
}

std::string normalized_cipher_text(const std::string& input) {
    const std::string normalized = normalize_plain_text(input);
    const std::size_t n = normalized.size();

    if (n == 0U) {
        return std::string{};
    }

    const std::size_t c = ceil_sqrt(n);
    const std::size_t r = (n + (c - 1U)) / c;

    std::string out;
    // Each of c chunks has length r, plus (c - 1) spaces between chunks.
    out.reserve((c * r) + (c > 0U ? (c - 1U) : 0U));

    for (std::size_t j = 0U; j < c; ++j) {
        for (std::size_t i = 0U; i < r; ++i) {
            const std::size_t idx = ((i * c) + j);
            if (idx < n) {
                out.push_back(normalized[idx]);
            } else {
                out.push_back(' ');
            }
        }
        if (((j + 1U) < c)) {
            out.push_back(' ');
        }
    }

    return out;
}

// class cipher implementation
cipher::cipher(const char* input) : input_{((input != nullptr) ? std::string{input} : std::string{})} {}

cipher::cipher(const std::string& input) : input_{input} {}

std::string cipher::normalize_plain_text() const {
    return crypto_square::normalize_plain_text(input_);
}

std::vector<std::string> cipher::plain_text_segments() const {
    const std::string normalized = crypto_square::normalize_plain_text(input_);
    const std::size_t n = normalized.size();

    if (n == 0U) {
        return std::vector<std::string>{};
    }

    const std::size_t c = ceil_sqrt(n);
    const std::size_t r = (n + (c - 1U)) / c;

    std::vector<std::string> rows;
    rows.reserve(r);

    for (std::size_t i = 0U; i < r; ++i) {
        const std::size_t start = (i * c);
        const std::size_t remaining = (n - start);
        const std::size_t count = ((remaining < c) ? remaining : c);
        rows.emplace_back(normalized.substr(start, count));
    }

    return rows;
}

std::string cipher::cipher_text() const {
    return crypto_square::cipher_text(input_);
}

std::string cipher::ciphertext() const {
    return crypto_square::cipher_text(input_);
}

std::string cipher::normalized_cipher_text() const {
    return crypto_square::normalized_cipher_text(input_);
}

}  // namespace crypto_square

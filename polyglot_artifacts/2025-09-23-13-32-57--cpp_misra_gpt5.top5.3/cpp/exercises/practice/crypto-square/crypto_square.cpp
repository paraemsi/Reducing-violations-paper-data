#include "crypto_square.h"

#include <cstddef>
#include <locale>
#include <string>
#include <vector>

namespace crypto_square {

namespace {
    std::string normalize(const std::string& s) {
        std::string out{};
        out.reserve(s.size());
        const std::locale loc{};
        for (const char ch : s) {
            if (std::isalnum(ch, loc)) {
                out.push_back(std::tolower(ch, loc));
            } else {
                // ignore non-alphanumeric
            }
        }
        return out;
    }

    struct dims {
        std::size_t rows;
        std::size_t cols;
    };

    dims compute_dims(const std::size_t n) {
        std::size_t c = 0U;
        while (((c * c) < n)) {
            c = (c + 1U);
        }
        const std::size_t r = (((c * (c - 1U)) >= n) ? (c - 1U) : c);
        const dims d{r, c};
        return d;
    }
}  // namespace

cipher::cipher(const std::string& text)
    : input_(text) {
}

std::string cipher::normalize_plain_text() const {
    return normalize(input_);
}

std::vector<std::string> cipher::plaintext_segments() const {
    const std::string norm = normalize(input_);
    const std::size_t n = norm.size();
    const dims d = compute_dims(n);
    const std::size_t r = d.rows;
    const std::size_t c = d.cols;

    std::vector<std::string> segs{};
    if ((c == 0U)) {
        return segs;
    } else {
        // proceed
    }

    segs.reserve(r);
    for (std::size_t row = 0U; (row < r); row = (row + 1U)) {
        const std::size_t start = (row * c);
        const std::size_t remaining = ((n > start) ? (n - start) : 0U);
        const std::size_t len = ((remaining < c) ? remaining : c);
        segs.emplace_back(norm.substr(start, len));
    }
    return segs;
}

std::string cipher::cipher_text() const {
    const std::string norm = normalize(input_);
    const std::size_t n = norm.size();
    const dims d = compute_dims(n);
    const std::size_t r = d.rows;
    const std::size_t c = d.cols;

    std::string out{};
    out.reserve(n);

    for (std::size_t col = 0U; (col < c); col = (col + 1U)) {
        for (std::size_t row = 0U; (row < r); row = (row + 1U)) {
            const std::size_t idx = ((row * c) + col);
            if ((idx < n)) {
                out.push_back(norm[idx]);
            } else {
                // skip out-of-range
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    const std::string norm = normalize(input_);
    const std::size_t n = norm.size();
    const dims d = compute_dims(n);
    const std::size_t r = d.rows;
    const std::size_t c = d.cols;

    if ((c == 0U)) {
        return std::string{};
    } else {
        // proceed
    }

    const std::size_t total = (r * c);
    const std::size_t missing = ((total > n) ? (total - n) : 0U);
    (void)missing; // computed for clarity; padding handled inline

    std::string out{};
    out.reserve(((r * c) + ((c > 0U) ? (c - 1U) : 0U)));

    for (std::size_t col = 0U; (col < c); col = (col + 1U)) {
        if ((col > 0U)) {
            out.push_back(' ');
        }
        for (std::size_t row = 0U; (row < r); row = (row + 1U)) {
            const std::size_t idx = ((row * c) + col);
            if ((idx < n)) {
                out.push_back(norm[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square

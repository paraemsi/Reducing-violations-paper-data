#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

namespace crypto_square {

// Normalize plaintext: keep alphanumerics, convert to lower-case
std::string normalize_plaintext(std::string_view text) {
    std::string result;
    result.reserve(text.size());
    std::for_each(text.begin(), text.end(), [&](unsigned char ch) {
        if (std::isalnum(ch)) {
            result.push_back(static_cast<char>(std::tolower(ch)));
        }
    });
    return result;
}

// Column count (c) computed per square-code rules
std::size_t size(std::string_view text) {
    const std::string norm = normalize_plaintext(text);
    if (norm.empty()) {
        return 0;
    }
    return static_cast<std::size_t>(std::ceil(std::sqrt(norm.size())));
}

// Split normalized plaintext into row segments of length `size(text)`
std::vector<std::string> plaintext_segments(std::string_view text) {
    const std::string norm = normalize_plaintext(text);
    const std::size_t columns = size(text);

    // Guard against empty input to avoid division-by-zero / infinite loop
    if (columns == 0) {
        return {};
    }

    std::vector<std::string> segments;
    for (std::size_t i = 0; i < norm.size(); i += columns) {
        segments.emplace_back(norm.substr(i, columns));
    }
    return segments;
}

// Produce the cipher text with no spacing
std::string ciphertext(std::string_view text) {
    const auto segments = plaintext_segments(text);
    if (segments.empty()) {
        return {};
    }
    const std::size_t columns = size(text);
    std::string cipher;
    cipher.reserve(segments.size() * columns);

    for (std::size_t col = 0; col < columns; ++col) {
        for (const auto& row : segments) {
            if (col < row.size()) {
                cipher.push_back(row[col]);
            }
        }
    }
    return cipher;
}

// Produce the normalized cipher text spaced every `row_count` characters
std::string normalized_cipher_text(std::string_view text) {
    const auto segments = plaintext_segments(text);
    if (segments.empty()) {
        return {};
    }
    const std::size_t rows    = segments.size();   // r
    const std::size_t columns = size(text);        // c

    std::ostringstream oss;
    for (std::size_t col = 0; col < columns; ++col) {
        if (col != 0) {
            oss << ' ';
        }
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                oss << segments[row][col];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

/* ------------------------------------------------------------------ */
/*  cipher wrapper implementation                                      */
/* ------------------------------------------------------------------ */

cipher::cipher(std::string_view text)
    : plain_{normalize_plaintext(text)} {}

// Return the already-normalized plaintext
std::string cipher::normalize_plaintext() const { return plain_; }

// Column/row size according to square-code rules
std::size_t cipher::size() const {
    if (plain_.empty()) {
        return 0;
    }
    return static_cast<std::size_t>(std::ceil(std::sqrt(plain_.size())));
}

// Break plaintext into row segments
std::vector<std::string> cipher::plaintext_segments() const {
    const std::size_t columns = size();
    if (columns == 0) {
        return {};
    }

    std::vector<std::string> segments;
    for (std::size_t i = 0; i < plain_.size(); i += columns) {
        segments.emplace_back(plain_.substr(i, columns));
    }
    return segments;
}

// Generate cipher text with no spacing
std::string cipher::ciphertext() const {
    const auto segments = plaintext_segments();
    if (segments.empty()) {
        return {};
    }

    const std::size_t columns = size();
    std::string cipher_text;
    cipher_text.reserve(segments.size() * columns);

    for (std::size_t col = 0; col < columns; ++col) {
        for (const auto &row : segments) {
            if (col < row.size()) {
                cipher_text.push_back(row[col]);
            }
        }
    }
    return cipher_text;
}

// Generate normalized cipher text with spaces between columns
std::string cipher::normalized_cipher_text() const {
    const auto segments = plaintext_segments();
    if (segments.empty()) {
        return {};
    }
    const std::size_t rows    = segments.size();  // r
    const std::size_t columns = size();           // c

    std::ostringstream oss;
    for (std::size_t col = 0; col < columns; ++col) {
        if (col != 0) {
            oss << ' ';
        }
        for (std::size_t row = 0; row < rows; ++row) {
            if (col < segments[row].size()) {
                oss << segments[row][col];
            } else {
                oss << ' ';
            }
        }
    }
    return oss.str();
}

}  // namespace crypto_square

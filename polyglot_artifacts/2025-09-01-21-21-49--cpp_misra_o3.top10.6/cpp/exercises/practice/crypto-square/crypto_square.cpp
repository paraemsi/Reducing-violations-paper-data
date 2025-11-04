#include "crypto_square.h"

#include <algorithm>
#include <cstdint>
#include <locale>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

static std::string normalize(const std::string& input)
{
    const std::locale              loc {};
    std::string                    cleaned {};
    cleaned.reserve(input.size());

    for (const char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch), loc) != 0) {           // locale-aware alphanumeric check
            cleaned.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch), loc)));   // to lower using same locale
        }
    }
    return cleaned;
}

std::string encode(const std::string& input)
{
    const std::string normalized { normalize(input) };
    const std::uint64_t len { static_cast<std::uint64_t>(normalized.length()) };

    if (len == static_cast<std::uint64_t>(0U)) {
        return std::string {};
    }

    const double        root_d { std::sqrt(static_cast<double>(len)) };
    std::uint64_t       rows { static_cast<std::uint64_t>(std::floor(root_d)) };
    std::uint64_t       cols { static_cast<std::uint64_t>(std::ceil(root_d)) };

    if ((rows * cols) < len) {
        ++rows;                                         // guarantee capacity
    }

    std::vector<std::string> chunks;
    chunks.reserve(cols);

    for (std::uint64_t col { 0U }; (col < cols); ++col) {
        std::string chunk {};
        chunk.reserve(rows);

        for (std::uint64_t row { 0U }; (row < rows); ++row) {
            const std::uint64_t index { (row * cols) + col };

            if (index < len) {
                chunk.push_back(normalized[static_cast<std::size_t>(index)]);
            } else {
                chunk.push_back(' ');                   // pad short columns
            }
        }
        chunks.push_back(chunk);
    }

    std::string encoded {};
    for (std::uint64_t i { 0U }; (i < cols); ++i) {
        encoded += chunks[static_cast<std::size_t>(i)];
        if (i + static_cast<std::uint64_t>(1U) < cols) {
            encoded.push_back(' ');
        }
    }

    return encoded;
}

// ----------------------------------------------------------------------
// class cipher implementation
// ----------------------------------------------------------------------

cipher::cipher(const std::string& text)
    : m_plaintext { normalize(text) }
{
}

std::string cipher::normalize_plain_text() const
{
    return m_plaintext;
}

std::vector<std::string> cipher::plaintext_segments() const
{
    const std::uint64_t len { static_cast<std::uint64_t>(m_plaintext.length()) };

    if (len == static_cast<std::uint64_t>(0U)) {
        return {};
    }

    const double        root_d { std::sqrt(static_cast<double>(len)) };
    std::uint64_t       rows { static_cast<std::uint64_t>(std::floor(root_d)) };
    std::uint64_t       cols { static_cast<std::uint64_t>(std::ceil(root_d)) };

    if ((rows * cols) < len) {
        ++rows;
    }

    std::vector<std::string> segments;
    segments.reserve(rows);

    for (std::uint64_t row { 0U }; (row < rows); ++row) {
        const std::uint64_t start { row * cols };
        const std::uint64_t remaining { (len > start) ? (len - start) : static_cast<std::uint64_t>(0U) };
        const std::uint64_t count { (remaining >= cols) ? cols : remaining };

        segments.emplace_back(
            m_plaintext.substr(static_cast<std::size_t>(start),
                               static_cast<std::size_t>(count)));
    }

    return segments;
}

std::string cipher::ciphertext() const
{
    const std::uint64_t len { static_cast<std::uint64_t>(m_plaintext.length()) };

    if (len == static_cast<std::uint64_t>(0U)) {
        return std::string {};
    }

    const double        root_d { std::sqrt(static_cast<double>(len)) };
    std::uint64_t       rows { static_cast<std::uint64_t>(std::floor(root_d)) };
    std::uint64_t       cols { static_cast<std::uint64_t>(std::ceil(root_d)) };

    if ((rows * cols) < len) {
        ++rows;
    }

    std::string cipher_txt {};
    cipher_txt.reserve(len);

    for (std::uint64_t col { 0U }; (col < cols); ++col) {
        for (std::uint64_t row { 0U }; (row < rows); ++row) {
            const std::uint64_t index { (row * cols) + col };
            if (index < len) {
                cipher_txt.push_back(m_plaintext[static_cast<std::size_t>(index)]);
            }
        }
    }
    return cipher_txt;
}

std::string cipher::normalized_cipher_text() const
{
    const std::uint64_t len { static_cast<std::uint64_t>(m_plaintext.length()) };

    if (len == static_cast<std::uint64_t>(0U)) {
        return std::string {};
    }

    const double        root_d { std::sqrt(static_cast<double>(len)) };
    std::uint64_t       rows { static_cast<std::uint64_t>(std::floor(root_d)) };
    std::uint64_t       cols { static_cast<std::uint64_t>(std::ceil(root_d)) };

    if ((rows * cols) < len) {
        ++rows;
    }

    std::vector<std::string> chunks;
    chunks.reserve(cols);

    for (std::uint64_t col { 0U }; (col < cols); ++col) {
        std::string chunk {};
        chunk.reserve(rows);

        for (std::uint64_t row { 0U }; (row < rows); ++row) {
            const std::uint64_t index { (row * cols) + col };

            if (index < len) {
                chunk.push_back(m_plaintext[static_cast<std::size_t>(index)]);
            } else {
                chunk.push_back(' ');
            }
        }
        chunks.push_back(chunk);
    }

    std::string encoded {};
    for (std::uint64_t i { 0U }; (i < cols); ++i) {
        encoded += chunks[static_cast<std::size_t>(i)];
        if ((i + static_cast<std::uint64_t>(1U)) < cols) {
            encoded.push_back(' ');
        }
    }

    return encoded;
}

}  // namespace crypto_square

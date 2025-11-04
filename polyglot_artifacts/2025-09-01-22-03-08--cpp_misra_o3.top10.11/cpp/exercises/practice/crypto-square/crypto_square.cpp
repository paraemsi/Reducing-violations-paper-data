#include "crypto_square.h"

#include <locale>
#include <string>

namespace crypto_square {

auto encode(const std::string& text) -> std::string
{
    // locale object for the character classification / transformation helpers
    const std::locale loc{};                                       // NOLINT(cert-err58-cpp)

    /* Step 1: normalise – keep only alphanumeric characters and convert to lower-case */
    std::string normalized{};
    normalized.reserve(text.size());

    for (const char ch : text) {
        if (std::isalnum(ch, loc) != 0) {
            normalized.push_back(std::tolower(ch, loc));
        }
    }

    const std::size_t length{normalized.size()};
    if (length == static_cast<std::size_t>(0U)) {
        return std::string{};
    }

    /* Step 2: determine rectangle dimensions (rows × columns) using only integral math */
    std::size_t columns{static_cast<std::size_t>(1U)};
    while (((columns * columns) < length)) {
        ++columns;
    }

    std::size_t rows{};
    if (columns > static_cast<std::size_t>(1U)) {
        rows = columns - static_cast<std::size_t>(1U);
    } else {
        rows = static_cast<std::size_t>(1U);
    }

    if (((rows * columns) < length)) {
        rows = columns;
    }

    /* Step 3: build the encoded message column-wise, inserting spaces between chunks */
    const std::size_t expected_size{
        (columns * rows) + (columns - static_cast<std::size_t>(1U))
    };
    std::string encoded{};
    encoded.reserve(expected_size);

    for (std::size_t col = static_cast<std::size_t>(0U); col < columns; ++col) {
        if (col != static_cast<std::size_t>(0U)) {
            encoded.push_back(' ');
        }

        for (std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row) {
            const std::size_t index{(row * columns) + col};
            if (index < length) {
                encoded.push_back(normalized[index]);
            } else {
                encoded.push_back(' ');
            }
        }
    }

    return encoded;
}

/* -------------------------------------------------------------------------- */
/*  Internal helpers                                                          */
/* -------------------------------------------------------------------------- */

/* Encode a message that is *already* normalised (digits / lowercase only). */
static auto encode_from_normalized(const std::string& normalized) -> std::string
{
    const std::size_t length{normalized.size()};
    if (length == static_cast<std::size_t>(0U)) {
        return std::string{};
    }

    /* Determine rectangle dimensions (rows × columns). */
    std::size_t columns{static_cast<std::size_t>(1U)};
    while (((columns * columns) < length)) {
        ++columns;
    }

    std::size_t rows{};
    if (columns > static_cast<std::size_t>(1U)) {
        rows = columns - static_cast<std::size_t>(1U);
    } else {
        rows = static_cast<std::size_t>(1U);
    }

    if (((rows * columns) < length)) {
        rows = columns;
    }

    /* Build encoded text column-wise with spaces between chunks. */
    const std::size_t expected_size{
        (columns * rows) + (columns - static_cast<std::size_t>(1U))
    };
    std::string encoded{};
    encoded.reserve(expected_size);

    for (std::size_t col = static_cast<std::size_t>(0U); col < columns; ++col) {
        if (col != static_cast<std::size_t>(0U)) {
            encoded.push_back(' ');
        }

        for (std::size_t row = static_cast<std::size_t>(0U); row < rows; ++row) {
            const std::size_t index{(row * columns) + col};
            if (index < length) {
                encoded.push_back(normalized[index]);
            } else {
                encoded.push_back(' ');
            }
        }
    }

    return encoded;
}

/* -------------------------------------------------------------------------- */
/*  crypto_square::cipher implementation                                      */
/* -------------------------------------------------------------------------- */

cipher::cipher(const std::string& text)
{
    const std::locale loc{};                                       // NOLINT(cert-err58-cpp)
    m_normalized.reserve(text.size());

    for (const char ch : text) {
        if (std::isalnum(ch, loc) != 0) {
            m_normalized.push_back(std::tolower(ch, loc));
        }
    }

    m_cipher = encode_from_normalized(m_normalized);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return m_normalized;
}

auto cipher::cipher_text() const -> std::string
{
    return m_cipher;
}

}  // namespace crypto_square

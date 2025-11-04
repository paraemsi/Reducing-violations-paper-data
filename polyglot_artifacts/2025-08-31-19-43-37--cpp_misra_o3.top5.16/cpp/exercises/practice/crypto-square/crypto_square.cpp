#include "crypto_square.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace crypto_square {

auto cipher_text(std::string const& input) -> std::string
{
    /* Normalise the input : remove punctuation / spaces and convert
       letters to lower-case (digits remain). */
    const char uppercase_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercase_letters[] = "abcdefghijklmnopqrstuvwxyz";
    const char digit_characters[]  = "0123456789";

    std::string normalised{};
    normalised.reserve(input.length());

    for (char ch : input) {
        bool added {false};

        /* Handle alphabetic characters */
        for (std::size_t idx {0U}; idx < 26U; ++idx) {
            if (uppercase_letters[idx] == ch) {
                normalised.push_back(lowercase_letters[idx]);
                added = true;
                break;
            } else if (lowercase_letters[idx] == ch) {
                normalised.push_back(ch);
                added = true;
                break;
            } else {
                /* continue searching */
            }
        }

        /* Handle decimal digits */
        if (!added) {
            for (std::size_t idx {0U}; idx < 10U; ++idx) {
                if (digit_characters[idx] == ch) {
                    normalised.push_back(ch);
                    added = true;
                    break;
                } else {
                    /* continue searching */
                }
            }
        } else {
            /* already processed */
        }
        /* All other characters are ignored */
    }

    const std::size_t message_length {normalised.length()};

    if (message_length == 0U) {
        return std::string{};
    }

    /* Determine rectangle dimensions (rows r, columns c) */
    std::size_t c {1U};
    while (((c * c) < message_length)) {
        ++c;
    }

    std::size_t r {c};
    if (((r > 0U) && (((r - 1U) * c) >= message_length))) {
        r -= 1U;
    }

    /* Build the rows, padding with spaces where necessary */
    std::vector<std::string> rows{};
    rows.reserve(r);

    std::size_t pos {0U};
    while (pos < message_length) {
        const std::size_t remaining {message_length - pos};
        const std::size_t take {(remaining < c) ? remaining : c};

        std::string row {normalised.substr(pos, take)};
        while (row.length() < c) {
            row.push_back(' ');
        }

        rows.push_back(row);
        pos += take;
    }

    while (rows.size() < r) {
        rows.emplace_back(std::string(c, ' '));
    }

    /* Read columns to obtain the encoded text */
    std::string encoded{};
    encoded.reserve(r * c);

    for (std::size_t col {0U}; col < c; ++col) {
        for (std::size_t row {0U}; row < r; ++row) {
            encoded.push_back(rows[row][col]);
        }
    }

    /* Split into chunks of length r, separated by spaces */
    std::string result{};
    result.reserve((c * (r + 1U)));   /* each chunk plus a space */

    for (std::size_t chunk {0U}; chunk < c; ++chunk) {
        if (chunk != 0U) {
            result.push_back(' ');
        }
        result.append(encoded.substr((chunk * r), r));
    }

    return result;
}

/* ---------------------------------------------------------------------
 *  cipher class implementation
 * ------------------------------------------------------------------ */
cipher::cipher(std::string const& text) :
    normalised_{}
{
    /* Normalise the plain text – remove punctuation / spaces and make
       alphabetic characters lower-case (digits remain unchanged). */
    const char uppercase_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercase_letters[] = "abcdefghijklmnopqrstuvwxyz";
    const char digit_characters[]  = "0123456789";

    normalised_.reserve(text.length());

    for (char ch : text) {
        bool added {false};

        /* Handle alphabetic characters */
        for (std::size_t idx {0U}; idx < 26U; ++idx) {
            if (uppercase_letters[idx] == ch) {
                normalised_.push_back(lowercase_letters[idx]);
                added = true;
                break;
            } else if (lowercase_letters[idx] == ch) {
                normalised_.push_back(ch);
                added = true;
                break;
            } else {
                /* continue searching */
            }
        }

        /* Handle decimal digits */
        if (!added) {
            for (std::size_t idx {0U}; idx < 10U; ++idx) {
                if (digit_characters[idx] == ch) {
                    normalised_.push_back(ch);
                    added = true;
                    break;
                } else {
                    /* continue searching */
                }
            }
        } else {
            /* already processed */
        }
        /* All other characters are ignored */
    }
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return normalised_;
}

auto cipher::cipher_text() const -> std::string
{
    const std::size_t message_length {normalised_.length()};

    if (message_length == 0U) {
        return std::string{};
    }

    /* Determine rectangle dimensions (rows r, columns c) */
    std::size_t c {1U};
    while (((c * c) < message_length)) {
        ++c;
    }

    std::size_t r {c};
    if (((r > 0U) && (((r - 1U) * c) >= message_length))) {
        r -= 1U;
    }

    /* Build the rows, padding with spaces where necessary */
    std::vector<std::string> rows{};
    rows.reserve(r);

    std::size_t pos {0U};
    while (pos < message_length) {
        const std::size_t remaining {message_length - pos};
        const std::size_t take {(remaining < c) ? remaining : c};

        std::string row {normalised_.substr(pos, take)};
        while (row.length() < c) {
            row.push_back(' ');
        }

        rows.push_back(row);
        pos += take;
    }

    while (rows.size() < r) {
        rows.emplace_back(std::string(c, ' '));
    }

    /* Read columns to obtain the encoded text */
    std::string encoded{};
    encoded.reserve(r * c);

    for (std::size_t col {0U}; col < c; ++col) {
        for (std::size_t row_idx {0U}; row_idx < r; ++row_idx) {
            encoded.push_back(rows[row_idx][col]);
        }
    }

    /* Split into chunks of length r, separated by spaces */
    std::string result{};
    result.reserve((c * (r + 1U)));

    for (std::size_t chunk {0U}; chunk < c; ++chunk) {
        if (chunk != 0U) {
            result.push_back(' ');
        }
        result.append(encoded.substr((chunk * r), r));
    }

    return result;
}

}  // namespace crypto_square

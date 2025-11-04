#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

/**
 * Encode the supplied English text using the “crypto-square” algorithm.
 *
 * The function applies the following steps:
 * 1. Normalise the input by removing spaces and punctuation and
 *    converting everything to lower-case.
 * 2. Lay the text out in an r × c rectangle where
 *      • r × c ≥ len,
 *      • c ≥ r,
 *      • c − r ≤ 1.
 * 3. Read the rectangle column-wise to build the cipher text.
 * 4. Split the cipher text into chunks of length r, separated by spaces.
 *
 * \param input The text to encode.
 * \return      The encoded text.
 */
class cipher
{
public:
    explicit cipher(std::string_view input);

    auto normalized_cipher_text() const -> std::string;
    auto cipher_text() const -> std::string;
    auto size() const -> std::size_t;
    auto plain_text_segments() const -> std::vector<std::string>;

private:
    std::string m_normalized {};
    std::size_t m_rows { 0U };
    std::size_t m_columns { 0U };
};

/* Convenience helper that directly returns the cipher text. */
auto cipher_text(std::string_view input) -> std::string;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

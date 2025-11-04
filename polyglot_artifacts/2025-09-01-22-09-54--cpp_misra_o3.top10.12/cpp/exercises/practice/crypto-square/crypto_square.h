#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

namespace crypto_square {

using index_t = std::size_t;

/* Normalise the input text by removing non-alphanumeric
 * characters and converting remaining letters to lower-case. */
auto normalize_plain_text(const std::string& input) -> std::string;

/* Break the normalised text into equal-sized rows that will form
 * the rectangle.  Each row contains the number of columns (`c`). */
auto plain_text_segments(const std::string& input) -> std::vector<std::string>;

/* Read the rectangle column-wise (left-to-right, top-to-bottom)
 * and return the resulting cipher text without spacing. */
auto ciphertext(const std::string& input) -> std::string;

/* Return the cipher text split into `c` chunks of length `r`
 * and separated by a single space.  Trailing chunks are padded
 * with spaces so each chunk length is identical. */
auto normalized_cipher_text(const std::string& input) -> std::string;

/* Wrapper class required by the unit-tests. */
class cipher
{
public:
    explicit cipher(const std::string& text);

    [[nodiscard]] auto normalize_plain_text() const -> std::string;
    [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>;
    [[nodiscard]] auto ciphertext() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string m_input;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

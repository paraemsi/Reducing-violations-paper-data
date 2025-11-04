#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>
#include <vector>
#include <cstddef>

namespace crypto_square {

/*
 * Encode the supplied text using the “crypto-square” algorithm.
 *
 * Parameters:
 *   text – the English text to encode
 *
 * Returns:
 *   encoded text split into column-chunks separated by a single space
 */
class cipher {
public:
    explicit cipher(std::string const & text);

    auto normalize_plain_text() const -> std::string;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string m_normalized {};
    std::size_t m_rows {0U};
    std::size_t m_cols {0U};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

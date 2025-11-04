#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>

namespace crypto_square {

/*
 * Encode the supplied English text using the “crypto square” method.
 *
 * The factory function ‘cipher’ returns an object that exposes
 *  – the normalised plain-text                      (normalized_cipher_text)
 *  – the cipher text grouped in equal-length chunks (ciphertext)
 * keeping everything self-contained and immutable.
 */

class cipher_result
{
public:
    explicit cipher_result(std::string_view text);

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;
    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto ciphertext() const -> std::string; // compatibility alias

private:
    std::string m_normalized;
};

/* Factory function expected by the test-suite */
[[nodiscard]] auto cipher(std::string_view text) -> cipher_result;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

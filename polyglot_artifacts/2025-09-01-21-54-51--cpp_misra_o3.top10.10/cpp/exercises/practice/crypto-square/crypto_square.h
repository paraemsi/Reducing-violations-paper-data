#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

#if __cplusplus >= 201703L
#define CRYPTO_NODISCARD [[nodiscard]]
#else
#define CRYPTO_NODISCARD
#endif

namespace crypto_square {

/*
 * Encode a message using the “crypto square” cipher.
 * The function normalises the input, determines the required
 * rectangle dimensions and returns the encoded text grouped
 * by columns separated with spaces.
 */
class cipher
{
public:
    explicit cipher(const std::string& text);

    CRYPTO_NODISCARD auto normalize_plain_text() const -> std::string;
    /* Compatibility alias expected by some test suites */
    CRYPTO_NODISCARD auto normalized_plain_text() const -> std::string
    {
        return normalize_plain_text();
    }

    CRYPTO_NODISCARD auto size() const -> std::size_t;
    CRYPTO_NODISCARD auto plain_text_segments() const -> std::vector<std::string>;
    CRYPTO_NODISCARD auto cipher_text() const -> std::string;
    CRYPTO_NODISCARD auto normalized_cipher_text() const -> std::string;

private:
    std::string m_text;
};

} // namespace crypto_square

#endif // CRYPTO_SQUARE_H

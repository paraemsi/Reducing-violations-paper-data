#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#if (__cplusplus >= 201703L)
#define CRYPTO_NODISCARD [[nodiscard]]
#else
#define CRYPTO_NODISCARD
#endif

namespace crypto_square {

/**
 * @brief Encode the supplied text using the classic square-code cipher.
 *
 * The function normalises the input, arranges the characters into an
 * r × c rectangle (as square as possible), then reads the rectangle
 * down the columns from left to right, emitting chunks that are
 * separated by a single space.
 *
 * @param input Plain-text to encode.
 * @return Encoded cipher-text (possibly empty).
 */
CRYPTO_NODISCARD auto cipher_text(std::string_view input) -> std::string;

/* -------------------------------------------------------------------------
 *  Class cipher : interface
 * --------------------------------------------------------------------- */
class cipher
{
public:
    explicit cipher(std::string_view text);

    [[nodiscard]] auto size() const -> std::size_t;
    [[nodiscard]] auto normalize_plain_text() const -> std::string;
    [[nodiscard]] auto normalize_plaintext() const -> std::string;       // alias
    [[nodiscard]] auto plaintext_segments() const -> std::vector<std::string>;
    [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>; // alias
    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

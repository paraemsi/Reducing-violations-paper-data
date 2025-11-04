#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

/*  Normalize an input phrase:
 *  1.  Remove punctuation and spaces.
 *  2.  Convert remaining characters to lower-case.
 */
[[nodiscard]] auto normalize_plain_text(std::string_view text) -> std::string;

/*  Smallest square side length that can contain the
 *  normalized text according to the rules.
 */
[[nodiscard]] auto square_size(std::string_view normalized_text) -> std::uint64_t;

/*  Break the normalized text into equally-sized segments
 *  (last one may be shorter).
 */
[[nodiscard]] auto plaintext_segments(std::string_view text) -> std::vector<std::string>;

/*  Ciphertext without any spacing. */
[[nodiscard]] auto ciphertext(std::string_view text) -> std::string;

/*  Ciphertext grouped by columns with single-space separation
 *  and right-padding of the final short chunks.
 */
[[nodiscard]] auto normalize_cipher_text(std::string_view text) -> std::string;

/*  Facade class required by unit-tests.
 *  Usage pattern:
 *      crypto_square::cipher("text").normalized_cipher_text();
 */
class cipher
{
public:
    explicit cipher(std::string_view text);

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string original_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

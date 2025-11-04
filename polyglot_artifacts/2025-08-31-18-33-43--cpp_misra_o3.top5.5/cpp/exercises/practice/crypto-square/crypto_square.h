#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>

namespace crypto_square {

/*  Normalise plain text:
 *  – remove punctuation and spaces
 *  – convert to lower-case
 */
auto normalize_plain_text(const std::string& text) -> std::string;

/*  Split the normalised text into row-wise segments that form the
 *  rectangle defined in the specification.
 */
auto plaintext_segments(const std::string& text) -> std::vector<std::string>;

/*  Cipher text without spaces (read column-wise). */
auto ciphertext(const std::string& text) -> std::string;

/*  Cipher text grouped into ‘c’ chunks of length ‘r’, separated by
 *  single spaces and padded with trailing spaces where required.     */
auto normalized_cipher_text(const std::string& text) -> std::string;

/*  Object-oriented façade internally used by the free-function
 *  `crypto_square::cipher()` that the unit tests call.                */
class cipher_text
{
public:
    explicit cipher_text(const std::string& text);

    auto normalize_plain_text()   const -> std::string;
    auto plaintext_segments()     const -> std::vector<std::string>;
    auto ciphertext()             const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string original_;
};

/*  Factory-style helper required by the tests:
 *      crypto_square::cipher("text").normalized_cipher_text();
 */
auto cipher(const std::string& text) -> cipher_text;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

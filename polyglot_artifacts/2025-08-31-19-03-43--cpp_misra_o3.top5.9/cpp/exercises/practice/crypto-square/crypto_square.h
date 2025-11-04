#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

/* Class-based interface expected by the unit-tests.
 * Provides a thin wrapper around the already-implemented
 * free-functions so we re-use the existing logic.           */
class cipher
{
public:
    explicit cipher(std::string_view text);

    [[nodiscard]] auto normalize_plain_text() const -> std::string;
    [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>;
    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string m_text {};
};

/*  Normalise the plain text:
 *   • remove punctuation / spaces
 *   • convert to lower-case
 */
auto normalize_plain_text(std::string_view text) -> std::string;

/*  Break the normalised text into row-wise segments that will form the
 *  rectangle (each segment size == column count, last may be shorter).
 */
auto plain_text_segments(std::string_view text) -> std::vector<std::string>;

/*  Read the rectangle column-wise, left→right, producing the raw cipher. */
auto cipher_text(std::string_view text) -> std::string;

/*  Group the cipher into space-separated chunks whose length equals the
 *  rectangle’s row count, padding the final chunk with spaces as required.
 */
auto normalized_cipher_text(std::string_view text) -> std::string;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

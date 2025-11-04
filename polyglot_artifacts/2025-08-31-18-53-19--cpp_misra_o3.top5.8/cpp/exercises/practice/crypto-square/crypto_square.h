#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>

namespace crypto_square {

/*
 * Normalize the input by:
 *  - removing punctuation and whitespace
 *  - converting to lower-case
 */
auto normalize_plain_text(const std::string& text) -> std::string;

/*
 * Break the normalized text into plain-text rows whose
 * length equals the chosen column count.
 */
auto plaintext_segments(const std::string& text) -> std::vector<std::string>;

/*
 * Encode the input by reading down the columns
 * of the plain-text rectangle (no spaces in output).
 */
auto cipher_text(const std::string& text) -> std::string;

/*
 * Same as cipher_text(), but return the groups
 * separated by single spaces.
 */
auto normalized_cipher_text(const std::string& text) -> std::string;

/* ------------------------------------------------------------------ */
/*  Fluent interface expected by the exercism test suite.             */
/* ------------------------------------------------------------------ */
class cipher_result final
{
public:
    explicit cipher_result(const std::string& text);

    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string original_;
};

/*
 * Factory that returns an object providing the two query
 * functions required by the tests.
 */
inline auto cipher(const std::string& text) -> cipher_result
{
    return cipher_result{text};
}

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

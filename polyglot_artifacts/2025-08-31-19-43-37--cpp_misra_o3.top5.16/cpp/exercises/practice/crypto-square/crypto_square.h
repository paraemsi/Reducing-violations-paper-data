#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <string>

namespace crypto_square {

auto cipher_text(std::string const& input) -> std::string;

/* ---------------------------------------------------------------------
 *  cipher class – supplies the API exercised by the unit-tests
 * ------------------------------------------------------------------ */
class cipher final
{
public:
    explicit cipher(std::string const& text);

    /* Normalised plain-text (lower-cased, no punctuation / spaces) */
    auto normalized_cipher_text() const -> std::string;

    /* Encoded text written in rectangular columns and chunked by rows */
    auto cipher_text() const -> std::string;

private:
    std::string normalised_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

/*
 * Encode a plaintext string using the classic “square code”.
 *
 *  - All characters that are not letters or decimal digits are removed.
 *  - Remaining characters are converted to lower-case.
 *  - The filtered text is written row-wise into the smallest rectangle
 *    that satisfies:  r * c >= N ,  c >= r ,  c - r <= 1 .
 *  - The cipher text is obtained by reading the rectangle column-wise,
 *    producing c chunks each of r characters (padding with spaces where
 *    the rectangle is not completely filled).
 *
 *  Example (see problem statement):
 *      cipher_text("If man was …") ->
 *      "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn  sseoau "
 */
auto cipher_text(const std::string& input) -> std::string;

/* Object-oriented façade expected by the test-suite */
class cipher {
public:
    explicit cipher(const std::string& text);

    auto normalize_plain_text() const -> std::string;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string normalized_{};
    std::uint32_t rows_{0U};
    std::uint32_t cols_{0U};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

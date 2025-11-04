#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>
#include <utility>

namespace crypto_square {

/**
 * Encode a text using the “crypto-square” algorithm.
 *
 * The function normalizes the input, arranges it in an r × c rectangle
 * that is as square as possible, then reads the columns left-to-right
 * producing chunks of length r separated by a single space.
 *
 * An empty input string yields an empty output string.
 *
 * \param text Plain-text message
 * \return     Cipher-text produced by the crypto-square algorithm
 */
[[nodiscard]] auto encode(const std::string& text) -> std::string;

class cipher
{
public:
    explicit cipher(const std::string& text_in);

    [[nodiscard]] auto normalize_plain_text() const -> std::string;

    [[nodiscard]] auto size() const -> std::size_t;

    [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>;

    [[nodiscard]] auto cipher_text() const -> std::string;

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string                       normalized_;
    std::size_t                       rows_;
    std::size_t                       cols_;
    std::vector<std::string>          rectangle_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

/**
 * @brief Encode the supplied text using the classic “square code”.
 *
 * The function performs the following steps:
 *   1. Normalises the text – strips non-alphanumeric characters and forces
 *      lower-case.
 *   2. Determines the smallest rectangle that satisfies the exercise rules.
 *   3. Reads the rectangle column-wise and returns the encoded text in chunks
 *      separated by single spaces.
 *
 * @param input  Plain-text to be encoded.
 * @return Encoded text, possibly containing internal spaces; an empty string
 *         when the input contains no alphanumeric characters.
 */
class cipher final {
public:
    explicit cipher(const std::string& text);

    auto normalize_plain_text() const -> std::string;
    auto size() const -> std::size_t;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string m_normalized {};
    std::size_t m_rows { 0U };
    std::size_t m_columns { 0U };
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

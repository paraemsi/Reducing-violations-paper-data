#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>

namespace crypto_square {

// Cipher object that provides the required API used by the tests
class cipher final
{
public:
    explicit cipher(std::string const& input);

    auto normalize_plain_text() const -> std::string;
    auto plaintext_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string text_;
};

// Return the normalized lower-case text with non-alphanumerics removed
auto normalize_plain_text(std::string const& input) -> std::string;

// Return the plain-text segments (rows) that form the rectangle
auto plaintext_segments(std::string const& input) -> std::vector<std::string>;

// Return the cipher text read down the columns (no spacing)
auto cipher_text(std::string const& input) -> std::string;

// Return the cipher text grouped in chunks of row-length, separated by spaces
auto normalized_cipher_text(std::string const& input) -> std::string;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

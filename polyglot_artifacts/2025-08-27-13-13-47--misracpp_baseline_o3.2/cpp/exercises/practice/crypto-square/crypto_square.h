#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

// Normalize the input by removing non-alphanumeric characters and
// converting to lowercase.
[[nodiscard]] std::string normalize_plain_text(const std::string& input);

// Break the normalized text into segments of equal column length.
[[nodiscard]] std::vector<std::string> plaintext_segments(const std::string& input);

// Encode the given text using the "crypto square" cipher.
[[nodiscard]] std::string cipher_text(const std::string& input);

// Class wrapper implementing the crypto square operations.
class cipher {
public:
    explicit cipher(const std::string& text);

    [[nodiscard]] std::string normalize_plain_text() const;
    [[nodiscard]] std::vector<std::string> plaintext_segments() const;
    [[nodiscard]] std::string ciphertext() const;
    [[nodiscard]] std::string normalized_cipher_text() const;

private:
    std::string text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

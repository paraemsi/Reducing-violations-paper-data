#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    // Normalized/plaintext helpers
    std::string normalized_plain_text() const;
    std::string normalize_plain_text() const;  // alias for compatibility

    // Row-wise segments of the plaintext (rows of length c, last may be shorter)
    std::vector<std::string> plain_text_segments() const;

    // Column-wise encodings
    std::string ciphertext() const;                 // concatenated columns (no spaces)
    std::string normalized_cipher_text() const;     // columns as chunks separated by spaces
    std::string normalize_cipher_text() const;      // alias for compatibility

    // Convenience aliases
    std::string encode() const;   // same as normalized_cipher_text()
    std::string encoded() const;  // alias for compatibility

private:
    std::string normalized_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    std::string normalize_plaintext() const;
    std::vector<std::string> plaintext_segments() const;
    std::string ciphertext() const;
    std::string normalized_cipher_text() const;

private:
    // Helpers
    std::string normalize(const std::string& text) const;
    std::size_t columns() const;
    std::size_t rows() const;

    std::string text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

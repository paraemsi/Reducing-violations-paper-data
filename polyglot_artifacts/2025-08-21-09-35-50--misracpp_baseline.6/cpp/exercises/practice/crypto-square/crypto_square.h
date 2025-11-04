#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher_result {
public:
    explicit cipher_result(std::string text);

    std::string normalized_cipher_text() const;
    std::string ciphertext() const;

private:
    std::string normalized_;
    std::string ciphered_;
};

cipher_result cipher(std::string text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

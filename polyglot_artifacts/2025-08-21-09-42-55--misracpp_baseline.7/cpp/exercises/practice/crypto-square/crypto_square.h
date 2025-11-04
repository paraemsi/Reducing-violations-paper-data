#ifndef CRYPTO_SQUARE_H
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher_result {
public:
    explicit cipher_result(const std::string& text);

    const std::string& normalized_cipher_text() const;
    const std::string& cipher_text() const;

private:
    std::string normalized_;
    std::string ciphered_;
};

cipher_result cipher(const std::string& text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

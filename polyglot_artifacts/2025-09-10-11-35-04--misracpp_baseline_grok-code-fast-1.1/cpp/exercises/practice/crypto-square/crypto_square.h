#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

struct cipher_result {
    std::string normalized_cipher_text() const;
    cipher_result(std::string t) : text_(std::move(t)) {}
private:
    std::string text_;
    friend cipher_result cipher(const std::string& plaintext);
};

cipher_result cipher(const std::string& plaintext);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

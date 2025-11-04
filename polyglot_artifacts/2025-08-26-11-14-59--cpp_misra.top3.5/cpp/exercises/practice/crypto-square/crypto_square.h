#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher_result {
public:
    cipher_result(const std::string& normalized, const std::string& encoded);

    [[nodiscard]] std::string normalized_cipher_text() const;

    [[nodiscard]] std::string cipher_text() const;

private:
    std::string normalized_text_;
    std::string encoded_text_;
};

[[nodiscard]] cipher_result cipher(const std::string& text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

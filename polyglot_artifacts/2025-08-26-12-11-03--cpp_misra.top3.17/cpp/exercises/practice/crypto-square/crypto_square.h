#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher_result {
public:
    cipher_result(const std::string& text, const std::string& normalized);

    std::string normalized_cipher_text() const;

    // Allow implicit conversion to std::string for backward compatibility
    operator std::string() const;

private:
    std::string encoded_text;
    std::string normalized_text;
};

cipher_result cipher(const std::string& text);

} // namespace crypto_square

#endif // CRYPTO_SQUARE_H

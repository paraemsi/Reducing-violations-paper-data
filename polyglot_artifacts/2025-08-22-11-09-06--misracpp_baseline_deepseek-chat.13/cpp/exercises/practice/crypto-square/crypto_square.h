#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher {
public:
    cipher(const std::string& text);
    std::string normalize_plain_text() const;
    std::size_t size() const;
    std::string normalized_cipher_text() const;
private:
    std::string normalized;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

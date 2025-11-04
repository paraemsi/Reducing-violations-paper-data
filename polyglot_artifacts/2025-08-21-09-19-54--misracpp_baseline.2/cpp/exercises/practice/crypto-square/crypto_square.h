#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher {
public:
    cipher(const std::string& text);

    std::string normalized_cipher_text() const;
private:
    std::string normalized_;
    std::size_t rows_{0};
    std::size_t cols_{0};
};

} // namespace crypto_square

#endif // CRYPTO_SQUARE_H

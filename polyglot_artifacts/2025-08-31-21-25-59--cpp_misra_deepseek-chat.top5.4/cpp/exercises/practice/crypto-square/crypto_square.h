#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <cstdint>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);
    std::string normalized_cipher_text() const;
    
private:
    std::string normalized_;
    std::uint32_t c_{0};
    std::uint32_t r_{0};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

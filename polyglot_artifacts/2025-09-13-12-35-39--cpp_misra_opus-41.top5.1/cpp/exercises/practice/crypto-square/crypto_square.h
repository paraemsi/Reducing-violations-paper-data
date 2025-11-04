#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <cstdint>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);
    
    std::string normalize_plain_text() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string plain_text;
    std::string normalized_text;
    
    void normalize();
    std::uint32_t calculate_columns() const;
    std::uint32_t calculate_rows(std::uint32_t cols) const;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

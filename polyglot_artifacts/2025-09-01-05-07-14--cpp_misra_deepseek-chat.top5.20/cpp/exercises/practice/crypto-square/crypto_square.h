#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <cstdint>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);
    std::string normalize_plain_text() const;
    std::uint32_t size() const;
    std::string plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;
    
private:
    std::string normalized_text;
    std::uint32_t num_cols;
    std::uint32_t num_rows;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

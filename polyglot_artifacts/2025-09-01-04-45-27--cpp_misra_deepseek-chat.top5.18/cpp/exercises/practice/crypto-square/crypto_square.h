#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);
    std::string normalize_plain_text() const;
    std::size_t size() const;
    std::string plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;
    
private:
    std::string normalized_text;
    std::size_t num_columns{0};
    std::size_t num_rows{0};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

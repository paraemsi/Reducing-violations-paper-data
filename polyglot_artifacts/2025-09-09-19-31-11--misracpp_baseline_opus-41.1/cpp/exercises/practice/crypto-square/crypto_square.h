#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {
    class cipher {
    private:
        std::string normalized_plain_text_;
        int rows_;
        int cols_;
        
        void normalize(const std::string& text);
        void calculate_dimensions();
        
    public:
        explicit cipher(const std::string& text);
        
        std::string normalized_cipher_text() const;
        std::string encoded() const;
        std::string ciphertext() const;
    };
}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

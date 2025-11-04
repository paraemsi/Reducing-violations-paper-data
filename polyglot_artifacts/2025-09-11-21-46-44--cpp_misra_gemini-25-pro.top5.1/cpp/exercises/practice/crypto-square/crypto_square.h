#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>

namespace crypto_square {
    class cipher {
    public:
        explicit cipher(std::string plain_text);

        std::string normalize_plain_text() const;
        std::vector<std::string> plain_text_segments() const;
        std::string cipher_text() const;
        std::string normalized_cipher_text() const;

    private:
        std::string plain_text_;
    };
}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

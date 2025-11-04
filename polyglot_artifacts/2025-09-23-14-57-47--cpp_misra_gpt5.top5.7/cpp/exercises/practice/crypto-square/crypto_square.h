#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    std::string normalize_plain_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string ciphertext() const;
    std::string normalized_cipher_text() const;
    std::size_t size() const;

private:
    std::string original_;

    static void dimensions(std::size_t length, std::size_t& rows, std::size_t& cols);
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

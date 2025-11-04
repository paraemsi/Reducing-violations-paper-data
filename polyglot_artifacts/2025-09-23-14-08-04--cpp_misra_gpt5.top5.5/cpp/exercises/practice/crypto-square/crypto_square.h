#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

class cipher final {
public:
    explicit cipher(const std::string& text);

    std::string normalize_plain_text() const;
    std::vector<std::string> plaintext_segments() const;
    std::string ciphertext() const;
    std::string normalized_cipher_text() const;
    std::size_t size() const;

private:
    std::string normalized_;
    std::size_t columns_;
    std::size_t rows_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

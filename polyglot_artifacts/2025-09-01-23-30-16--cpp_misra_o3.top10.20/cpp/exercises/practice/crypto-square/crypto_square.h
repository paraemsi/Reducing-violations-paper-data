#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <cstdint>

namespace crypto_square {

class cipher
{
public:
    explicit cipher(const std::string& input);

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;
    [[nodiscard]] auto cipher_text() const -> std::string;

private:
    std::string m_normalized_cipher_text {};
    std::string m_cipher_text {};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

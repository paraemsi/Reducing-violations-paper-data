#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

auto encode(const std::string& text) -> std::string;

/* -------------------------------------------------------------------------- */
/*  Crypto-square cipher interface                                            */
/* -------------------------------------------------------------------------- */
class cipher
{
public:
    explicit cipher(const std::string& text);

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;
    [[nodiscard]] auto cipher_text() const -> std::string;
    /* Many tracks name this the same as the exercise – provide an alias.    */
    [[nodiscard]] auto ciphertext() const -> std::string { return cipher_text(); }

private:
    std::string m_normalized{};
    std::string m_cipher{};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

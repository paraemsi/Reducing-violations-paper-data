#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>

namespace crypto_square {

class cipher final
{
public:
    explicit cipher(std::string_view input);

    auto normalized_cipher_text() const -> std::string;
    auto cipher_text() const -> std::string;

private:
    std::string m_normalised {};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

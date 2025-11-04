#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <string>
#include <string_view>
#include <cstdint>

namespace crypto_square {

auto encode(std::string_view text) -> std::string;

class cipher
{
public:
    explicit cipher(std::string_view text);

    auto normalized_cipher_text() const -> std::string;

private:
    std::string cipher_text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

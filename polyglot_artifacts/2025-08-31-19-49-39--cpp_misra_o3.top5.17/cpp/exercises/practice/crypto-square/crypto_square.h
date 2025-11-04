#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>

namespace crypto_square {

auto cipher_text(::std::string_view plain) -> ::std::string;

class cipher final
{
public:
    explicit cipher(::std::string_view text);

    [[nodiscard]] auto normalized_cipher_text() const -> ::std::string;

    [[nodiscard]] auto ciphertext() const -> ::std::string;

private:
    ::std::string normalized_;
};

auto cipher(::std::string_view text) -> cipher;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

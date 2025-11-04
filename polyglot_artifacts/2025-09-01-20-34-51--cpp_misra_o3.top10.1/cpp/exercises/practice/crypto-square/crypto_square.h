#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <cstddef>
#include <vector>

namespace crypto_square {

class cipher
{
public:
    explicit cipher(std::string_view input);

    auto normalize_plain_text() const -> std::string;
    auto square_size() const -> std::size_t;
    auto plaintext_segments() const -> std::vector<std::string>;
    auto ciphertext() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string normalized_;
};

auto cipher(std::string_view input) -> cipher;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

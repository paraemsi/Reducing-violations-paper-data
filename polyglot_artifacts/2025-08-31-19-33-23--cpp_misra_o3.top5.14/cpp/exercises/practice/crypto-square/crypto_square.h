#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <cstddef>
#include <string>
#include <vector>

namespace crypto_square {

auto cipher_text(const std::string& input) -> std::string;

class cipher
{
public:
    explicit cipher(const std::string& text);

    auto normalize_plain_text() const -> std::string;
    auto plaintext_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string normalized_;
    std::size_t rows_;
    std::size_t cols_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

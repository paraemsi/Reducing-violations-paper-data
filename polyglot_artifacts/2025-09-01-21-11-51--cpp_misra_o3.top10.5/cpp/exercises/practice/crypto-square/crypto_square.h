#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

class cipher
{
public:
    explicit cipher(const std::string& input);

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;
    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>;

private:
    std::string normalized_;
    std::vector<std::string> segments_;
    std::size_t columns_ { 0U };
    std::size_t rows_ { 0U };
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <string>

namespace crypto_square {

class cipher_result
{
public:
    explicit cipher_result(std::string input);

    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string original_text_;
};

[[nodiscard]] auto cipher(const std::string& input) -> cipher_result;

[[nodiscard]] auto cipher(const std::string& input) -> cipher;


}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

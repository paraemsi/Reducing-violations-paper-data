#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

auto normalize_plaintext(std::string_view text) -> std::string;

auto plaintext_segments(std::string_view text) -> std::vector<std::string>;

auto ciphertext(std::string_view text) -> std::string;

auto normalize_ciphertext(std::string_view text) -> std::string;

class cipher
{
public:
    explicit cipher(std::string_view text_in);

    [[nodiscard]] auto normalize_plaintext() const -> std::string;
    [[nodiscard]] auto plaintext_segments() const -> std::vector<std::string>;
    [[nodiscard]] auto ciphertext() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string m_input{};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

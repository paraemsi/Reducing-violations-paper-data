#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstdint>

namespace crypto_square {

class cipher
{
public:
    explicit cipher(const std::string& text);

    [[nodiscard]] auto normalize_plain_text() const -> std::string;
    [[nodiscard]] auto plaintext_segments() const -> std::vector<std::string>;
    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string m_text;
};

[[nodiscard]] auto normalize_plain_text(const std::string& text) -> std::string;
[[nodiscard]] auto plaintext_segments(const std::string& text) -> std::vector<std::string>;
[[nodiscard]] auto cipher_text(const std::string& text) -> std::string;
[[nodiscard]] auto normalized_cipher_text(const std::string& text) -> std::string;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

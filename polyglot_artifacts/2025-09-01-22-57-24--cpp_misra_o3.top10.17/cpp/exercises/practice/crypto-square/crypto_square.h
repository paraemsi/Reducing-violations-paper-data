#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

auto normalize_plain_text(const std::string& input) -> std::string;

auto plain_text_segments(const std::string& input) -> std::vector<std::string>;

auto cipher_text(const std::string& input) -> std::string;

auto normalized_cipher_text(const std::string& input) -> std::string;

/* Wrapper object expected by the unit-tests */
class cipher
{
public:
    explicit cipher(const std::string& text);

    auto normalize_plain_text() const -> std::string;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string m_text;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

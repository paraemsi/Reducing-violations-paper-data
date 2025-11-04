#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace crypto_square {

class cipher_result final
{
public:
    explicit cipher_result(std::string_view input);

    [[nodiscard]] auto normalize_plain_text() const -> std::string;
    [[nodiscard]] auto plaintext_segments() const -> std::vector<std::string>;
    [[nodiscard]] auto cipher_text() const -> std::string;
    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string   m_normalized{};
    std::uint64_t m_rows{0U};
    std::uint64_t m_columns{0U};
};

auto cipher(std::string_view input) -> cipher_result;

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

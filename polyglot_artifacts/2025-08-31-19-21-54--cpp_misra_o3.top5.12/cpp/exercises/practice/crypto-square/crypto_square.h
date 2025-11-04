#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>
#include <cstddef>
#include <cstdint>

namespace crypto_square {

class cipher
{
public:
    explicit cipher(std::string_view text);

    auto normalize_plain_text() const -> std::string;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string  m_normalized{};
    std::size_t  m_columns{0U};
    std::size_t  m_rows{0U};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

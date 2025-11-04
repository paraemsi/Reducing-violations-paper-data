#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>
#include <cstddef>

namespace crypto_square {

class cipher {
public:
    explicit cipher(std::string_view text);

    [[nodiscard]] std::string normalize_plain_text() const;
    [[nodiscard]] std::vector<std::string> plain_text_segments() const;
    [[nodiscard]] std::string cipher_text() const;
    [[nodiscard]] std::string normalized_cipher_text() const;

private:
    std::string m_normalized;

    [[nodiscard]] static std::size_t row_count(std::size_t length);
    [[nodiscard]] static std::size_t column_count(std::size_t length);
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

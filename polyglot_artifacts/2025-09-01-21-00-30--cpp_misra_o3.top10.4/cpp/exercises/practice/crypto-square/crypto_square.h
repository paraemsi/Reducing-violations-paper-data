#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>   // for std::size_t
#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    [[nodiscard]] std::string normalize_plain_text() const;
    [[nodiscard]] std::vector<std::string> plaintext_segments() const;
    [[nodiscard]] std::string cipher_text() const;
    [[nodiscard]] std::string normalized_cipher_text() const;

private:
    std::string m_normalized;

    [[nodiscard]] static std::string normalize(const std::string& text);
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

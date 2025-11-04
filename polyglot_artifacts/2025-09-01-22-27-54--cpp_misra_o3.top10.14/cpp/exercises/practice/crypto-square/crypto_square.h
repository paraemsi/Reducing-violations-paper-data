#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

std::string normalize_plain_text(const std::string& text);

std::vector<std::string> plaintext_segments(const std::string& text);

std::string ciphertext(const std::string& text);

std::string normalize_ciphertext(const std::string& text);

class cipher {
public:
    explicit cipher(std::string text);

    [[nodiscard]] std::string normalized_plain_text() const;
    [[nodiscard]] std::string cipher_text() const;
    [[nodiscard]] std::string normalized_cipher_text() const;

private:
    std::string m_text;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

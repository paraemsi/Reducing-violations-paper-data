#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);
    std::string normalized_plain_text() const;
    std::vector<std::string> plaintext_segments() const;
    std::string ciphertext() const;
    std::string normalized_cipher_text() const;

private:
    std::string m_text;
};

// Free-function facade
std::string normalized_plain_text(const std::string& text);
std::vector<std::string> plaintext_segments(const std::string& text);
std::string ciphertext(const std::string& text);
std::string normalized_cipher_text(const std::string& text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

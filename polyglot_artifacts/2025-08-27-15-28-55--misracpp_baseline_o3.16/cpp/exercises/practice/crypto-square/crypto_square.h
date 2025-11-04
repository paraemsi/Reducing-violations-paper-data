#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

std::string normalize_plain_text(const std::string& input);
std::vector<std::string> plaintext_segments(const std::string& input);
std::string ciphertext(const std::string& input);
std::string normalize_cipher_text(const std::string& input);

class cipher {
public:
    explicit cipher(const std::string& input);

    std::string normalize_plain_text() const;
    std::vector<std::string> plaintext_segments() const;
    std::string ciphertext() const;
    std::string normalized_cipher_text() const;

private:
    std::string text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

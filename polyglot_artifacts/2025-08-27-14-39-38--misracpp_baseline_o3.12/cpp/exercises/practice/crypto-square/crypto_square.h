#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

std::string normalize_plain_text(const std::string &text);

std::vector<std::string> plaintext_segments(const std::string &text);

std::string cipher_text(const std::string &text);

std::string normalize_cipher_text(const std::string &text);

// Object-oriented interface expected by the tests
class cipher {
public:
    explicit cipher(const std::string &text);

    std::string normalized_plain_text() const;
    std::size_t size() const;
    std::vector<std::string> plaintext_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string input_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

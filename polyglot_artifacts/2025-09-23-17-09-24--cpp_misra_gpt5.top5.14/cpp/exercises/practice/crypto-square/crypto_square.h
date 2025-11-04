#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

// Remove spaces/punctuation and convert to lowercase.
std::string normalize_plain_text(const std::string& input);

// Encoded text with no spaces (read column-wise).
std::string cipher_text(const std::string& input);
std::string ciphertext(const std::string& input);

// Encoded text split into c chunks of length r, separated by single spaces.
// Each of the last n chunks is padded with a trailing space as needed.
std::string normalized_cipher_text(const std::string& input);

// Object-oriented API compatible with tests.
class cipher {
public:
    explicit cipher(const char* input);
    explicit cipher(const std::string& input);
    std::string normalize_plain_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string ciphertext() const;
    std::string normalized_cipher_text() const;

private:
    std::string input_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

// Normalize the input by down-casing and stripping non-alphanumerics
std::string normalize_text(std::string_view text);

// Side length of the crypto square
std::size_t square_size(std::string_view text);

// Plain-text segments placed row-wise into the square
std::vector<std::string> plain_text_segments(std::string_view text);

// Cipher text read column-wise (chunks separated by spaces)
std::string cipher_text(std::string_view text);

// Crypto-square cipher class
class cipher {
public:
    explicit cipher(std::string_view text);

    std::string normalize_plain_text() const;
    std::size_t size() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string  normalized_;
    std::size_t  columns_{0};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

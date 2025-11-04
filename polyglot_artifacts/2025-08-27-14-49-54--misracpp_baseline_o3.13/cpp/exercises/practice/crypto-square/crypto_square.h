#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <string>
#include <vector>

namespace crypto_square {

std::string encode(const std::string& input);

class cipher {
public:
    explicit cipher(const std::string& input);

    std::string normalize_plain_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string normalized_;
    std::size_t rows_{0};
    std::size_t cols_{0};
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

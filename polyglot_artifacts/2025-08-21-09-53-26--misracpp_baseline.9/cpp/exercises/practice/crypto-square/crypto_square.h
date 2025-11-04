#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    std::string normalized_cipher_text() const;
private:
    std::string normalized_;
    std::vector<std::string> rectangle_;
    std::size_t rows_{0};
    std::size_t cols_{0};
    void build_rectangle();
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

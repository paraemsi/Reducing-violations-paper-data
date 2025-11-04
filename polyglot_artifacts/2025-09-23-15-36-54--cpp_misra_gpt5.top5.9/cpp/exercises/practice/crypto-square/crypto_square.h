#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);
    std::string normalized_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string normalized_;
    static std::pair<std::size_t, std::size_t> dimensions(std::size_t length);
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

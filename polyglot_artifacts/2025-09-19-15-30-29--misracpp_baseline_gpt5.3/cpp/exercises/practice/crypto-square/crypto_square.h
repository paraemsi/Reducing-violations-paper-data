#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    std::string normalize_plain_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    static std::string normalize(const std::string& text);
    std::size_t size() const noexcept;  // number of columns
    std::size_t rows() const noexcept;  // number of rows
    std::string normalized_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

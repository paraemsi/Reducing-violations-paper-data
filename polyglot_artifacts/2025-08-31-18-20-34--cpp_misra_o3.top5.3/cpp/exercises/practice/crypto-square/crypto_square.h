#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>
#include <utility>

namespace crypto_square {

class cipher final
{
public:
    explicit cipher(const std::string& text);

    [[nodiscard]] std::string normalize_plain_text() const;
    [[nodiscard]] std::vector<std::string> plain_text_segments() const;
    [[nodiscard]] std::string cipher_text() const;
    [[nodiscard]] std::string normalized_cipher_text() const;

private:
    static std::string normalize(const std::string& text);
    [[nodiscard]] std::pair<std::size_t, std::size_t> rectangle_dimensions() const;

    std::string normalized_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

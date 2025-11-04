#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <string>
#include <string_view>
#include <vector>
#include <cstddef>

namespace crypto_square {

class cipher {
public:
    explicit cipher(std::string_view text);

    std::string normalize_plain_text() const;
    std::size_t size() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string m_input;
};

std::string normalize_plain_text(std::string_view text);
std::size_t size(std::string_view text);
std::vector<std::string> plain_text_segments(std::string_view text);
std::string cipher_text(std::string_view text);
std::string normalized_cipher_text(std::string_view text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

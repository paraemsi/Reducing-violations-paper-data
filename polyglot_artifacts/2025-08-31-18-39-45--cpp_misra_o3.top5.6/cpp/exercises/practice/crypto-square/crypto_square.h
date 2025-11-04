#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace crypto_square {

class cipher_impl;

class cipher
{
public:
    explicit cipher(const std::string& text);

    auto normalize_plain_text() const -> std::string;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::shared_ptr<cipher_impl> pimpl_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

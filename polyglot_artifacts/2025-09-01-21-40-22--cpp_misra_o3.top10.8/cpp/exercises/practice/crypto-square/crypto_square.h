#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

auto normalize_plain_text(const std::string &plain_text) -> std::string;

auto square_size(const std::string &plain_text) -> std::size_t;

auto plain_text_segments(const std::string &plain_text) -> std::vector<std::string>;

auto cipher_text(const std::string &plain_text) -> std::string;

auto normalized_cipher_text(const std::string &plain_text) -> std::string;

/*------------------------------------------------------------------------------*
 * Class interface required by the test-suite                                   *
 *------------------------------------------------------------------------------*/
class cipher
{
public:
    explicit cipher(const std::string &text);

    auto normalize_plain_text() const -> std::string;
    auto size() const -> std::size_t;
    auto plain_text_segments() const -> std::vector<std::string>;
    auto cipher_text() const -> std::string;
    auto normalized_cipher_text() const -> std::string;

private:
    std::string  normalized_{};
    std::size_t  columns_{ static_cast<std::size_t>(0) };
    std::size_t  rows_{ static_cast<std::size_t>(0) };
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

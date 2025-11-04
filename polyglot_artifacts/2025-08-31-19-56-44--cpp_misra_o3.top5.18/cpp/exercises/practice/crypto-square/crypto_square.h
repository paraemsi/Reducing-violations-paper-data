#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>     // for std::size_t
#include <cstdint>

namespace crypto_square {

auto normalize_plain_text(const std::string & text) -> std::string;

auto square_size(const std::string & text) -> std::size_t;

auto plain_text_segments(const std::string & text) -> std::vector<std::string>;

auto cipher_text(const std::string & text) -> std::string;

auto normalized_cipher_text(const std::string & text) -> std::string;

/* ------------------------------------------------------------------ */
/* façade object expected by the unit tests                           */
class cipher
{
public:
    explicit cipher(const std::string & text);

    [[nodiscard]] auto normalized_cipher_text() const -> std::string;

private:
    std::string m_text;
};

auto cipher(const std::string & text) -> cipher;


}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

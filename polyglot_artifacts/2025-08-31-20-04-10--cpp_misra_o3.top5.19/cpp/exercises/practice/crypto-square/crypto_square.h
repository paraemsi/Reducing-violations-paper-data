#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>

namespace crypto_square {

    using index_t = std::size_t;

    auto normalize_plain_text(const std::string &text) -> std::string;
    auto size(const std::string &text) -> index_t;
    auto plain_text_segments(const std::string &text) -> std::vector<std::string>;
    auto cipher_text(const std::string &text) -> std::string;
    auto normalize_cipher_text(const std::string &text) -> std::string;

    // O-O façade used by the tests
    struct cipher
    {
        explicit cipher(const std::string &source);

        [[nodiscard]] auto size() const -> index_t;
        [[nodiscard]] auto normalized_plain_text() const -> std::string;
        [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>;
        [[nodiscard]] auto cipher_text() const -> std::string;
        [[nodiscard]] auto normalized_cipher_text() const -> std::string;

    private:
        std::string m_source {};
    };

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

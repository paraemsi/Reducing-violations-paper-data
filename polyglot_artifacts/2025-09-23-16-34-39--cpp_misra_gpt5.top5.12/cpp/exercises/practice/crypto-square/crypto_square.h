#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string& text);

    std::string normalize_plain_text() const;
    std::vector<std::string> plaintext_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string m_normalized;
    std::size_t m_rows;
    std::size_t m_cols;

    static std::string normalize(const std::string& text);
    static void compute_dimensions(std::size_t length, std::size_t& rows_out, std::size_t& cols_out);
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

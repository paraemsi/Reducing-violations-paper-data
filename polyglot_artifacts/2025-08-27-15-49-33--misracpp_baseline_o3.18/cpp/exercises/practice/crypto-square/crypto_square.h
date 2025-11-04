#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>

namespace crypto_square {

    std::string normalize_plaintext(std::string_view text);
    std::size_t size(std::string_view text);
    std::vector<std::string> plaintext_segments(std::string_view text);
    std::string ciphertext(std::string_view text);
    std::string normalized_cipher_text(std::string_view text);

    // A convenience wrapper that allows the fluent syntax:
    // crypto_square::cipher("some text").normalized_cipher_text();
    class cipher {
    public:
        explicit cipher(std::string_view text);

        std::string normalize_plaintext() const;
        std::size_t size() const;
        std::vector<std::string> plaintext_segments() const;
        std::string ciphertext() const;
        std::string normalized_cipher_text() const;

    private:
        std::string plain_;
    };

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

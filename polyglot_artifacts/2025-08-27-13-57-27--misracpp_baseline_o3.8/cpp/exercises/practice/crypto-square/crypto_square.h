#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

class cipher {
public:
    explicit cipher(const std::string &input);

    [[nodiscard]] std::string normalize_plain_text() const;
    [[nodiscard]] std::vector<std::string> plaintext_segments() const;
    [[nodiscard]] std::string ciphertext() const;
    [[nodiscard]] std::string normalized_cipher_text() const;

private:
    std::string input_;
};

/* -------------------------------------------------------------------------
   Free-function helpers – provide the same operations without instantiating
   a cipher object.  These mirror the member functions and forward to the
   same implementations found in crypto_square.cpp.
   ------------------------------------------------------------------------- */
[[nodiscard]] std::string normalize_plain_text(const std::string &text);
[[nodiscard]] std::vector<std::string> plaintext_segments(const std::string &text);
[[nodiscard]] std::string ciphertext(const std::string &text);
[[nodiscard]] std::string normalized_cipher_text(const std::string &text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

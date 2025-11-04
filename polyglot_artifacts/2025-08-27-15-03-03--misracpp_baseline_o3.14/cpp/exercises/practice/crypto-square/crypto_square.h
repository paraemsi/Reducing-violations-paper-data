#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

// Remove spaces/punctuation and convert to lowercase
std::string normalize_plain_text(const std::string& input);

 // Break normalized text into rows of equal length (as square as possible)
std::vector<std::string> plain_text_segments(const std::string& input);

// Cipher text with no spacing (column-wise read of the rectangle)
std::string cipher_text(const std::string& input);

// Cipher text grouped into equal chunks (one chunk per original column)
std::string normalized_cipher_text(const std::string& input);

// ------------------------------------------------------------------
// OO wrapper expected by the tests
// ------------------------------------------------------------------
class cipher {
public:
    explicit cipher(const std::string& text);

    std::string normalize_plain_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;                 // no-spacing version
    std::string normalized_cipher_text() const;      // spaced / grouped

private:
    std::string text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

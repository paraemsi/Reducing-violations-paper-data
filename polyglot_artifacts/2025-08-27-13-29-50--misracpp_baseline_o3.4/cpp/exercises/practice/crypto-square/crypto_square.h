#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>

namespace crypto_square {

// Normalize the input: remove non-alphanumeric chars and lowercase everything
std::string normalize_plain_text(const std::string &input);

// Break the normalized string into row segments (r rows, c columns)
std::vector<std::string> plain_text_segments(const std::string &input);

// Read down the columns (no spaces, no padding)
std::string cipher_text(const std::string &input);

// Read down the columns and return text in padded chunks separated by spaces
std::string normalized_cipher_text(const std::string &input);

// Object-oriented façade expected by the tests ------------------------------
class cipher {
public:
    explicit cipher(const std::string &text) : text_{text} {}

    std::string normalize_plain_text() const {
        return crypto_square::normalize_plain_text(text_);
    }

    std::vector<std::string> plain_text_segments() const {
        return crypto_square::plain_text_segments(text_);
    }

    std::string cipher_text() const {
        return crypto_square::cipher_text(text_);
    }

    std::string normalized_cipher_text() const {
        return crypto_square::normalized_cipher_text(text_);
    }

private:
    std::string text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

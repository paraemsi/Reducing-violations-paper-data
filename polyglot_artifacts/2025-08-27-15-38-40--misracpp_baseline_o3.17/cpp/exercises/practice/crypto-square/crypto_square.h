#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <vector>
#include <cstddef>

namespace crypto_square {

std::string normalize_plain_text(const std::string& input);
std::size_t square_size(const std::string& input);
std::size_t size(const std::string& input);  // alias kept for backward-compatibility with tests
std::vector<std::string> plain_text_segments(const std::string& input);
std::string cipher_text(const std::string& input);
std::string normalized_cipher_text(const std::string& input);

class cipher {
public:
    explicit cipher(const std::string& text) : text_{text} {}

    std::string normalized_cipher_text() const {
        return ::crypto_square::normalized_cipher_text(text_);
    }

    std::size_t size() const {
        return ::crypto_square::size(text_);
    }

    std::vector<std::string> plain_text_segments() const {
        return ::crypto_square::plain_text_segments(text_);
    }

    std::string cipher_text() const {
        // fully-qualify to call the free function, not this method
        return ::crypto_square::cipher_text(text_);
    }

private:
    std::string text_;
};

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

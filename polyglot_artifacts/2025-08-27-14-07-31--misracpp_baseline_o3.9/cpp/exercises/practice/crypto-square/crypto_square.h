#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>
#include <string_view>
#include <vector>
#include <cstddef>

namespace crypto_square {

class cipher {
public:
    explicit cipher(std::string_view text);

    std::string normalize_plain_text() const;
    std::vector<std::string> plain_text_segments() const;
    std::string cipher_text() const;
    std::string normalized_cipher_text() const;

private:
    std::string norm_;
    std::size_t rows_{0};
    std::size_t cols_{0};
    std::vector<std::string> segments_;
};

// Step-1: normalize – keep only alpha-numeric and lower-case letters
std::string normalize_plain_text(std::string_view text);

// Step-2: break the normalized text into row segments of equal length
std::vector<std::string> plain_text_segments(std::string_view text);

// Step-3: read the rectangle column-wise (no spaces)
std::string cipher_text(std::string_view text);

// Step-4: same as cipher_text but returned in r-length chunks separated by
// single spaces and padded with spaces when required.
std::string normalized_cipher_text(std::string_view text);

}  // namespace crypto_square

#endif // CRYPTO_SQUARE_H

#include "crypto_square.h"

#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {
    cipher::cipher(std::string plain_text) : plain_text_(std::move(plain_text)) {}

    std::string cipher::normalize_plain_text() const {
        std::string normalized_text;
        for (const char c : plain_text_) {
            if (std::isalnum(static_cast<unsigned char>(c))) {
                normalized_text += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }
        return normalized_text;
    }

    std::vector<std::string> cipher::plain_text_segments() const {
        const std::string normalized_text = normalize_plain_text();
        if (normalized_text.empty()) {
            return {};
        }

        const std::size_t length = normalized_text.length();
        std::size_t c = 0;
        while ((c * c) < length) {
            c += 1;
        }

        std::vector<std::string> segments;
        for (std::size_t i = 0; i < length; i += c) {
            segments.push_back(normalized_text.substr(i, c));
        }

        return segments;
    }

    std::string cipher::cipher_text() const {
        const std::string normalized_text = normalize_plain_text();
        const std::size_t length = normalized_text.length();

        if (length == 0) {
            return "";
        }

        std::size_t c = 0;
        while ((c * c) < length) {
            c += 1;
        }
        const std::size_t r = ((length + c) - 1) / c;

        std::string encoded_text;
        encoded_text.reserve(length);

        for (std::size_t col = 0; col < c; ++col) {
            for (std::size_t row = 0; row < r; ++row) {
                const std::size_t index = ((row * c) + col);
                if (index < length) {
                    encoded_text += normalized_text.at(index);
                }
            }
        }

        return encoded_text;
    }

    std::string cipher::normalized_cipher_text() const {
        const std::string normalized_text = normalize_plain_text();
        const std::size_t length = normalized_text.length();

        if (length == 0) {
            return "";
        }

        std::size_t c = 0;
        while ((c * c) < length) {
            c += 1;
        }
        const std::size_t r = ((length + c) - 1) / c;

        std::string padded_text = normalized_text;
        padded_text.resize((r * c), ' ');

        std::vector<std::string> chunks;
        chunks.reserve(c);
        for (std::size_t col = 0; col < c; ++col) {
            std::string chunk;
            chunk.reserve(r);
            for (std::size_t row = 0; row < r; ++row) {
                chunk += padded_text.at(((row * c) + col));
            }
            chunks.push_back(chunk);
        }
        
        std::string result;
        if (!chunks.empty()) {
            result.reserve((((c * r) + c) - 1));
            result.append(chunks[0]);
            for (std::size_t i = 1; i < c; ++i) {
                result.append(" ");
                result.append(chunks[i]);
            }
        }
        return result;
    }

}  // namespace crypto_square

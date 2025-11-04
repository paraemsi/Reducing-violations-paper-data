#include "crypto_square.h"

#include <cmath>
#include <sstream>
#include <cctype>
// <algorithm> no longer required

namespace crypto_square {

// Compute rectangle dimensions (rows, columns) satisfying the rules
static auto dimensions(std::size_t length) -> std::pair<std::size_t, std::size_t>
{
    if (length == static_cast<std::size_t>(0U)) {
        return {0U, 0U};
    }

    const double root { std::sqrt(static_cast<double>(length)) };
    const std::size_t columns { static_cast<std::size_t>(std::ceil(root)) };
    const std::size_t rows { (length + columns - static_cast<std::size_t>(1U)) / columns };
    return {rows, columns};
}

auto normalize_plain_text(std::string const& input) -> std::string
{
    std::string result {};
    result.reserve(input.size());

    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch)) != 0) {
            const char lower_ch { static_cast<char>(std::tolower(static_cast<unsigned char>(ch))) };
            result.push_back(lower_ch);
        } else {
            /* ignore non-alphanumeric characters */
        }
    }

    return result;
}

auto plaintext_segments(std::string const& input) -> std::vector<std::string>
{
    const std::string text { normalize_plain_text(input) };
    const std::size_t length { text.size() };

    auto [rows, columns] = dimensions(length);

    std::vector<std::string> segments {};
    segments.reserve(rows);

    for (std::size_t i { 0U }; i < length; i += columns) {
        segments.emplace_back(text.substr(i, columns));
    }

    return segments;
}

auto cipher_text(std::string const& input) -> std::string
{
    const std::string text { normalize_plain_text(input) };
    const std::size_t length { text.size() };

    auto [rows, columns] = dimensions(length);
    if ((rows == static_cast<std::size_t>(0U)) || (columns == static_cast<std::size_t>(0U))) {
        return std::string {};
    }

    std::string result {};
    result.reserve(length);

    for (std::size_t column { 0U }; column < columns; ++column) {
        for (std::size_t row { 0U }; row < rows; ++row) {
            const std::size_t index { (row * columns) + column };
            if (index < length) {
                result.push_back(text[index]);
            }
        }
    }

    return result;
}

auto normalized_cipher_text(std::string const& input) -> std::string
{
    const std::string text { normalize_plain_text(input) };
    const std::size_t length { text.size() };

    auto [rows, columns] = dimensions(length);
    if ((rows == static_cast<std::size_t>(0U)) || (columns == static_cast<std::size_t>(0U))) {
        return std::string {};
    }

    std::ostringstream oss {};

    for (std::size_t column { 0U }; column < columns; ++column) {
        if (column > static_cast<std::size_t>(0U)) {
            oss << ' ';
        }

        for (std::size_t row { 0U }; row < rows; ++row) {
            const std::size_t index { (row * columns) + column };
            if (index < length) {
                oss << text[index];
            } else {
                oss << ' ';
            }
        }
    }

    return oss.str();
}

//------------------------------------------------------------------
//  cipher class member function definitions
//------------------------------------------------------------------
cipher::cipher(std::string const& input) : text_(input) {}

auto cipher::normalize_plain_text() const -> std::string
{
    return ::crypto_square::normalize_plain_text(text_);
}

auto cipher::plaintext_segments() const -> std::vector<std::string>
{
    return ::crypto_square::plaintext_segments(text_);
}

auto cipher::cipher_text() const -> std::string
{
    return ::crypto_square::cipher_text(text_);
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return ::crypto_square::normalized_cipher_text(text_);
}

}  // namespace crypto_square

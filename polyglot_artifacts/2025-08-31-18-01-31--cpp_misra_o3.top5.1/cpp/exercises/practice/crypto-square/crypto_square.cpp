#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <string>
#include <string_view>

namespace crypto_square {

auto cipher_text(std::string_view input) -> std::string
{
    /* Normalise input: keep alphanumerics, make lower-case */
    std::string normalised {};
    normalised.reserve(input.size());

    for (char ch : input) {
        if ((std::isalnum(static_cast<unsigned char>(ch))) != 0) {
            normalised.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }

    const std::uint32_t len { static_cast<std::uint32_t>(normalised.size()) };
    if (len == static_cast<std::uint32_t>(0U)) {
        return std::string {};
    }

    /* Determine rectangle dimensions */
    const double root { std::sqrt(static_cast<double>(len)) };
    std::uint32_t col { static_cast<std::uint32_t>(std::ceil(root)) };
    std::uint32_t row { static_cast<std::uint32_t>(std::floor(root)) };

    if (((row * col) < len)) {
        ++row;
    }

    /* Build cipher text column-wise, adding spaces between chunks */
    std::string output {};
    output.reserve(len + col); /* space characters between chunks */

    for (std::uint32_t c { static_cast<std::uint32_t>(0U) }; c < col; ++c) {
        if (c != static_cast<std::uint32_t>(0U)) {
            output.push_back(' ');
        }

        for (std::uint32_t r { static_cast<std::uint32_t>(0U) }; r < row; ++r) {
            const std::uint32_t index { (r * col) + c };
            if (index < len) {
                output.push_back(normalised[index]);
            }
        }
    }

    return output;
}

/* -------------------------------------------------------------------------
 *  Implementation of crypto_square::cipher
 * ---------------------------------------------------------------------- */
namespace {

/* Remove non-alphanumeric characters and force lower-case */
auto normalise(std::string_view input) -> std::string
{
    std::string result {};
    result.reserve(input.size());

    for (char ch : input) {
        if ((std::isalnum(static_cast<unsigned char>(ch))) != 0) {
            result.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return result;
}

/* Calculate rectangle dimensions that satisfy the puzzle rules */
struct dimensions
{
    std::uint32_t row {};
    std::uint32_t col {};
};

auto calc_dimensions(std::uint32_t len) -> dimensions
{
    if (len == static_cast<std::uint32_t>(0U)) {
        return { 0U, 0U };
    }

    const double root { std::sqrt(static_cast<double>(len)) };
    std::uint32_t col { static_cast<std::uint32_t>(std::ceil(root)) };
    std::uint32_t row { static_cast<std::uint32_t>(std::floor(root)) };

    if (((row * col) < len)) {
        ++row;
    }

    return { row, col };
}

}   /* unnamed namespace */

cipher::cipher(std::string_view input)
    : m_normalised { normalise(input) }
{
}

auto cipher::cipher_text() const -> std::string
{
    const std::uint32_t len { static_cast<std::uint32_t>(m_normalised.size()) };
    const auto dims { calc_dimensions(len) };

    if (len == static_cast<std::uint32_t>(0U)) {
        return std::string {};
    }

    std::string output {};
    output.reserve(len + dims.col);

    for (std::uint32_t c { static_cast<std::uint32_t>(0U) }; c < dims.col; ++c) {
        if (c != static_cast<std::uint32_t>(0U)) {
            output.push_back(' ');
        }

        for (std::uint32_t r { static_cast<std::uint32_t>(0U) }; r < dims.row; ++r) {
            const std::uint32_t index { (r * dims.col) + c };
            if (index < len) {
                output.push_back(m_normalised[index]);
            } else {
                output.push_back(' ');
            }
        }
    }

    return output;
}

auto cipher::normalized_cipher_text() const -> std::string
{
    const std::uint32_t len { static_cast<std::uint32_t>(m_normalised.size()) };
    const auto dims { calc_dimensions(len) };

    if (len == static_cast<std::uint32_t>(0U)) {
        return std::string {};
    }

    std::string output {};
    output.reserve(len);

    for (std::uint32_t c { static_cast<std::uint32_t>(0U) }; c < dims.col; ++c) {
        for (std::uint32_t r { static_cast<std::uint32_t>(0U) }; r < dims.row; ++r) {
            const std::uint32_t index { (r * dims.col) + c };
            if (index < len) {
                output.push_back(m_normalised[index]);
            }
        }
    }

    return output;
}

}  // namespace crypto_square

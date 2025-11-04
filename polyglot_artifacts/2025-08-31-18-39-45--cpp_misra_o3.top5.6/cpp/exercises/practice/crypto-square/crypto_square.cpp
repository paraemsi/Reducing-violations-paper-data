#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <vector>
#include <memory>

namespace crypto_square {

/* **************************
 *  cipher implementation   *
 * **************************/
class cipher_impl
{
public:
    explicit cipher_impl(const std::string& text)
    {
        normalize(text);
        calculate_dimensions();
    }

    [[nodiscard]] auto normalize_plain_text() const -> std::string
    {
        return normalized_;
    }

    [[nodiscard]] auto plain_text_segments() const -> std::vector<std::string>
    {
        std::vector<std::string> segments{};
        segments.reserve(rows_);

        for (std::uint32_t r{ static_cast<std::uint32_t>(0U) }; r < rows_; ++r)
        {
            std::string segment{};
            segment.reserve(cols_);

            for (std::uint32_t c{ static_cast<std::uint32_t>(0U) }; c < cols_; ++c)
            {
                const std::uint32_t index{ ((r * cols_) + c) };
                if (index < static_cast<std::uint32_t>(normalized_.size()))
                {
                    segment.push_back(normalized_[index]);
                }
                else
                {
                    segment.push_back(' ');
                }
            }

            segments.push_back(segment);
        }

        return segments;
    }

    [[nodiscard]] auto cipher_text() const -> std::string
    {
        std::string output{};
        output.reserve(normalized_.size());

        for (std::uint32_t c{ static_cast<std::uint32_t>(0U) }; c < cols_; ++c)
        {
            for (std::uint32_t r{ static_cast<std::uint32_t>(0U) }; r < rows_; ++r)
            {
                const std::uint32_t index{ ((r * cols_) + c) };
                if (index < static_cast<std::uint32_t>(normalized_.size()))
                {
                    output.push_back(normalized_[index]);
                }
            }
        }

        return output;
    }

    [[nodiscard]] auto normalized_cipher_text() const -> std::string
    {
        if (normalized_.empty())
        {
            return std::string{};
        }

        std::string output{};
        output.reserve(normalized_.size() + cols_ - static_cast<std::uint32_t>(1U));

        for (std::uint32_t c{ static_cast<std::uint32_t>(0U) }; c < cols_; ++c)
        {
            for (std::uint32_t r{ static_cast<std::uint32_t>(0U) }; r < rows_; ++r)
            {
                const std::uint32_t index{ ((r * cols_) + c) };
                if (index < static_cast<std::uint32_t>(normalized_.size()))
                {
                    output.push_back(normalized_[index]);
                }
                else
                {
                    output.push_back(' ');
                }
            }

            if (c < (cols_ - static_cast<std::uint32_t>(1U)))
            {
                output.push_back(' ');
            }
        }

        return output;
    }

private:
    void normalize(const std::string& text)
    {
        normalized_.reserve(text.size());

        for (char ch : text)
        {
            const int ch_value{ static_cast<int>(static_cast<std::uint8_t>(ch)) };

            if ((std::isalnum(ch_value)) != 0)
            {
                normalized_.push_back(static_cast<char>(std::tolower(ch_value)));
            }
        }
    }

    void calculate_dimensions()
    {
        const std::uint32_t len{ static_cast<std::uint32_t>(normalized_.size()) };

        if (len == static_cast<std::uint32_t>(0U))
        {
            rows_ = static_cast<std::uint32_t>(0U);
            cols_ = static_cast<std::uint32_t>(0U);
            return;
        }

        const double sqrt_len{ std::sqrt(static_cast<double>(len)) };
        rows_ = static_cast<std::uint32_t>(std::floor(sqrt_len));
        cols_ = static_cast<std::uint32_t>(std::ceil(sqrt_len));

        if (((rows_ * cols_) < len))
        {
            ++rows_;
        }
    }

    std::string   normalized_{};
    std::uint32_t rows_{ static_cast<std::uint32_t>(0U) };
    std::uint32_t cols_{ static_cast<std::uint32_t>(0U) };
};

/* Glue wrapper that maps the public cipher interface to the internal
 * implementation, while keeping all data private.
 */
cipher::cipher(const std::string& text) : pimpl_{ std::make_shared<cipher_impl>(text) } {}

auto cipher::normalize_plain_text() const -> std::string
{
    return pimpl_->normalize_plain_text();
}

auto cipher::plain_text_segments() const -> std::vector<std::string>
{
    return pimpl_->plain_text_segments();
}

auto cipher::cipher_text() const -> std::string
{
    return pimpl_->cipher_text();
}

auto cipher::normalized_cipher_text() const -> std::string
{
    return pimpl_->normalized_cipher_text();
}

}  // namespace crypto_square

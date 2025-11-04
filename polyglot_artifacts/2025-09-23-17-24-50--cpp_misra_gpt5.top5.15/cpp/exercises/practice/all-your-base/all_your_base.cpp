#include "all_your_base.h"

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

namespace {

// Internal implementation shared by both overloads.
// Converts a number represented by `digits` in base `input_base`
// into digits in base `output_base`.
auto convert_impl(const std::vector<std::uint32_t>& digits,
                  std::uint32_t input_base,
                  std::uint32_t output_base) -> std::vector<std::uint32_t>
{
    if ((input_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if ((output_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Empty input -> empty output (consistent with typical task expectations).
    if ((digits.empty())) {
        return {};
    }

    // Validate digits and detect all-zero case.
    bool all_zero = true;
    for (std::uint32_t d : digits) {
        if ((d >= input_base)) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if ((d != static_cast<std::uint32_t>(0U))) {
            all_zero = false;
        }
    }

    if ((all_zero)) {
        return {};
    }

    // Accumulator in output_base representation (most-significant at index 0).
    std::vector<std::uint32_t> result{};

    // Helpers: multiply current result by input_base, then add the next digit.
    auto multiply_in_place = [](std::vector<std::uint32_t>& res,
                                std::uint32_t factor,
                                std::uint32_t out_base) -> void {
        std::uint64_t carry = static_cast<std::uint64_t>(0ULL);

        std::size_t idx = res.size();
        while ((idx > static_cast<std::size_t>(0U))) {
            idx = (idx - static_cast<std::size_t>(1U));
            const std::uint64_t temp =
                (static_cast<std::uint64_t>(res[idx]) * static_cast<std::uint64_t>(factor)) + carry;

            const std::uint64_t out_base_u64 = static_cast<std::uint64_t>(out_base);
            const std::uint64_t rem = (temp % out_base_u64);
            res[idx] = static_cast<std::uint32_t>(rem);  // safe: rem < out_base <= 2^32-1

            carry = (temp / out_base_u64);
        }

        const std::uint64_t out_base_u64 = static_cast<std::uint64_t>(out_base);
        while ((carry > static_cast<std::uint64_t>(0ULL))) {
            const std::uint64_t rem = (carry % out_base_u64);
            res.insert(res.begin(), static_cast<std::uint32_t>(rem));  // safe: rem < out_base
            carry = (carry / out_base_u64);
        }
    };

    auto add_in_place = [](std::vector<std::uint32_t>& res,
                           std::uint32_t addend,
                           std::uint32_t out_base) -> void {
        std::uint64_t carry = static_cast<std::uint64_t>(addend);

        std::size_t idx = res.size();
        while ((idx > static_cast<std::size_t>(0U))) {
            idx = (idx - static_cast<std::size_t>(1U));
            const std::uint64_t sum =
                static_cast<std::uint64_t>(res[idx]) + carry;

            const std::uint64_t out_base_u64 = static_cast<std::uint64_t>(out_base);
            const std::uint64_t rem = (sum % out_base_u64);
            res[idx] = static_cast<std::uint32_t>(rem);  // safe: rem < out_base

            carry = (sum / out_base_u64);
        }

        const std::uint64_t out_base_u64 = static_cast<std::uint64_t>(out_base);
        while ((carry > static_cast<std::uint64_t>(0ULL))) {
            const std::uint64_t rem = (carry % out_base_u64);
            res.insert(res.begin(), static_cast<std::uint32_t>(rem));  // safe: rem < out_base
            carry = (carry / out_base_u64);
        }
    };

    for (std::uint32_t d : digits) {
        multiply_in_place(result, input_base, output_base);
        add_in_place(result, d, output_base);
    }

    // No leading zeros will be present here (except the all-zero case handled earlier).
    return result;
}

} // namespace

 // Overload: (digits, input_base, output_base)
auto convert(const std::vector<std::uint32_t>& digits,
             std::uint32_t input_base,
             std::uint32_t output_base) -> std::vector<std::uint32_t>
{
    return convert_impl(digits, input_base, output_base);
}

// Overload: (input_base, digits, output_base)
auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>
{
    return convert_impl(digits, input_base, output_base);
}

}  // namespace all_your_base

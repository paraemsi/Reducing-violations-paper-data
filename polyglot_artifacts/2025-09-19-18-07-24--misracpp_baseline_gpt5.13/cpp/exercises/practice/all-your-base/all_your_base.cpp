#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    if (digits.empty()) {
        return {};
    }

    // Validate digits and trim leading zeros
    std::vector<unsigned int> src;
    src.reserve(digits.size());
    bool leading = true;
    for (auto d : digits) {
        if (d >= input_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if (leading && d == 0) {
            continue;
        }
        leading = false;
        src.push_back(d);
    }

    if (src.empty()) {
        return {0};
    }

    // Repeated division algorithm to avoid overflow of fixed-size integers
    std::vector<unsigned int> out;
    out.reserve(src.size());
    while (!src.empty()) {
        std::vector<unsigned int> next;
        next.reserve(src.size());
        unsigned long long remainder = 0ULL;
        for (auto d : src) {
            unsigned long long acc = remainder * input_base + d;
            unsigned int q = static_cast<unsigned int>(acc / output_base);
            remainder = static_cast<unsigned int>(acc % output_base);
            if (!next.empty() || q != 0) {
                next.push_back(q);
            }
        }
        out.push_back(static_cast<unsigned int>(remainder));
        src.swap(next);
    }

    std::reverse(out.begin(), out.end());
    return out;
}

}  // namespace all_your_base

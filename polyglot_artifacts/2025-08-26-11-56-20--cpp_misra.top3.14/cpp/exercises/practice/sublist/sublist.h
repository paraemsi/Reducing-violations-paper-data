#pragma once

#include <vector>
#include <cstdint>

namespace sublist {

using index_t = std::uint32_t;

// The test suite expects these exact names and values:
enum class Comparison {
    equal,
    sublist,
    superlist,
    unequal
};

// Provide a non-template, test-facing function for int lists
Comparison sublist(const std::vector<std::int32_t>& a, const std::vector<std::int32_t>& b);

}  // namespace sublist

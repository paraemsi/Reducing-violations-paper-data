#pragma once

#include <vector>
#include <string>

namespace sublist {

enum class Comparison {
    Equal,
    Sublist,
    Superlist,
    Unequal
};

Comparison compare(const std::vector<int>& A, const std::vector<int>& B);
Comparison compare(const std::vector<std::string>& A, const std::vector<std::string>& B);

} // namespace sublist

#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

//  Fixed-width unsigned integer alias used throughout the interface
using uint_t = std::uint32_t;

//  Return the diamond as a collection of lines (no trailing '\n')
std::vector<std::string> make_lines(const char letter);

//  Convenience alias expected by tests
std::vector<std::string> rows(const char letter);

//  Return the diamond as a single '\n'-separated string
std::string make(const char letter);

}  // namespace diamond

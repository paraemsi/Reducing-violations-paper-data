#pragma once

#include <vector>
#include <initializer_list>

namespace sublist {

// Relationship between two sequences
enum class relation { equal, sublist, superlist, unequal };

// Common aliases to improve compatibility with different test suites
using result = relation;
using comparison_result = relation;

// Exercism canonical API: enum used by tests
enum class List_comparison { equal, sublist, superlist, unequal };

// Primary API function expected by tests
List_comparison sublist(const std::vector<int>& a, const std::vector<int>& b);

// Convenience overload to accept brace-initialized lists directly
List_comparison sublist(std::initializer_list<int> a, std::initializer_list<int> b);

/**
 * Classify the relationship between two sequences 'a' and 'b'.
 * Returns one of: relation::equal, relation::sublist, relation::superlist, relation::unequal.
 */
relation classify(const std::vector<int>& a, const std::vector<int>& b);

/* Compatibility wrappers (some test suites expect these names) */
relation compare(const std::vector<int>& a, const std::vector<int>& b);
relation check(const std::vector<int>& a, const std::vector<int>& b);

}  // namespace sublist

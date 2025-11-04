#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>
#include <initializer_list>

namespace sublist {

/*
 * Enumeration describing the relationship between two lists.
 */
enum class Relationship : std::uint8_t
{
    equal,
    sublist,
    superlist,
    unequal
};

 /*
  * Enumeration expected by the exercism test-suite.
  * It mirrors 'Relationship' but preserves the original name.
  */
 enum class List_comparison : std::uint8_t
 {
     equal,
     sublist,
     superlist,
     unequal
 };

 /*
  * Forward declaration of helper for use in sublist() template.
  */
 template <typename T>
 [[nodiscard]] inline auto is_sublist( const std::vector<T>& longer,
                                       const std::vector<T>& shorter ) noexcept -> bool;

 /*
  * Public API expected by the exercism test-suite.
  * Determines how two lists relate in terms of equality / containment.
  */
 template <typename T>
 [[nodiscard]] inline auto sublist( const std::vector<T>& list_a,
                                    const std::vector<T>& list_b ) noexcept -> List_comparison
 {
     if( list_a == list_b )
     {
         return List_comparison::equal;
     }

     if( is_sublist( list_a, list_b ) )
     {
         return List_comparison::superlist;
     }

     if( is_sublist( list_b, list_a ) )
     {
         return List_comparison::sublist;
     }

     return List_comparison::unequal;
 }

 /*
  * Convenience overload that accepts brace-initialiser lists so the
  * test-suite can write:
  *     sublist::sublist({1, 2, 3}, {2, 3})
  * without having to construct std::vector objects explicitly.
  */
 template <typename T = std::int32_t>
 [[nodiscard]] inline auto sublist( std::initializer_list<T> list_a,
                                    std::initializer_list<T> list_b ) noexcept -> List_comparison
 {
     const std::vector<T> vec_a{ list_a };
     const std::vector<T> vec_b{ list_b };
     return sublist( vec_a, vec_b );
 }

/*
 * Check whether `shorter` is a contiguous sub-sequence of `longer`.
 */
template <typename T>
[[nodiscard]] inline auto is_sublist( const std::vector<T>& longer,
                                      const std::vector<T>& shorter ) noexcept -> bool
{
    using size_type = typename std::vector<T>::size_type;

    const size_type longer_size  = longer.size();
    const size_type shorter_size = shorter.size();

    if( shorter_size == static_cast<size_type>(0U) )
    {
        return true;
    }

    if( shorter_size > longer_size )
    {
        return false;
    }

    for( size_type i = static_cast<size_type>(0U);
         ( i + shorter_size ) <= longer_size;
         ++i )
    {
        bool match = true;

        for( size_type j = static_cast<size_type>(0U); j < shorter_size; ++j )
        {
            if( !( ( longer.at( i + j ) == shorter.at( j ) ) ) )
            {
                match = false;
                break;
            }
        }

        if( match )
        {
            return true;
        }
    }

    return false;
}

/*
 * Classify the relationship between lists `list_a` and `list_b`.
 */
template <typename T>
[[nodiscard]] inline auto classify( const std::vector<T>& list_a,
                                    const std::vector<T>& list_b ) noexcept -> Relationship
{
    if( list_a == list_b )
    {
        return Relationship::equal;
    }

    if( is_sublist( list_a, list_b ) )
    {
        return Relationship::superlist;
    }

    if( is_sublist( list_b, list_a ) )
    {
        return Relationship::sublist;
    }

    return Relationship::unequal;
}

}  // namespace sublist

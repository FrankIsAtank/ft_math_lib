#pragma once

// project headers
#include "vector.h"
#include "container/make_array.hpp"

// other headers
#include "error/ft_assert.h"

namespace ft {
namespace math {

// Make a vector containing all zeros
template<class T, std::size_t S>
constexpr vector<T, S> make_zero_vector()
{
    vector<T, S> result;
    for (std::size_t i = 0; i < S; ++i)
    {
        result[i] = 0;
    }
    return result;
}

namespace details {
namespace vector_ns  {

// Copy a vector to a new vector with a different element type
template<class U, class T, std::size_t ... I>
constexpr auto convert_vector(const vector<T, sizeof...(I)>& p_src, std::index_sequence<I...>) -> vector<U, sizeof...(I)> {
    return { static_cast<U>(p_src[I])... };
}

}   // namespace vector_ns
}   // namespace details


// Value-wise constructor
template<class T, std::size_t S>
template<class ... t_args>
constexpr vector<T, S>::vector(const std::enable_if_t<sizeof...(t_args) + 1 == S, T> & p_first, t_args&& ... p_args) noexcept(std::is_nothrow_constructible_v<T>) :
    m_data(ft::base::container::make_array(p_first, std::forward<t_args>(p_args)...))
{
    static_assert(S <= sizeof...(t_args) + 1, "Too many arguments");
    static_assert(S >= sizeof...(t_args) + 1, "Too few arguments");
}


// Value-wise constructor
template<class T, std::size_t S>
template<class ... t_args>
constexpr vector<T, S>::vector(std::enable_if_t<sizeof...(t_args) + 1 == S, T> && p_first, t_args&& ... p_args) noexcept(std::is_nothrow_constructible_v<T>) :
    m_data(ft::base::container::make_array(std::move(p_first), std::forward<t_args>(p_args)...))
{
    static_assert(S <= sizeof...(t_args) + 1, "Too many arguments");
    static_assert(S >= sizeof...(t_args) + 1, "Too few arguments");
}

// Construct from an array of values
template<class T, std::size_t S>
constexpr vector<T, S>::vector(const std::array<T, S> & p_values) :
    m_data(p_values)
{ }


// Construct from an array of values
template<class T, std::size_t S>
constexpr vector<T, S>::vector(std::array<T, S> && p_values) :
    m_data(std::move(p_values))
{ }


// Construct from contiguous data
// p_value must point to an element in an array
//  which is followed by at least S - 1 elements
template<class T, std::size_t S>
constexpr vector<T, S>::vector(const T * p_values)
{
    std::copy(p_values, p_values + S, std::begin(m_data));
}


// Returns a subsection of this vector
// Remove `R` elements, starting with the first `p_offset` and
//  then remove the rest from the end
// Ex. remove<1>(1) will turn [XYZ] into [YZ]
template<class T, std::size_t S>
template<std::size_t R>
constexpr vector<T, S - R> vector<T, S>::demote(const std::size_t p_offset) const
{
    static_assert(R < S);
    FT_ASSERT(R + p_offset < S);

    return { m_data.data() + p_offset };
}


// Make a larger vector and initialize a subsection of it
//  to the values of this vector
template<class T, std::size_t S>
template<std::size_t R>
constexpr vector<T, S + R> vector<T, S>::promote(const std::size_t p_offset) const
{
    FT_ASSERT(p_offset < R);
    vector<T, S + R> result;
    std::copy(begin(), end(), std::begin(result) + p_offset);
    return result;
}


// Convert to another vector of the same size but with a different element type
template<class T, std::size_t S>
template<class U>
constexpr vector<U, S> vector<T, S>::cast() const
{
    return details::vector_ns::convert_vector<U>(*this, std::make_index_sequence<S>());
}


// Mutable reference to an element
template<class T, std::size_t S>
constexpr T & vector<T, S>::operator[](const std::size_t p_index) noexcept {
    return get(p_index);
}


// Mutable reference to an element
template<class T, std::size_t S>
constexpr T & vector<T, S>::get(const std::size_t p_index) noexcept
{
    return m_data[p_index];
}


// Const reference to an element
template<class T, std::size_t S>
constexpr const T & vector<T, S>::operator[](const std::size_t p_index) const noexcept {
    return get(p_index);
}


// Const reference to an element
template<class T, std::size_t S>
constexpr const T & vector<T, S>::get(const std::size_t p_index) const noexcept
{
    return m_data[p_index];
}


// Arithmetic operators
template<class T, std::size_t S>
constexpr vector<T, S> & vector<T, S>::operator-=(const vector & p_other)
{
    for (size_t i = 0; i < S; ++i) {
        get(i) -= p_other.get(i);
    }
    return *this;
}


// Arithmetic operators
template<class T, std::size_t S>
constexpr vector<T, S> & vector<T, S>::operator+=(const vector & p_other)
{
    for (size_t i = 0; i < S; ++i) {
        get(i) += p_other.get(i);
    }
    return *this;
}


// Arithmetic operators
template<class T, std::size_t S>
template<class V>
constexpr vector<T, S> & vector<T, S>::operator*=(const V & p_value)
{
    for (size_t i = 0; i < S; ++i) {
        get(i) *= p_value;
    }
    return *this;
}


// Arithmetic operators
template<class T, std::size_t S>
template<class V>
constexpr vector<T, S> & vector<T, S>::operator/=(const V & p_value)
{
    for (size_t i = 0; i < S; ++i) {
        get(i) /= p_value;
    }
    return *this;
}


// Compare operator
template<class T, std::size_t S>
constexpr bool  vector<T, S>::operator==(const vector & p_other) const
{
    for (std::size_t i = 0; i < S; ++i)
    {
        if (m_data[i] != p_other.m_data[i]) {
            return false;
        }
    }
    return true;
}


// Compare operator
template<class T, std::size_t S>
constexpr bool  vector<T, S>::operator!=(const vector & p_other) const
{
    return operator==(p_other) == false;
}


// Compare this vector with another with the same dimensions
// Returns true if the difference between each element
// is within a rounding error
template<class T, std::size_t S>
constexpr bool vector<T, S>::compare_epsilon(const vector & p_ref, const T p_error) const
{
    const auto minus_error = -p_error;
    for (std::size_t i = 0; i < S; ++i)
    {
        const auto delta = (*this)[i] - p_ref[i];
        if (delta > p_error || delta < minus_error) {
            return false;
        }
    }

    // No difference found
    return true;
}


// Provide an iterator
template<class T, std::size_t S>
constexpr T * vector<T, S>::begin()
{
    return &(m_data.front());
}


// Provide an iterator
template<class T, std::size_t S>
constexpr const T * vector<T, S>::begin() const
{
    return cbegin();
}


// Provide an iterator
template<class T, std::size_t S>
constexpr const T * vector<T, S>::cbegin() const
{
    return &(m_data.front());
}


// Provide an iterator
template<class T, std::size_t S>
constexpr T * vector<T, S>::end()
{
    return std::next(&(m_data.back()));
}


// Provide an iterator
template<class T, std::size_t S>
constexpr const T * vector<T, S>::end() const
{
    return cend();
}


// Provide an iterator
template<class T, std::size_t S>
constexpr const T * vector<T, S>::cend() const
{
    return std::next(&(m_data.back()));
}


// Get a pointer to the first element
// Elements are held in an array
template<class T, std::size_t S>
constexpr T * vector<T, S>::data()
{
    return &(*begin());
}


// Get a pointer to the first element
// Elements are held in an array
template<class T, std::size_t S>
constexpr const T * vector<T, S>::data() const
{
    return &(*cbegin());
}


// Support structured binding
template<class T, std::size_t S>
template<std::size_t I>
constexpr T vector<T, S>::get() const
{
    return m_data[I];
}


// Support structured binding
template<class T, std::size_t S>
template<std::size_t I>
constexpr T & vector<T, S>::get()
{
    return m_data[I];
}

}   // namespace core
}   // namespace ft

namespace std {

// Support structured bindings
template<std::size_t I, class T, std::size_t S>
struct tuple_element<I, ft::math::vector<T, S>> { using type = T; };

// Support structured bindings
template<class T, std::size_t S>
struct tuple_size<ft::math::vector<T, S>> : std::integral_constant<std::size_t, S> {};

};  // namespace std

#include "vector_functions.h"

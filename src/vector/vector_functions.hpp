#pragma once

// Automatically included by vector.hpp
// Defines free functions associated with vectors

// standard headers
#include <cmath>

namespace ft {
namespace math {
namespace details {
namespace vector_functions_ns {

template<class ... t_rest>
constexpr auto compare_each(bool p_first, t_rest ... p_rest) {
    return p_first && compare_each(p_rest...);
}
constexpr auto compare_each() {
    return true;
}

template<class T, std::size_t ... I>
constexpr auto compare_vectors(
    const ft::math::vector<T, sizeof...(I)>& p_left,
    const ft::math::vector<T, sizeof...(I)>& p_right,
    std::index_sequence<I...>) {
    return compare_each((p_left[I] == p_right[I])...);
}

}   // namespace vector_functions_ns
}   // namespace details
}   // namespace math
}   // namespace ft

// Comparison operators
template<class T, std::size_t S>
constexpr bool ft::math::operator==(const vector<T, S>& p_left, const vector<T, S>& p_right)
{
    return details::vector_functions_ns::compare_vectors(p_left, p_right, std::make_index_sequence<S>());
}
template<class T, std::size_t S>
constexpr bool ft::math::operator!=(const vector<T, S>& p_left, const vector<T, S>& p_right)
{
    return (p_left == p_right) == false;
}


// Arithmetic operators
template<class T, std::size_t S>
constexpr ft::math::vector<T, S> ft::math::operator+(vector<T, S> p_left, const vector<T, S>& p_right)
{
    return p_left += p_right;
}

template<class T, std::size_t S>
constexpr ft::math::vector<T, S> ft::math::operator-(vector<T, S> p_left, const vector<T, S>& p_right)
{
    return p_left -= p_right;
}

template<class T, std::size_t S, class V>
constexpr ft::math::vector<T, S> ft::math::operator*(vector<T, S> p_left, const V& p_right)
{
    return p_left *= p_right;
}

template<class T, std::size_t S, class V>
constexpr ft::math::vector<T, S> ft::math::operator*(const V& p_left, vector<T, S> p_right)
{
    return p_right * p_left;
}

template<class T, std::size_t S, class V>
constexpr ft::math::vector<T, S> ft::math::operator/(vector<T, S> p_left, const V& p_right)
{
    return p_left /= p_right;
}


// Unary minus
template<class T, std::size_t S>
constexpr ft::math::vector<T, S> ft::math::operator-(const vector<T, S>& p_vect)
{
    return p_vect * -1;
}


// Get a vector length
template<class T, std::size_t S>
constexpr T ft::math::length2(const vector<T, S>& p_ref)
{
    auto result = T{};
    for (size_t i = 0; i < S; ++i) {
        const auto& elem = p_ref.get(i);
        result += elem * elem;
    }
    return result;
}

template<class T, std::size_t S>
T ft::math::length(const vector<T, S>& p_ref)
{
    return std::sqrt(length2(p_ref));
}


// Normalize a vector
template<class T, std::size_t S>
void ft::math::normalize(vector<T, S>& p_vector)
{
    p_vector /= length(p_vector);
}


// Normalize a vector
template<class T, std::size_t S>
ft::math::vector<T, S> ft::math::normalized(const vector<T, S>& p_vector)
{
    return p_vector / length(p_vector);
}


// Calculate the cross product of two 3D vectors
template<class T>
ft::math::vector<T, 3> ft::math::vector_cross(const vector<T, 3>& p_left, const vector<T, 3>& p_right)
{
    // https://en.wikipedia.org/wiki/Cross_product

    const auto& a = p_left;
    const auto& b = p_right;

    return {
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    };
}


// Calculate the dot product of two vectors
template<std::size_t S, class T>
constexpr T ft::math::vector_dot(const vector<T, S>& p_left, const vector<T, S>& p_right)
{
    T result = 0;
    for (std::size_t i = 0; i < S; ++i)
    {
        result = p_left[i] * p_right[i];
    }
    return result;
}

// Get the angle between two vectors in radians
template<std::size_t S, class T>
constexpr T ft::math::vector_angle(const vector<T, S>& p_left, const vector<T, S>& p_right)
{
    const auto dot = vector_dot(p_left, p_right);
    const auto length_product = length(p_left) * length(p_right);
    return std::acos(dot / length_product);
}

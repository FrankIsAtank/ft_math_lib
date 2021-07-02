#pragma once

// Automatically included by vector.hpp
// Defines free functions associated with vectors

#include "vector.hpp"

namespace ft {
namespace math {

// Comparison operators
template<class T, std::size_t S>
constexpr bool operator==(const vector<T, S> & p_left, const vector<T, S> & p_right);
template<class T, std::size_t S>
constexpr bool operator!=(const vector<T, S> & p_left, const vector<T, S> & p_right);


// Arithmetic operators
template<class T, std::size_t S>
constexpr vector<T, S> operator+(vector<T, S> p_left, const vector<T, S> & p_right);
template<class T, std::size_t S>
constexpr vector<T, S> operator-(vector<T, S> p_left, const vector<T, S> & p_right);
template<class T, std::size_t S, class V>
constexpr vector<T, S> operator*(vector<T, S> p_left, const V & p_right);
template<class T, std::size_t S, class V>
constexpr vector<T, S> operator*(const V & p_left, vector<T, S> p_right);
template<class T, std::size_t S, class V>
constexpr vector<T, S> operator/(vector<T, S> p_left, const V & p_right);

// Unary minus
template<class T, std::size_t S>
constexpr vector<T, S> operator-(const vector<T, S> & p_vect);

// Get a vector length
template<class T, std::size_t S>
constexpr T length2(const vector<T, S> & p_ref);
template<class T, std::size_t S>
T length(const vector<T, S> & p_ref);

// Normalize a vector
template<class T, std::size_t S>
void normalize(vector<T, S> & p_vector);

// Normalize a vector
template<class T, std::size_t S>
vector<T, S> normalized(const vector<T, S> & p_vector);


// Calculate the cross product of two 3D vectors
template<class T>
vector<T, 3> vector_cross(const vector<T, 3> & p_left, const vector<T, 3> & p_right);

// Calculate the dot product of two vectors
template<std::size_t S, class T>
constexpr T vector_dot(const vector<T, S> & p_left, const vector<T, S> & p_right);

// Get the angle between two vectors in radians
template<std::size_t S, class T>
constexpr T vector_angle(const vector<T, S> & p_left, const vector<T, S> & p_right);

};  // namespace math
};  // namesapce ft

#include "vector_functions.hpp"

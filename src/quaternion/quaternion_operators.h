#pragma once

// Defines free operators for quaternions

// project headers
#include "quaternion.h"

namespace ft {
namespace math {

// Addition
template<class T>
quaternion<T> operator+(quaternion<T> p_left, const quaternion<T> & p_right);

// Subtraction
template<class T>
quaternion<T> operator-(quaternion<T> p_left, const quaternion<T> & p_right);


// Scalar product
template<class T>
quaternion<T> operator*(quaternion<T> p_left, const T p_right);
template<class T>
quaternion<T> operator*(const T p_left, quaternion<T> p_right);

// Scalar division
template<class T>
quaternion<T> operator/(quaternion<T> p_left, const T p_right);


// Quaternion multiplication
template<class T>
quaternion<T> operator*(quaternion<T> p_left, const quaternion<T> & p_right);

};  // namespace math
};  // namespace ft

#include "quaternion_operators.hpp"

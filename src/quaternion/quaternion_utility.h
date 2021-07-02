#pragma once

#include "quaternion.h"

namespace ft {
namespace math {


// Get the quaternion's conjugate
template<class T>
quaternion<T> conjugate(const quaternion<T> & p_quaternion);


// Get the square of the norm of this quaternion
template<class T>
T length2(const quaternion<T> & p_quaternion);


// Get the norm of this quaternion
template<class T>
T length(const quaternion<T> & p_quaternion);


// Get the inverse of this quaternion
template<class T>
quaternion<T> inverse(const quaternion<T> & p_quaternion);


// Normalize the given quaternion
template<class T>
void normalize(quaternion<T> & p_quaternion);


// Return a copy of the given quaternion but normalized
template<class T>
quaternion<T> normalized(quaternion<T> p_quaternion);

};  // namespace math
};  // namespace ft

#include "quaternion_utility.hpp"

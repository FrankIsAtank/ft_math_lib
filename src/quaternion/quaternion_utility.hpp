#pragma once

// project headers
#include "quaternion_utility.h"
#include "vector/vector_functions.h"

// standard headers
#include <cmath>

// Get the quaternion's conjugate
template<class T>
ft::math::quaternion<T> ft::math::conjugate(const quaternion<T> & p_quaternion)
{
    return quaternion(p_quaternion.get_real(), -1 * p_quaternion.get_imaginary());
}


// Get the square of the norm of this quaternion
template<class T>
T ft::math::length2(const quaternion<T> & p_quaternion)
{
    return length2(p_quaternion.get_components());
}


// Get the norm of this quaternion
template<class T>
T ft::math::length(const quaternion<T> & p_quaternion)
{
    return std::sqrt(length2(p_quaternion));
}


// Get the inverse of this quaternion
template<class T>
ft::math::quaternion<T> ft::math::inverse(const quaternion<T> & p_quaternion)
{
    return conjugate(p_quaternion) / length2(p_quaternion);
}


// Normalize the given quaternion
template<class T>
void ft::math::normalize(quaternion<T> & p_quaternion)
{
    const auto l = length(p_quaternion);
    FT_ASSERT(l > 0);
    p_quaternion /= l;
}


// Return a copy of the given quaternion but normalized
template<class T>
ft::math::quaternion<T> ft::math::normalized(quaternion<T> p_quaternion)
{
    normalize(p_quaternion);
    return p_quaternion;
}

#pragma once

#include "quaternion_operators.h"


// Addition
template<class T>
ft::math::quaternion<T> ft::math::operator+(quaternion<T> p_left, const quaternion<T> & p_right)
{
    p_left += p_right;
    return p_left;
}

// Subtraction
template<class T>
ft::math::quaternion<T> ft::math::operator-(quaternion<T> p_left, const quaternion<T> & p_right)
{
    p_left -= p_right;
    return p_left;
}


// Scalar product
template<class T>
ft::math::quaternion<T> ft::math::operator*(quaternion<T> p_left, const T p_right)
{
    p_left *= p_right;
    return p_left;
}


// Scalar product
template<class T>
ft::math::quaternion<T> ft::math::operator*(const T p_left, quaternion<T> p_right)
{
    p_right *= p_left;
    return p_right;
}


// Scalar division
template<class T>
ft::math::quaternion<T> ft::math::operator/(quaternion<T> p_left, const T p_right)
{
    p_left /= p_right;
    return p_left;
}


// Quaternion multiplication
template<class T>
ft::math::quaternion<T> ft::math::operator*(quaternion<T> p_left, const quaternion<T> & p_right)
{
    p_left *= p_right;
    return p_left;
}

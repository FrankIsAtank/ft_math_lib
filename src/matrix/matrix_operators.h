#pragma once

// Implements free operators for matrices
// Included by matrix.h

#include "matrix.h"

namespace ft {
namespace math {


// Add two matrices of the same dimensions together
// Gets the sum of matching cells
template<class T, std::size_t R, std::size_t C>
matrix<T, R, C> operator+(matrix<T, R, C> p_left, const matrix<T, R, C> & p_right);


// Substract a matrix from another with the same dimensions
// Gets the difference between matching cells
template<class T, std::size_t R, std::size_t C>
matrix<T, R, C> operator-(matrix<T, R, C> p_left, const matrix<T, R, C> & p_right);


// Multiply a matrix by a scalar
template<class T, std::size_t R, std::size_t C>
matrix<T, R, C> operator*(matrix<T, R, C> p_left, const T p_scalar);


// Multiply a matrix by a scalar
template<class T, std::size_t R, std::size_t C>
matrix<T, R, C> operator*(const T p_scalar, const matrix<T, R, C> & p_right);


// Divide a matrix by a scalar
template<class T, std::size_t R, std::size_t C>
matrix<T, R, C> operator/(matrix<T, R, C> p_left, const T p_scalar);


// matrix product operation
// Multiplies an [R, I] sized matrix by a [I, C] matrix
template<class T, std::size_t R, std::size_t I, std::size_t C>
matrix<T, R, C> operator*(const matrix<T, R, I> & p_left, const matrix<T, I, C> & p_right);


// matrix product operation
// Multiplies an square  matrix by a matrix of the same size in-plaice
template<class T, std::size_t S>
matrix<T, S, S> & operator*=(matrix<T, S, S> & p_left, const matrix<T, S, S> & p_right);

};  // namespace math
};  // namespace ft

#include "matrix_operators.hpp"

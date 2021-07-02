#pragma once

// Implements free operators for matrices
// Included by matrix.h

#include "matrix_operators.h"


// Add two matrices of the same dimensions together
// Gets the sum of matching cells
template<class T, std::size_t R, std::size_t C>
ft::math::matrix<T, R, C> ft::math::operator+(matrix<T, R, C> p_left, const matrix<T, R, C> & p_right)
{
    p_left += p_right;
    return p_left;
}


// Substract a matrix from another with the same dimensions
// Gets the difference between matching cells
template<class T, std::size_t R, std::size_t C>
ft::math::matrix<T, R, C> ft::math::operator-(matrix<T, R, C> p_left, const matrix<T, R, C> & p_right)
{
    p_left -= p_right;
    return p_left;
}


// Multiply a matrix by a scalar
template<class T, std::size_t R, std::size_t C>
ft::math::matrix<T, R, C> ft::math::operator*(matrix<T, R, C> p_left, const T p_scalar)
{
    p_left *= p_scalar;
    return p_left;
}


// Multiply a matrix by a scalar
template<class T, std::size_t R, std::size_t C>
ft::math::matrix<T, R, C> ft::math::operator*(const T p_scalar, const matrix<T, R, C> & p_right)
{
    return p_right * p_scalar;
}


// Divide a matrix by a scalar
template<class T, std::size_t R, std::size_t C>
ft::math::matrix<T, R, C> ft::math::operator/(matrix<T, R, C> p_left, const T p_scalar)
{
    p_left /= p_scalar;
    return p_left;
}


// matrix product operation
// Multiplies an [R, I] sized matrix by a [I, C] matrix
template<class T, std::size_t R, std::size_t I, std::size_t C>
ft::math::matrix<T, R, C> ft::math::operator*(const matrix<T, R, I> & p_left, const matrix<T, I, C> & p_right)
{
    ft::math::matrix<T, R, C> result;
    result.fill(0);

    for (std::size_t y = 0; y < R; ++y) {
        // The row to modify
        auto row = result[y];

        for (std::size_t x = 0; x < C; ++x) {
            // The row's element to calculate
            auto & element = row[x];

            // Calculate this row's values
            for (std::size_t k = 0; k < I; ++k) {
                element += p_left[y][k] * p_right[k][x];
            }
        }
    }

    return result;
}


// matrix product operation
// Multiplies an square  matrix by a matrix of the same size in-plaice
template<class T, std::size_t S>
ft::math::matrix<T, S, S> & ft::math::operator*=(matrix<T, S, S> & p_left, const matrix<T, S, S> & p_right)
{
    p_left = p_left * p_right;
    return p_left;
}

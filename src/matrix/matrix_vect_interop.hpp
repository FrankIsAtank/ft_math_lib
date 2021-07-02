#pragma once

// project header
#include "matrix_vect_interop.h"

// Convert a matrix's row to a vector
template<class T, std::size_t R, std::size_t C>
constexpr ft::math::vector<T, C>
ft::math::matrix_row_to_vect(const matrix<T, R, C> & p_matrix, const std::size_t p_row)
{
    FT_ASSERT(p_row < R);
    return p_matrix[p_row];
}


// Convert a matrix's column to a vector
template<class T, std::size_t R, std::size_t C>
constexpr ft::math::vector<T, R>
ft::math::matrix_column_to_vect(const matrix<T, R, C> & p_matrix, const std::size_t p_column)
{
    FT_ASSERT(p_column < C);
    auto result = vector<T, R>{};
    for (std::size_t i = 0; i < R; ++i)
    {
        result[i] = p_matrix[i][p_column];
    }
    return result;
}


// Convert row matrix to vector
template<class T, std::size_t S>
constexpr ft::math::vector<T, S>
ft::math::matrix_to_vect(const matrix<T, 1, S> & p_matrix)
{
    return matrix_row_to_vect(p_matrix, 0);
}


// Convert column matrix to vector
template<class T, std::size_t S>
constexpr std::enable_if_t<S != 1, ft::math::vector<T, S>>
ft::math::matrix_to_vect(const matrix<T, S, 1> & p_matrix)
{
    return matrix_column_to_vect(p_matrix, 0);
}


// Convert a vector to a row matrix
template<class T, std::size_t S>
constexpr ft::math::matrix<T, 1, S>
ft::math::vect_to_row_matrix(const vector<T, S> & p_vector)
{
    return p_vector.data();
}


// Convert a vector to a row matrix
template<class T, std::size_t S>
constexpr ft::math::matrix<T, S, 1> 
ft::math::vect_to_col_matrix(const vector<T, S> & p_vector)
{
    return p_vector.data();
}


// Calculate a vector tensor product
template<class T, std::size_t R, std::size_t C>
constexpr ft::math::matrix<T, R, C>
ft::math::vector_tensor_product(const vector<T, C> & p_cols, const vector<T, R> & p_rows)
{
    return vect_to_col_matrix(p_cols) * vect_to_row_matrix(p_rows);
}

#pragma once

// Functions and operators for matrix/vector interoperability

// project header
#include "matrix.h"
#include "vector/vector.h"

namespace ft {
namespace math {

// Convert a matrix's row to a vector
template<class T, std::size_t R, std::size_t C>
constexpr vector<T, C> matrix_row_to_vect(const matrix<T, R, C> & p_matrix, const std::size_t p_row);

// Convert a matrix's column to a vector
template<class T, std::size_t R, std::size_t C>
constexpr vector<T, R> matrix_column_to_vect(const matrix<T, R, C> & p_matrix, const std::size_t p_column);


// Convert row matrix to vector
template<class T, std::size_t S>
constexpr vector<T, S> matrix_to_vect(const matrix<T, 1, S> & p_matrix);

// Convert column matrix to vector
template<class T, std::size_t S>
constexpr std::enable_if_t<S != 1, vector<T, S>> matrix_to_vect(const matrix<T, S, 1> & p_matrix);


// Convert a vector to a row matrix
template<class T, std::size_t S>
constexpr matrix<T, 1, S> vect_to_row_matrix(const vector<T, S> & p_vector);

// Convert a vector to a row matrix
template<class T, std::size_t S>
constexpr matrix<T, S, 1> vect_to_col_matrix(const vector<T, S> & p_vector);


// Calculate a vector tensor product
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C> vector_tensor_product(const vector<T, C> & p_cols, const vector<T, R> & p_rows);


};  // namespace math
};  // namespace ft

#include "matrix_vect_interop.hpp"

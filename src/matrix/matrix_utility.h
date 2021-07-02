#pragma once

// Various utility functions dealing with matrices

// porject headers
#include "matrix.h"

// standard headers
#include <type_traits>

namespace ft {
namespace math {

// Returns an identify matrix of size S by S
template<class T, std::size_t S>
constexpr matrix<T, S, S> make_identity_matrix();

// Returns a matrix of size R by C containing all zero values
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C> make_zero_matrix();


// Checks if a matrix is an identify matrix
// Overload for square matrix
template<class T, std::size_t R, std::size_t C>
constexpr bool is_identify_matrix(const matrix<T, R, C> & p_matrix, std::enable_if_t<R == C>* = nullptr);

// Checks if a matrix is an identify matrix
// Overload for non-square matrix (always false)
template<class T, std::size_t R, std::size_t C>
constexpr bool is_identify_matrix(const matrix<T, R, C> & p_matrix, std::enable_if_t<R != C>* = nullptr);

// Checks if a matrix is a zero matrix
template<class T, std::size_t R, std::size_t C>
constexpr bool is_zero_matrix(const matrix<T, R, C> & p_matrix);


// Returns a subregion of this matrix
// The copied subregion starts at row p_row_offset and column p_col_offset
template<std::size_t Rout, std::size_t Cout, class T, std::size_t Rin, std::size_t Cin>
constexpr matrix<T, Rout, Cout> make_sub_matrix(
    const matrix<T, Rin, Cin> & p_matrix,
    const std::size_t p_row_offset,
    const std::size_t p_col_offset);

// Returns a minor of a matrix
// Returns the given matrix but removed the specified row and column
// The result is a matrix that is 1 element smaller in both axis
template<class T, std::size_t R, std::size_t C, class = std::enable_if_t<(R > 0) && (C > 0)>>
constexpr matrix<T, R - 1, C - 1> make_minor_matrix(
    const matrix<T, R, C> & p_matrix,
    const std::size_t p_row_index,
    const std::size_t p_col_index);


// Transpose a square matrix in-place
// Inverts columns with rows
template<class T, std::size_t S>
constexpr void transpose_matrix(matrix<T, S, S> & p_matrix);

// Make a new matrix that is the transposed of another
template<class T, std::size_t S>
constexpr matrix<T, S, S> transposed_matrix(const matrix<T, S, S> & p_matrix);


// Calculate the determinant of a matrix
// The third template argument is optional
// This is the type of value returned
template<class T, std::size_t S, class O = T, class = std::enable_if_t<S >= 2>>
constexpr O calculate_matrix_determinant(const matrix<T, S, S> & p_matrix);

// Make a matrix of the cofactor of each cell in another matrix
// The third template argument is optional
// This is the type of value returned
template<class T, std::size_t S, class O = T>
constexpr matrix<O, S, S> make_cofactor_matrix(const matrix<T, S, S> & p_matrix);

// Calculate the cofactor for a single matrix cell
// The third template argument is optional
// This is the type of value returned
template<class T, std::size_t S, class O = T>
constexpr O calculate_matrix_cell_cofactor(
    const matrix<T, S, S> & p_matrix, 
    const std::size_t p_row_index,
    const std::size_t p_col_index);


// Make a new matrix that is the inverse of another
template<class T, std::size_t S>
constexpr matrix<T, S, S> make_inverse_matrix(const matrix<T, S, S> & p_matrix);

};  // namespace math
};  // namespace ft

#include "matrix_utility.hpp"

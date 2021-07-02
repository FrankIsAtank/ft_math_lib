#pragma once

// Implements the utilities of matrix_utility.h

// oroject heaers
#include "matrix_utility.h"

// other headers
#include "error/ft_assert.h"

namespace ft {
namespace math {
namespace details {
namespace matrix_utility_ns {

template<class T, std::size_t R, std::size_t C>
constexpr auto make_zero()
{
    matrix<T, R, C> result;
    result.fill(0);
    return result;
}

template<class T, std::size_t S>
constexpr auto make_identity()
{
    matrix<T, S, S> result = make_zero<T, S, S>();
    for (std::size_t i = 0; i < S; ++i)
    {
        result[i][i] = 1;
    }
    return result;
}

};  // namespace matrix_utility_ns
};  // namespace details
};  // namespace core
};  // namespace ft


// Returns an identify matrix of size S by S
template<class T, std::size_t S>
constexpr ft::math::matrix<T, S, S> ft::math::make_identity_matrix()
{
    constexpr auto the_matrix = ft::math::details::matrix_utility_ns::make_identity<T, S>();
    return the_matrix;
}

// Returns a matrix of size R by C containing all zero values
template<class T, std::size_t R, std::size_t C>
constexpr ft::math::matrix<T, R, C> ft::math::make_zero_matrix()
{
    constexpr auto the_matrix = ft::math::details::matrix_utility_ns::make_zero<T, R, C>();
    return the_matrix;
}


// Checks if a matrix is an identify matrix
// Overload for square matrix
template<class T, std::size_t R, std::size_t C>
constexpr bool ft::math::is_identify_matrix(const matrix<T, R, C> & p_matrix, std::enable_if_t<R == C>*)
{
    constexpr auto identity = make_identity_matrix<T, R>();
    return p_matrix == identity;
}


// Checks if a matrix is an identify matrix
// Overload for non-square matrix (always false)
template<class T, std::size_t R, std::size_t C>
constexpr bool ft::math::is_identify_matrix(const matrix<T, R, C> & p_matrix, std::enable_if_t<R != C>*)
{
    return false;
}


// Checks if a matrix is a zero matrix
template<class T, std::size_t R, std::size_t C>
constexpr bool ft::math::is_zero_matrix(const matrix<T, R, C> & p_matrix)
{
    constexpr auto zero = make_zero_matrix<T, R, C>();
    return p_matrix == zero;
}


// Returns a subregion of this matrix
template<std::size_t Rout, std::size_t Cout, class T, std::size_t Rin, std::size_t Cin>
constexpr ft::math::matrix<T, Rout, Cout> ft::math::make_sub_matrix(
    const matrix<T, Rin, Cin> & p_matrix,
    const std::size_t p_row_offset,
    const std::size_t p_col_offset)
{
    FT_ASSERT(p_row_offset + Rout <= Rin);
    FT_ASSERT(p_col_offset + Cout <= Rout);

    // Start with an uninitialized matrix of the size to output
    auto result = matrix<T, Rout, Cout>{};

    // Copy the subregion
    for (std::size_t row = 0; row < Rout; ++row)
    {
        auto & to_row = result[row];
        const auto & from_row = p_matrix[row + p_row_offset];

        for (std::size_t col = 0; col < Cout; ++col)
        {
            to_row[col] = from_row[col + p_col_offset];
        }
    }
    return result;
}


// Returns a minor of a matrix
// Returns the given matrix but removed the specified row and column
// The result is a matrix that is 1 element smaller in both axis
template<class T, std::size_t R, std::size_t C, class>
constexpr ft::math::matrix<T, R - 1, C - 1> ft::math::make_minor_matrix(
    const matrix<T, R, C> & p_matrix,
    const std::size_t p_row_index,
    const std::size_t p_col_index)
{
    FT_ASSERT(p_row_index < R);
    FT_ASSERT(p_col_index < C);

    // Start with an uninitialized matrix of the size to output
    matrix<T, R - 1, C - 1> result;

    std::size_t row = 0;
    for (std::size_t y = 0; y < R; ++y)
    {
        // Skip the specified row
        if (y == p_row_index) continue;

        std::size_t col = 0;
        for (std::size_t x = 0; x < C; ++x)
        {
            // Skip the specified column
            if (x == p_col_index) continue;

            result[row][col] = p_matrix[y][x];

            col += 1;
        }

        FT_ASSERT(col == C - 1);

        row += 1;
    }

    FT_ASSERT(row == R - 1);

    return result;
}


// Transpose a square matrix in-place
// Inverts columns with rows
template<class T, std::size_t S>
constexpr void ft::math::transpose_matrix(matrix<T, S, S> & p_matrix)
{
    for (std::size_t y = 1; y < S; ++y)
    {
        for (std::size_t x = 0; x < y; ++x)
        {
            auto & arg1 = p_matrix[y][x];
            auto & arg2 = p_matrix[x][y];

            // std::Swap is not constexpr yet in c++17
            auto t = std::move(arg1);
            arg1 = std::move(arg2);
            arg2 = std::move(t);
        }
    }
}


// Make a new matrix that is the transposed of another
template<class T, std::size_t S>
constexpr ft::math::matrix<T, S, S> 
ft::math::transposed_matrix(const matrix<T, S, S> & p_matrix)
{
    // Start with an uninitialized matrix of the size to output
    matrix<T, S, S> result;

    for (std::size_t y = 0; y < S; ++y)
    {
        for (std::size_t x = 0; x < S; ++x)
        {
            result[y][x] = p_matrix[x][y];
        }
    }

    return result;
}


// Calculate the determinant of a matrix
// The third template argument is optional
// This is the type of value returned
template<class T, std::size_t S, class O, class>
constexpr O ft::math::calculate_matrix_determinant(const matrix<T, S, S> & p_matrix)
{
    static_assert(S >= 2);

    if constexpr (S == 2)
    {
        // Determinant for a 2x2 matrix
        const auto a = static_cast<O>(p_matrix[0][0]);
        const auto b = static_cast<O>(p_matrix[0][1]);
        const auto c = static_cast<O>(p_matrix[1][0]);
        const auto d = static_cast<O>(p_matrix[1][1]);
        return (a * d) - (b * c);
    }
    else
    {
        // For matrices larger than 2x2
        O result = 0;
        for (std::size_t i = 0; i < S; ++i)
        {
            result += p_matrix[0][i] * calculate_matrix_cell_cofactor<T, S, O>(p_matrix, 0, i);
        }
        return result;
    }
}


// Make a matrix of the cofactor of each cell in another matrix
// The third template argument is optional
// This is the type of value returned
template<class T, std::size_t S, class O>
constexpr ft::math::matrix<O, S, S>
ft::math::make_cofactor_matrix(const matrix<T, S, S> & p_matrix)
{
    // Start with an uninitialized matrix of the size to output
    matrix<O, S, S> result;

    for (std::size_t row = 0; row < S; ++row) {
        for (std::size_t col = 0; col < S; ++col) {
            result[row][col] = calculate_matrix_cell_cofactor<T, S, O>(p_matrix, row, col);
        }
    }
    return result;
}


// Calculate the cofactor for a single matrix cell
// The third template argument is optional
// This is the type of value returned
template<class T, std::size_t S, class O>
constexpr O ft::math::calculate_matrix_cell_cofactor(
    const matrix<T, S, S> & p_matrix,
    const std::size_t p_row_index,
    const std::size_t p_col_index)
{
    const auto minor = make_minor_matrix(p_matrix, p_row_index, p_col_index);
    const auto subdeterminant = calculate_matrix_determinant<T, S-1, O>(minor);
    const auto sign = // Simplifed (-1 ^ (p_Row + p_Col))
        static_cast<O>(1 - 2 * ((p_row_index + p_col_index) % 2));

    return sign * subdeterminant;
}



// Inverse a matrix in-place
// Make a new matrix that is the inverse of another
template<class T, std::size_t S>
constexpr ft::math::matrix<T, S, S> 
ft::math::make_inverse_matrix(const matrix<T, S, S> & p_matrix)
{
    static_assert(S > 0);

    if constexpr (S == 1)
    {
        // Shortcut for 1x1 matrix
        matrix<T, 1, 1> result;
        result[0][0] = 1 / p_matrix[0][0];
        return result;
    }
    else if constexpr (S == 2)
    {
        // Shortcut for 2x2 matrix
        matrix<T, 2, 2> result;
	    result[0][0] = p_matrix[1][1];
	    result[0][1] = -p_matrix[0][1];
	    result[1][0] = -p_matrix[0][1];
	    result[1][1] = p_matrix[0][0];
	    result /= calculate_matrix_determinant(p_matrix);
	    return result;

    }
    else if constexpr (S == 3)
    {
        // Shortcut for 3x3 matrix
        matrix<T, 3, 3> result;
        for (std::size_t i = 0; i < 3; ++i)
        {
            for (std::size_t j = 0; j < 3; ++j)
            {
                auto minor = make_minor_matrix(p_matrix, j, i);
                result[i][j] = calculate_matrix_determinant(minor);

                if ((i + j) % 2)
                {
                    result[i][j] *= -1;
                }
            }
        }

        transpose_matrix(result);

        result /= calculate_matrix_determinant(p_matrix);

        return result;
    }
    else
    {
        // General solution
        // https://en.wikipedia.org/wiki/Invertible_matrix#Analytic_solution

        const auto cofactors = make_cofactor_matrix(p_matrix);
        const auto transposed = make_transpose_matrix(cofactors);
        const auto determinant = calculate_matrix_determinant(p_matrix);

        // Check for non invertible matrix
        FT_ASSERT(determinant != 0);

        return transposed / determinant;
    }
}

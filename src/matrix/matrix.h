#pragma once

// Represents a row major matrix of `R` rows by `C` columns of `T` elements
// Implemented as a flat array
// Move semantics is no faster than copy, consider using `std::unique_ptr<matrix>` for
//  very large matrices

#include "vector/vector.h"

namespace ft {
namespace math {
 
template<class T, std::size_t R, std::size_t C>
class matrix
{
public:
    // Matrix type information
    static constexpr auto size_rows = R;
    static constexpr auto size_cols = C;
    static constexpr auto size = vector<std::size_t, 2>{ R, C };
    static constexpr auto elements = size_rows * size_cols;
    using value_type = T;
    using value_array = vector<T, elements>;

public:
    // Default constructor
    // Values are uninitialized
    constexpr matrix() = default;


    // Construct from an array of values
    constexpr matrix(const std::array<T, elements> & p_values);

    // Construct from an array of values
    constexpr matrix(std::array<T, elements> && p_values);


    // Construct from a vector of values
    constexpr matrix(const value_array & p_values);

    // Construct from a vector of values
    constexpr matrix(value_array && p_values);

    // Construct from an initializer list
    constexpr matrix(const std::initializer_list<T> & p_list);


    
    // Construct from a pointer to the start of an array
    // The pointer must point to an element that is part
    //  of an array with at least R * C - 1 elements
    //  following it
    constexpr matrix(const T * const p_data);


    // Convert to an equal matrix with different data type
    template<class U>
    constexpr matrix<U, R, C> cast() const;


    // Assign values to all elements
    constexpr void fill(const value_type & p_value);


    // Access a matrix's row (mutable)
    // Returns a pointer to the first element of the row
    constexpr value_type * operator[](const std::size_t p_row);

    // Access a matrix's row (const)
    // Returns a pointer to the first element of the row
    constexpr const value_type * operator[](const std::size_t p_row) const;


    // Compare this matrix with another with the same dimensions
    // Returns true if the difference between each element
    // is within a rounding error
    constexpr bool compare_epsilon(const matrix & p_ref, const T p_error) const;

    // Compare this matrix with another with the same dimensions
    constexpr bool operator==(const matrix & p_ref) const;

    // Compare this matrix with another with the same dimensions
    constexpr bool operator!=(const matrix & p_ref) const;


    // Add a matrix to this matrix
    constexpr matrix & operator+=(const matrix & p_ref);

    // Substract a matrix from this matrix
    constexpr matrix & operator-=(const matrix & p_ref);

    // Multiply this matrix by a scalar
    constexpr matrix & operator*=(const value_type & p_scalar);

    // Divide this matrix by a scalar
    constexpr matrix & operator/=(const value_type & p_scalar);


    // Get direct access to the underlying data
    constexpr value_type * data();

    // Get direct access to the underlying data
    constexpr const value_type * data() const;

private:
    // Stored as an array of rows
    value_array m_data;

};  // class matrix

};	// namespace math
};	// namespace ft

#include "matrix.hpp"
#include "matrix_operators.h"

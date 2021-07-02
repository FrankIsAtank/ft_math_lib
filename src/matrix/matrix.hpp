#pragma once

// Implementation for the matrix class

// project headers
#include "matrix.h"

// other headers
#include "error/ft_assert.h"

// standard headers
#include <algorithm>

namespace ft {
namespace math {

// Construct from an array of values
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C>::matrix(const std::array<T, elements> & p_values) :
    m_data(p_values)
{}


// Construct from an array of values
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C>::matrix(std::array<T, elements> && p_values) :
    m_data(std::move(p_values))
{ }


// Construct from a vector of values
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C>::matrix(const value_array & p_values) :
    m_data(p_values)
{ }


// Construct from a vector of values
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C>::matrix(value_array && p_values) :
    m_data(std::move(p_values))
{ }


// Construct from an initializer list
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C>::matrix(const std::initializer_list<T> & p_list)
{ 
    FT_ASSERT(p_list.size() == elements);
    std::size_t i = 0;
    for(auto & value : p_list)
    {
        m_data[i] = value;
        ++i;
    }
}


// Construct from a pointer to the start of an array
// The pointer must point to an element that is part
//  of an array with at least R * C - 1 elements
//  following it
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C>::matrix(const T * const p_data) :
    m_data(p_data)
{ }


// Convert to an equal matrix with different data type
template<class T, std::size_t R, std::size_t C>
template<class U>
constexpr matrix<U, R, C> matrix<T, R, C>::cast() const
{
    return { m_data.cast<U>() };
}


// Assign values to all elements
template<class T, std::size_t R, std::size_t C>
constexpr void matrix<T, R, C>::fill(const value_type & p_value)
{
    for (auto & cell : m_data) {
        cell = p_value;
    }
}


// Access a matrix's row (mutable)
template<class T, std::size_t R, std::size_t C>
constexpr typename matrix<T, R, C>::value_type * 
matrix<T, R, C>::operator[](const std::size_t p_row)
{
    FT_ASSERT(p_row < size_rows);
    return &(m_data[p_row * C]);
}


// Access a matrix's row (const)
template<class T, std::size_t R, std::size_t C>
constexpr const typename matrix<T, R, C>::value_type *
matrix<T, R, C>::operator[](const std::size_t p_row) const
{
    FT_ASSERT(p_row < size_rows);
    return &(m_data[p_row * C]);
}


// Compare this matrix with another with the same dimensions
// Returns true if the difference between each element
// is within a rounding error
template<class T, std::size_t R, std::size_t C>
constexpr bool matrix<T, R, C>::compare_epsilon(const matrix & p_ref, const T p_error) const
{
    return m_data.compare_epsilon(p_ref.m_data, p_error);
}


// Compare this matrix with another with the same dimensions
template<class T, std::size_t R, std::size_t C>
constexpr bool matrix<T, R, C>::operator==(const matrix & p_ref) const
{
    for (std::size_t y = 0; y < size_rows; ++y)
    {
        if (m_data[y] != p_ref.m_data[y])
        {
            return false;
        }
    }

    // No difference found
    return true;
}


// Compare this matrix with another with the same dimensions
template<class T, std::size_t R, std::size_t C>
constexpr bool matrix<T, R, C>::operator!=(const matrix & p_ref) const
{
    return operator==(p_ref) == false;
}


// Add a matrix to this matrix
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C> & matrix<T, R, C>::operator+=(const matrix & p_ref)
{
    m_data += p_ref.m_data;
    return *this;
}


// Substract a matrix from this matrix
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C> & matrix<T, R, C>::operator-=(const matrix & p_ref)
{
    m_data -= p_ref.m_data;
    return *this;
}


// Multiply this matrix by a scalar
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C> & matrix<T, R, C>::operator*=(const value_type & p_scalar)
{
    m_data *= p_scalar;
    return *this;
}


// Divide this matrix by a scalar
template<class T, std::size_t R, std::size_t C>
constexpr matrix<T, R, C> & matrix<T, R, C>::operator/=(const value_type & p_scalar)
{
    m_data /= p_scalar;
    return *this;
}


// Get direct access to the underlying data
template<class T, std::size_t R, std::size_t C>
constexpr typename matrix<T, R, C>::value_type * matrix<T, R, C>::data()
{
    return m_data.data();
}


// Get direct access to the underlying data
template<class T, std::size_t R, std::size_t C>
constexpr const typename matrix<T, R, C>::value_type * matrix<T, R, C>::data() const
{
    return m_data.data();
}

};	// namespace math
};	// namespace ft

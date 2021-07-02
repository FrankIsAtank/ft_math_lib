// project heaers
#include "matrix/matrix_operators.h"
#include "quaternion.h"

// standard headers
#include <cmath>

// Initialize to these values
template<class T>
ft::math::quaternion<T>::quaternion(const T p_r, const T p_i, const T p_j, const T p_k)
{
    set(p_r, p_i, p_j, p_j);
}


// Initialize to these values
template<class T>
ft::math::quaternion<T>::quaternion(const T p_r, const vector<T, 3> & p_v)
{
    set(p_r, p_v);
}


// Set the quaternion to these values
template<class T>
void ft::math::quaternion<T>::set(const T p_r, const T p_i, const T p_j, const T p_k)
{
    m_matrix[0][0] = { p_r, p_i };
    m_matrix[0][1] = { p_j, p_k };
    m_matrix[1][0] = { -p_j, p_k };
    m_matrix[1][1] = { p_r, -p_i };
}


// Initialize to these values
template<class T>
ft::math::quaternion<T>::quaternion(const vector<T, 4> & p_values)
{
    set(p_values);
}


// Set the quaternion to these values
template<class T>
void ft::math::quaternion<T>::set(const T p_r, const vector<T, 3> & p_v)
{
    set(p_r, p_v[0], p_v[1], p_v[2]);
}


// Set the quaternion to these values
template<class T>
void ft::math::quaternion<T>::set(const vector<T, 4> & p_values)
{
    set(p_values[0], p_values[1], p_values[2], p_values[3]);
}


// Get the imaginary components
template<class T>
ft::math::vector<T, 3> ft::math::quaternion<T>::get_imaginary() const
{
    return { get_i(), get_j(), get_k() };
}


// Get the real component
template<class T>
T ft::math::quaternion<T>::get_real() const
{
    return get_r();
}


// Get all components
// The first component is the real part
template<class T>
ft::math::vector<T, 4> ft::math::quaternion<T>::get_components() const
{
    return { get_r(), get_i(), get_j(), get_k() };
}


// Addition
template<class T>
ft::math::quaternion<T> & ft::math::quaternion<T>::operator+=(const quaternion & p_other)
{
    m_matrix += p_other.m_matrix;
    return *this;
}


// Subtraction
template<class T>
ft::math::quaternion<T> & ft::math::quaternion<T>::operator-=(const quaternion & p_other)
{
    m_matrix -= p_other.m_matrix;
    return *this;
}


// Scalar product
template<class T>
ft::math::quaternion<T> & ft::math::quaternion<T>::operator*=(const T p_scalar)
{
    m_matrix *= p_scalar;
    return *this;
}


// Scalar division
template<class T>
ft::math::quaternion<T> & ft::math::quaternion<T>::operator/=(const T p_scalar)
{
    m_matrix /= p_scalar;
    return *this;
}


// Quaternion multiplication
template<class T>
ft::math::quaternion<T> & ft::math::quaternion<T>::operator*=(const quaternion & p_other)
{
    m_matrix *= p_other.m_matrix;
    return *this;
}


// Get a component from the matrix representation
template<class T>
T ft::math::quaternion<T>::get_r() const
{
    return m_matrix[0][0].real();
}


// Get a component from the matrix representation
template<class T>
T ft::math::quaternion<T>::get_i() const
{
    return m_matrix[0][0].imag();
}


// Get a component from the matrix representation
template<class T>
T ft::math::quaternion<T>::get_j() const
{
    return m_matrix[0][1].real();
}


// Get a component from the matrix representation
template<class T>
T ft::math::quaternion<T>::get_k() const
{
    return m_matrix[0][1].imag();
}

// Explicit specialization
template class ft::math::quaternion<float>;
template class ft::math::quaternion<double>;
template class ft::math::quaternion<long double>;

#pragma once

// project headers
#include "matrix/matrix.h"
#include "vector/vector.h"

// standard headers
#include <complex>
#include <type_traits>

// i, j, k are the imaginary components
// r is the real component
// v is an array of 3 values representing i, j and k

// T must be one of :
//  float
//  double
//  long double

namespace ft {
namespace math {

template<class T>
class quaternion
{
    static_assert(
        std::is_same_v<T, float> ||
        std::is_same_v<T, double> ||
        std::is_same_v<T, long double>,
        "Uses std::complex internally, only float, double or long double are supported");

public:
    // Default constructor
    // Uninitialized elements
    quaternion() = default;


    // Initialize to these values
    quaternion(const T p_r, const T p_i, const T p_j, const T p_k);

    // Initialize to these values
    quaternion(const T p_r, const vector<T, 3> & p_v);

    // Initialize to these values
    // The first component is the real part
    quaternion(const vector<T, 4> & p_values);


    // Set the quaternion to these values
    void set(const T p_r, const T p_i, const T p_j, const T p_k);

    // Set the quaternion to these values
    void set(const T p_r, const vector<T, 3> & p_v);

    // Set the quaternion to these values
    // The first component is the real part
    void set(const vector<T, 4> & p_values);


    // Get the imaginary components
    vector<T, 3> get_imaginary() const;

    // Get the real component
    T get_real() const;

    // Get all components
    // The first component is the real part
    vector<T, 4> get_components() const;


    // Addition
    quaternion & operator+=(const quaternion & p_other);

    // Subtraction
    quaternion & operator-=(const quaternion & p_other);


    // Scalar product
    quaternion & operator*=(const T p_scalar);

    // Scalar division
    quaternion & operator/=(const T p_scalar);


    // Quaternion multiplication
    quaternion & operator*=(const quaternion & p_other);

private:
    // Get a component from the matrix representation
    T get_r() const;
    T get_i() const;
    T get_j() const;
    T get_k() const;

private:
    // Use matrix representation
    // https://en.wikipedia.org/wiki/Quaternion#Matrix_representations
    matrix<std::complex<T>, 2, 2> m_matrix;

};  // class quaternion

};  // namespace math
};  // namespace ft

#include "quaternion_operators.h"

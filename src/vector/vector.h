#pragma once

// standard headers
#include <array>
#include <cstddef>  // std::size_t
#include <functional>
#include <type_traits>
#include <utility>

namespace ft {
namespace math {

template<class T, std::size_t S>
class vector
{
private:
    struct t_private {};
    static_assert(S > 0, "No support for zero sized vector");

public:
    using value_type = T;
    static constexpr auto elements = S;

public:
    // Default constructor
    constexpr vector() = default;

    // Value-wise constructor
    template<class ... t_args>
    constexpr vector(const std::enable_if_t<sizeof...(t_args) + 1 == S, T>& p_first, t_args&& ... p_args) noexcept(std::is_nothrow_constructible_v<T>);

    // Value-wise constructor
    template<class ... t_args>
    constexpr vector(std::enable_if_t<sizeof...(t_args) + 1 == S, T>&& p_first, t_args&& ... p_args) noexcept(std::is_nothrow_constructible_v<T>);


    // Construct from an array of values
    constexpr vector(const std::array<T, S>& p_values);

    // Construct from an array of values
    constexpr vector(std::array<T, S>&& p_values);

    // Construct from contiguous data
    // p_value must point to an element in an array
    //  which is followed by at least S - 1 elements
    constexpr vector(const T* p_values);


    // Returns a subsection of this vector
    // Remove `R` elements, starting with the first `p_offset` and
    //  then remove the rest from the end
    // Ex. remove<1>(1) will turn [XYZ] into [YZ]
    template<std::size_t R>
    constexpr vector<T, S - R> demote(const std::size_t p_offset) const;

    // Make a larger vector and initialize a subsection of it
    //  to the values of this vector
    template<std::size_t R>
    constexpr vector<T, S + R> promote(const std::size_t p_offset) const;



    // Convert to another vector of the same size but with a different element type
    template<class U>
    constexpr vector<U, S> cast() const;

    // Mutable reference to an element
    constexpr T& operator[](const std::size_t p_index) noexcept;
    constexpr T& get(const std::size_t p_index) noexcept;

    // Const reference to an element
    constexpr const T& operator[](const std::size_t p_index) const noexcept;
    constexpr const T& get(const std::size_t p_index) const noexcept;

    // Helper function to get common elements
    constexpr auto&& x() const noexcept { static_assert(S >= 1); return get(0); }
    constexpr auto&& y() const noexcept { static_assert(S >= 2); return get(1); }
    constexpr auto&& z() const noexcept { static_assert(S >= 3); return get(2); }
    constexpr auto&& w() const noexcept { static_assert(S >= 4); return get(3); }
    constexpr auto&& x() noexcept { static_assert(S >= 1); return get(0); }
    constexpr auto&& y() noexcept { static_assert(S >= 2); return get(1); }
    constexpr auto&& z() noexcept { static_assert(S >= 3); return get(2); }
    constexpr auto&& w() noexcept { static_assert(S >= 4); return get(3); }

    // Arithmetic operators
    constexpr vector& operator-=(const vector& p_other);
    constexpr vector& operator+=(const vector& p_other);
    template<class V>
    constexpr vector& operator*=(const V& p_value);
    template<class V>
    constexpr vector& operator/=(const V& p_value);

    // Compare operators
    constexpr bool operator==(const vector& p_other) const;
    constexpr bool operator!=(const vector& p_other) const;

    // Compare this vector with another with the same dimensions
    // Returns true if the difference between each element
    // is within a rounding error
    constexpr bool compare_epsilon(const vector& p_ref, const T p_error) const;

    // Provides iterators
    constexpr T* begin();
    constexpr const T* begin() const;
    constexpr const T* cbegin() const;
    constexpr T* end();
    constexpr const T* end() const;
    constexpr const T* cend() const;

    // Get a pointer to the first element
    // Elements are held in an array
    constexpr T* data();
    constexpr const T* data() const;

    // Support structured binding
    template<std::size_t I>
    constexpr T get() const;
    template<std::size_t I>
    constexpr T& get();

private:
    // Data
    std::array<T, S> m_data;

};  // class vector

}   // namespace math
}   // namespace ft

#include "vector.hpp"

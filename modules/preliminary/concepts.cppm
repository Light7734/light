// A simple extension to stdlib's <concept>

export module preliminary.concepts;

import std;

template<class T, template<class> class U>
inline constexpr bool is_instance_of_v = std::false_type {};

template<template<class> class U, class V>
inline constexpr bool is_instance_of_v<U<V>, U> = std::true_type {};

export template<class T, template<class> class U>
concept is_instance_of = is_instance_of_v<T, U>;

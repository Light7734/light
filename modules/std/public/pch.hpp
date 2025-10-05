/** @file pch.hpp
 *
 * @brief Provides the entire standard library as a precompiled header
 */

#pragma once // NOLINTBEGIN

//============================================================
// C Standard Library Headers (from <c...> family)
//============================================================
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

//============================================================
// Input/Output and Formatting
//============================================================
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

//============================================================
// Containers
//============================================================
#include <array>
#include <deque>
#include <flat_map>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <span>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//============================================================
// Algorithms and Iterators
//============================================================
#include <algorithm>
#include <execution>
#include <iterator>
#include <numeric>

//============================================================
// Strings and Localization
//============================================================
#include <charconv>
#include <codecvt>
#include <locale>
#include <string>
#include <string_view>

//============================================================
// Memory Management and Smart Pointers
//============================================================
#include <memory>
#include <memory_resource>
#include <new>
#include <scoped_allocator>

//============================================================
// Utility and Miscellaneous
//============================================================
#include <any>
#include <bitset>
#include <chrono>
#include <functional>
#include <optional>
#include <ratio>
#include <source_location>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <variant>
#include <version>

//============================================================
// Concurrency and Multithreading
//============================================================
#include <atomic>
#include <barrier>
#include <condition_variable>
#include <future>
#include <latch>
#include <mutex>
#include <semaphore>
#include <shared_mutex>
#include <stop_token>
#include <thread>

//============================================================
// Random Numbers and Numeric Limits
//============================================================
#include <complex>
#include <limits>
#include <numbers>
#include <random>
#include <valarray>

//============================================================
// Regular Expressions
//============================================================
#include <regex>

//============================================================
// Error Handling and Diagnostics
//============================================================
#include <cassert>
#include <cerrno>
#include <exception>
#include <source_location>
#include <stdexcept>
#include <system_error>

//============================================================
// C++20/23 Additions
//============================================================
#include <bit>      // C++20 bit operations
#include <compare>  // C++20 three-way comparison
#include <expected> // C++23 std::expected (if supported)
#include <format>   // C++20 formatting
#include <print>    // C++23 print functions
#include <ranges>   // C++20 ranges library
#include <span>     // C++20 span (repeated intentionally for clarity)
// #include <stacktrace> // C++23 stack tracing utilities // Not supported yet
#include <syncstream> // C++20 synchronized output streams
// NOLINTEND

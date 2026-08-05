// A simple extension to stdlib's <concept>

export module preliminary.concepts;

import std;

export namespace lt {

template<typename Ptr_T>
concept is_nullptr_assignable = std::is_assignable_v<Ptr_T &, std::nullptr_t>;

} // namespace lt

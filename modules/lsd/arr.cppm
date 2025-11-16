export module lsd.arr;
import std;

export namespace lt::lsd {

template<typename T, size_t size>
using arr = std::array<T, size>;

}

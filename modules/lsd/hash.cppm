export module lsd.hash;
import std;

export namespace lt::lsd {

template<typename T>
using hash = std::hash<T>;
}

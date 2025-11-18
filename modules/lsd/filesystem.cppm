export module lsd.filesystem;
import std;

export namespace lt::lsd::file {

using path = ::std::filesystem::path;
using ::std::filesystem::remove;
using in_stream = ::std::ifstream;
using out_stream = ::std::ofstream;

constexpr auto ios_binary = std::ios::binary;
constexpr auto ios_end = std::ios::end;
constexpr auto ios_beg = std::ios::beg;


} // namespace lt::lsd::file

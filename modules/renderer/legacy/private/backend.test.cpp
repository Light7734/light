#include <ranges>
#include <renderer/system.hpp>
#include <test/test.hpp>

using namespace lt;
#include <renderer/backend.hpp>

using lt::test::Case;
using lt::test::Suite;

Suite raii = [] {
	Case { "happy path won't throw" } = [] {
	};
};

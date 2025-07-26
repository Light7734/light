#include <renderer/vk/instance.hpp>
#include <test/test.hpp>

lt::test::Suite raii = [] {
	lt::test::Case { "raii" } = [] {
		auto instance = lt::vk::Instance {};
	};
};

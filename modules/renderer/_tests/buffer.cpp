import renderer.frontend;
import renderer.test_utils;

using enum ::lt::renderer::IDebugger::MessageSeverity;
using enum ::lt::renderer::IBuffer::Usage;

Suite raii = "buffer_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	Case { "unhappy path throws" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	Case { "tapping" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	Case { "mapping" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
};

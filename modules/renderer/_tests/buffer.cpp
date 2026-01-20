import renderer.frontend;
import renderer.test_utils;

using enum ::lt::renderer::IDebugger::MessageSeverity;
using enum ::lt::renderer::IBuffer::Usage;
using ::std::this_thread::sleep_for;

// TODO(Light): finish these (and many other) tests...
Suite raii = "buffer_raii"_suite = [] {
	Case { "happy paths" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	sleep_for(std::chrono::milliseconds { 500u });

	Case { "unhappy paths" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	sleep_for(std::chrono::milliseconds { 500u });

	Case { "mapping" } = [] {
		auto fixture = FixtureDeviceSwapchain {};
	};
	sleep_for(std::chrono::milliseconds { 500u });
};

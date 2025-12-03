import renderer.frontend;
import renderer.test_utils;

using enum ::lt::renderer::IDebugger::MessageSeverity;
using enum ::lt::renderer::IBuffer::Usage;

Suite raii = "buffer_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		for (auto idx = 0; idx <= std::to_underlying(staging); ++idx)
		{
			ignore = lt::renderer::create_buffer(
			    lt::renderer::Api::vulkan,
			    fixture.device(),
			    fixture.gpu(),
			    lt::renderer::IBuffer::CreateInfo {
			        .usage = static_cast<lt::renderer::IBuffer::Usage>(idx),
			        .size = 1000u,
			        .debug_name = "",
			    }
			);
		}

		expect_false(fixture.has_any_messages_of(error));
		expect_false(fixture.has_any_messages_of(warning));
	};

	Case { "unhappy path throws" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		auto info = lt::renderer::IBuffer::CreateInfo {
			.usage = vertex,
			.size = 10000u,
			.debug_name = "",
		};

		expect_throw([&] {
			ignore = lt::renderer::create_buffer(
			    lt::renderer::Api::vulkan,
			    nullptr,
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_buffer(lt::renderer::Api::vulkan, fixture.device(), nullptr, info);
		});

		expect_throw([&, info] mutable {
			info.size = 0;
			ignore = lt::renderer::create_buffer(
			    lt::renderer::Api::vulkan,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_buffer(
			    lt::renderer::Api::direct_x,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_buffer(
			    lt::renderer::Api::metal,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = lt::renderer::create_buffer(
			    lt::renderer::Api::none,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		/** Make sure the default-case was OK */
		ignore = lt::renderer::create_buffer(lt::renderer::Api::vulkan, fixture.device(), fixture.gpu(), info);

		expect_false(fixture.has_any_messages_of(error));
		expect_false(fixture.has_any_messages_of(warning));
	};
};

Suite mapping = "buffer_mapping"_suite = [] {
	Case { "mapping" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		constexpr auto size = 1000u;

		auto buffer = lt::renderer::create_buffer(
		    lt::renderer::Api::vulkan,
		    fixture.device(),
		    fixture.gpu(),
		    lt::renderer::IBuffer::CreateInfo {
		        .usage = staging,
		        .size = size,
		        .debug_name = "",
		    }
		);

		auto map = buffer->map();
		expect_eq(map.size(), size);
		expect_not_nullptr(map.data());

		expect_false(fixture.has_any_messages_of(error));
		expect_false(fixture.has_any_messages_of(warning));
	};
};

#include <renderer/frontend/data/buffer.hpp>
#include <renderer/test/utils.hpp>

using ::lt::renderer::IBuffer;
using enum ::lt::renderer::IMessenger::MessageSeverity;

Suite raii = "buffer_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		for (auto idx = 0; idx <= std::to_underlying(IBuffer::Usage::staging); ++idx)
		{
			ignore = IBuffer::create(
			    lt::renderer::Api::vulkan,
			    fixture.device(),
			    fixture.gpu(),
			    IBuffer::CreateInfo {
			        .usage = static_cast<IBuffer::Usage>(idx),
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

		auto info = IBuffer::CreateInfo {
			.usage = IBuffer::Usage::vertex,
			.size = 10000u,
			.debug_name = "",
		};

		expect_throw([&] {
			ignore = IBuffer::create(lt::renderer::Api::vulkan, nullptr, fixture.gpu(), info);
		});

		expect_throw([&] {
			ignore = IBuffer::create(lt::renderer::Api::vulkan, fixture.device(), nullptr, info);
		});

		expect_throw([&, info] mutable {
			info.size = 0;
			ignore = IBuffer::create(
			    lt::renderer::Api::vulkan,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = IBuffer::create(
			    lt::renderer::Api::direct_x,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = IBuffer::create(
			    lt::renderer::Api::metal,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		expect_throw([&] {
			ignore = IBuffer::create(
			    lt::renderer::Api::none,
			    fixture.device(),
			    fixture.gpu(),
			    info
			);
		});

		/** Make sure the default-case was OK */
		ignore = IBuffer::create(lt::renderer::Api::vulkan, fixture.device(), fixture.gpu(), info);

		expect_false(fixture.has_any_messages_of(error));
		expect_false(fixture.has_any_messages_of(warning));
	};
};

Suite mapping = "buffer_mapping"_suite = [] {
	Case { "mapping" } = [] {
		auto fixture = FixtureDeviceSwapchain {};

		constexpr auto size = 1000u;

		auto buffer = IBuffer::create(
		    lt::renderer::Api::vulkan,
		    fixture.device(),
		    fixture.gpu(),
		    IBuffer::CreateInfo {
		        .usage = IBuffer::Usage::staging,
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

import renderer.test_utils;

Suite raii = "debugger_raii"_suite = [] {
	Case { "happy paths" } = [] {
		ignore = lt::renderer::vkb::Debugger(
		    lt::renderer::vkb::Instance::get(),
		    lt::renderer::vkb::Debugger::CreateInfo {
		        .severities = lt::renderer::vkb::Debugger::MessageSeverity::all,
		        .types = lt::renderer::vkb::Debugger::MessageType::all,
		        .callback = &noop_callback,
		    }
		);
	};

	Case { "unhappy paths" } = [] {
		expect_throw([] {
			ignore = lt::renderer::vkb::Debugger(
			    lt::renderer::vkb::Instance::get(),
			    lt::renderer::vkb::Debugger::CreateInfo {
			        .severities = {},
			        .types = lt::renderer::vkb::Debugger::MessageType::all,
			        .callback = &noop_callback,
			    }
			);
		});

		expect_throw([] {
			ignore = lt::renderer::vkb::Debugger(
			    lt::renderer::vkb::Instance::get(),
			    lt::renderer::vkb::Debugger::CreateInfo {
			        .severities = lt::renderer::vkb::Debugger::MessageSeverity::all,
			        .types = {},
			        .callback = &noop_callback,
			    }
			);
		});

		expect_throw([] {
			ignore = lt::renderer::vkb::Debugger(
			    lt::renderer::vkb::Instance::get(),
			    lt::renderer::vkb::Debugger::CreateInfo {
			        .severities = lt::renderer::vkb::Debugger::MessageSeverity::all,
			        .types = lt::renderer::vkb::Debugger::MessageType::all,
			        .callback = {},
			    }
			);
		});
	};
};

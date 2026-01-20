import renderer.frontend;
import renderer.test_utils;

Suite raii = "debugger_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		ignore = lt::renderer::create_debugger(
		    lt::renderer::Api::vulkan,
		    lt::renderer::get_instance(lt::renderer::Api::vulkan),
		    lt::renderer::IDebugger::CreateInfo {
		        .severities = lt::renderer::IDebugger::MessageSeverity::all,
		        .types = lt::renderer::IDebugger::MessageType::all,
		        .callback = &noop_callback,
		    }
		);
	};

	Case { "unhappy path throws" } = [] {
		expect_throw([] {
			ignore = lt::renderer::create_debugger(
			    lt::renderer::Api::vulkan,
			    lt::renderer::get_instance(lt::renderer::Api::vulkan),
			    lt::renderer::IDebugger::CreateInfo {
			        .severities = lt::renderer::IDebugger::MessageSeverity::all,
			        .types = lt::renderer::IDebugger::MessageType::all,
			        .callback = {},
			    }
			);
		});

		expect_throw([] {
			ignore = lt::renderer::create_debugger(
			    lt::renderer::Api::vulkan,
			    lt::renderer::get_instance(lt::renderer::Api::vulkan),
			    lt::renderer::IDebugger::CreateInfo {
			        .severities = {},
			        .types = lt::renderer::IDebugger::MessageType::all,
			        .callback = &noop_callback,
			    }
			);
		});

		expect_throw([] {
			ignore = lt::renderer::create_debugger(
			    lt::renderer::Api::vulkan,
			    lt::renderer::get_instance(lt::renderer::Api::vulkan),
			    lt::renderer::IDebugger::CreateInfo {
			        .severities = lt::renderer::IDebugger::MessageSeverity::all,
			        .types = {},
			        .callback = &noop_callback,
			    }
			);
		});
	};
};

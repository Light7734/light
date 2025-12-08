import renderer.frontend;
import renderer.test_utils;

void noop_callback(
    lt::renderer::IDebugger::MessageSeverity message_severity,
    lt::renderer::IDebugger::MessageType message_type,
    const lt::renderer::IDebugger::MessageData &data,
    std::any &user_data
)
{
}

Suite raii = "debugger_raii"_suite = [] {
	Case { "happy path won't throw" } = [] {
		std::ignore = lt::renderer::create_debugger(
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
			std::ignore = lt::renderer::create_debugger(
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
			std::ignore = lt::renderer::create_debugger(
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
			std::ignore = lt::renderer::create_debugger(
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

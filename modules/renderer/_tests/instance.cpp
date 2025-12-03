#include <renderer/backend/vk/context/instance.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <test/test.hpp>

using namespace lt;
using renderer::vk::Instance;
using test::Case;
using test::expect_not_nullptr;
using test::Suite;
// NOLINTNEXTLINE
Suite raii = "raii"_suite = [] {
	Case { "post singleton insantiation state is correct" } = [] {
		expect_not_nullptr(Instance::get());

		using namespace renderer::vk;
		expect_not_nullptr(vk_get_physical_device_properties);
		expect_not_nullptr(vk_get_physical_device_queue_family_properties);
		expect_not_nullptr(vk_create_device);
		expect_not_nullptr(vk_get_device_proc_address);
		expect_not_nullptr(vk_destroy_device);
		expect_not_nullptr(vk_get_physical_device_features);
		expect_not_nullptr(vk_enumerate_device_extension_properties);

		expect_not_nullptr(vk_cmd_begin_debug_label);
		expect_not_nullptr(vk_cmd_end_debug_label);
		expect_not_nullptr(vk_cmd_insert_debug_label);
		expect_not_nullptr(vk_create_debug_messenger);
		expect_not_nullptr(vk_destroy_debug_messenger);
		expect_not_nullptr(vk_queue_begin_debug_label);
		expect_not_nullptr(vk_queue_end_debug_label);
		expect_not_nullptr(vk_queue_insert_debug_label);
		expect_not_nullptr(vk_set_debug_object_name);
		expect_not_nullptr(vk_set_debug_object_tag);
		expect_not_nullptr(vk_submit_debug_message);

		expect_not_nullptr(vk_get_physical_device_surface_support);
		expect_not_nullptr(vk_get_physical_device_surface_capabilities);
		expect_not_nullptr(vk_get_physical_device_surface_formats);

		// TODO(Light): add test for platform-dependant functions
		// expect_not_nullptr(vk_create_xlib_surface_khr);
		// expect_not_nullptr(vk_destroy_surface_khr);
	};

	// TODO(Light): move device function symbols to device.cpp
	// Case { "post load device functions state is correct" } = [] {
	// 	using namespace renderer::vk;
	// 	expect_not_nullptr(Instance::get());
	//
	// 	expect_not_nullptr(vk_get_device_queue);
	// 	expect_not_nullptr(vk_create_command_pool);
	// 	expect_not_nullptr(vk_destroy_command_pool);
	// 	expect_not_nullptr(vk_allocate_command_buffers);
	// 	expect_not_nullptr(vk_free_command_buffers);
	// 	expect_not_nullptr(vk_begin_command_buffer);
	// 	expect_not_nullptr(vk_end_command_buffer);
	// 	expect_not_nullptr(vk_cmd_pipeline_barrier);
	// 	expect_not_nullptr(vk_queue_submit);
	// 	expect_not_nullptr(vk_queue_wait_idle);
	// 	expect_not_nullptr(vk_device_wait_idle);
	// 	expect_not_nullptr(vk_create_fence);
	// 	expect_not_nullptr(vk_destroy_fence);
	// 	expect_not_nullptr(vk_wait_for_fences);
	// 	expect_not_nullptr(vk_reset_fences);
	// 	expect_not_nullptr(vk_create_semaphore);
	// 	expect_not_nullptr(vk_destroy_semaphore);
	// 	expect_not_nullptr(vk_create_swapchain_khr);
	// 	expect_not_nullptr(vk_destroy_swapchain_khr);
	// 	expect_not_nullptr(vk_get_swapchain_images_khr);
	// 	expect_not_nullptr(vk_acquire_next_image_khr);
	// 	expect_not_nullptr(vk_queue_present_khr);
	// 	expect_not_nullptr(vk_create_image_view);
	// 	expect_not_nullptr(vk_destroy_image_view);
	// 	expect_not_nullptr(vk_create_render_pass);
	// 	expect_not_nullptr(vk_destroy_render_pass);
	// 	expect_not_nullptr(vk_create_frame_buffer);
	// 	expect_not_nullptr(vk_destroy_frame_buffer);
	// 	expect_not_nullptr(vk_create_shader_module);
	// 	expect_not_nullptr(vk_destroy_shader_module);
	// 	expect_not_nullptr(vk_create_pipeline_layout);
	// 	expect_not_nullptr(vk_destroy_pipeline_layout);
	// 	expect_not_nullptr(vk_create_graphics_pipelines);
	// 	expect_not_nullptr(vk_destroy_pipeline);
	// 	expect_not_nullptr(vk_cmd_begin_render_pass);
	// 	expect_not_nullptr(vk_cmd_end_render_pass);
	// 	expect_not_nullptr(vk_cmd_bind_pipeline);
	// 	expect_not_nullptr(vk_cmd_draw);
	// 	expect_not_nullptr(vk_cmd_set_viewport);
	// 	expect_not_nullptr(vk_cmd_set_scissors);
	// };
};

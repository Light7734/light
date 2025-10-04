//
#include <renderer/backend/vk/context/device.hpp>
#include <renderer/backend/vk/context/gpu.hpp>
#include <renderer/backend/vk/context/surface.hpp>
#include <renderer/backend/vk/utils.hpp>

//
#include <renderer/backend/vk/context/instance.hpp>

namespace lt::renderer::vk {

Device::Device(IGpu *gpu, ISurface *surface)
    : m_gpu(static_cast<Gpu *>(gpu))
    , m_surface(static_cast<Surface *>(surface))
{
	ensure(m_surface->vk(), "Failed to initialize vk::Device: null vulkan surface");

	initialize_queue_indices();
	initialize_logical_device();
	Instance::load_device_functions(m_device);

	vk_get_device_queue(m_device, m_graphics_queue_family_index, 0, &m_graphics_queue);
	vk_get_device_queue(m_device, m_present_queue_family_index, 0, &m_present_queue);

	if (m_present_queue == m_graphics_queue)
	{
		name(m_present_queue, "graphics|present queue");
	}
	else
	{
		name(m_graphics_queue, "graphics queue");
		name(m_present_queue, "present queue");
	}
}

Device::~Device()
{
	if (!m_gpu)
	{
		return;
	}

	vkc(vk_device_wait_idle(m_device));
	vk_destroy_device(m_device, nullptr);
}

void Device::initialize_logical_device()
{
	const float priorities = .0f;

	auto queue_infos = std::vector<VkDeviceQueueCreateInfo> {};
	auto queue_families = std::set { m_graphics_queue_family_index, m_present_queue_family_index };

	for (auto queue_family : queue_families)
	{
		queue_infos.emplace_back(
		    VkDeviceQueueCreateInfo {
		        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		        .queueFamilyIndex = queue_family,
		        .queueCount = 1u,
		        .pQueuePriorities = &priorities,
		    }
		);
	}

	auto physical_device_features = VkPhysicalDeviceFeatures {};

	auto extensions = std::vector<const char *> {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	auto device_info = VkDeviceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = static_cast<uint32_t>(queue_infos.size()),
		.pQueueCreateInfos = queue_infos.data(),
		.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
		.ppEnabledExtensionNames = extensions.data(),
		.pEnabledFeatures = &physical_device_features,
	};

	ensure(
	    !vk_create_device(m_gpu->vk(), &device_info, nullptr, &m_device),
	    "Failed to create logical vulkan device"
	);
}

void Device::initialize_queue_indices()
{
	auto properties = m_gpu->get_queue_family_properties();
	for (auto idx = uint32_t { 0u }; const auto &property : properties)
	{
		if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			m_graphics_queue_family_index = idx;
		}

		if (m_gpu->queue_family_supports_presentation(m_surface->vk(), idx))
		{
			m_present_queue_family_index = idx;
		}

		if (m_graphics_queue_family_index != VK_QUEUE_FAMILY_IGNORED
		    && m_present_queue_family_index != VK_QUEUE_FAMILY_IGNORED)
		{
			break;
		}

		++idx;
	}

	ensure(
	    m_graphics_queue_family_index != VK_QUEUE_FAMILY_IGNORED,
	    "Failed to find graphics queue family"
	);

	ensure(
	    m_present_queue_family_index != VK_QUEUE_FAMILY_IGNORED,
	    "Failed to find presentation queue family"
	);
}

void Device::submit(VkSubmitInfo info, VkFence fence) const
{
	vkc(vk_queue_submit(m_graphics_queue, 1u, &info, fence));
}

void Device::present(VkPresentInfoKHR info) const
{
	vk_queue_present_khr(m_present_queue, &info);
}

void Device::wait_idle() const
{
	vkc(vk_device_wait_idle(m_device));
}

void Device::wait_for_fence(VkFence fence) const
{
	vkc(vk_wait_for_fences(m_device, 1u, &fence, true, std::numeric_limits<uint64_t>::max()));
}

void Device::reset_fence(VkFence fence) const
{
	vkc(vk_reset_fences(m_device, 1u, &fence));
}

void Device::reset_fences(std::span<VkFence> fences) const
{
	vkc(vk_reset_fences(m_device, fences.size(), fences.data()));
}

auto Device::acquire_image(VkSwapchainKHR swapchain, VkSemaphore semaphore, uint64_t timeout)
    -> std::optional<uint32_t>
{
	auto image_idx = uint32_t {};
	const auto result = vk_acquire_next_image_khr(
	    m_device,
	    swapchain,
	    timeout,
	    semaphore,
	    VK_NULL_HANDLE,
	    &image_idx
	);

	if (result == VK_SUCCESS)
	{
		return image_idx;
	}

	if (result == VK_SUBOPTIMAL_KHR || result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		return {};
	}

	vkc(result); // throws
	return {};
}

void Device::wait_for_fences(std::span<VkFence> fences) const
{
	vkc(vk_wait_for_fences(
	    m_device,
	    fences.size(),
	    fences.data(),
	    true,
	    std::numeric_limits<uint64_t>::max()
	));
}

[[nodiscard]] auto Device::get_swapchain_images(VkSwapchainKHR swapchain) const
    -> std::vector<VkImage>
{
	auto count = uint32_t { 0u };
	vkc(vk_get_swapchain_images_khr(m_device, swapchain, &count, nullptr));
	ensure(count != 0u, "Failed to get swapchain images");

	auto images = std::vector<VkImage>(count);
	vkc(vk_get_swapchain_images_khr(m_device, swapchain, &count, images.data()));
	return images;
}

[[nodiscard]] auto Device::create_swapchain(VkSwapchainCreateInfoKHR info) const -> VkSwapchainKHR
{
	auto *swapchain = VkSwapchainKHR {};
	vkc(vk_create_swapchain_khr(m_device, &info, nullptr, &swapchain));
	return swapchain;
}

[[nodiscard]] auto Device::create_framebuffer(VkFramebufferCreateInfo info) const -> VkFramebuffer
{
	auto *framebuffer = VkFramebuffer {};
	vkc(vk_create_frame_buffer(m_device, &info, m_allocator, &framebuffer));
	return framebuffer;
}

[[nodiscard]] auto Device::create_image_view(VkImageViewCreateInfo info) const -> VkImageView
{
	auto *view = VkImageView {};
	vkc(vk_create_image_view(m_device, &info, m_allocator, &view));
	return view;
}

[[nodiscard]] auto Device::create_graphics_pipeline(VkGraphicsPipelineCreateInfo info) const
    -> VkPipeline
{
	auto *graphics_pipeline = VkPipeline {};
	vkc(vk_create_graphics_pipelines(
	    m_device,
	    VK_NULL_HANDLE,
	    1u,
	    &info,
	    m_allocator,
	    &graphics_pipeline

	));
	return graphics_pipeline;
}

[[nodiscard]] auto Device::create_pass(VkRenderPassCreateInfo info) const -> VkRenderPass
{
	auto *pass = VkRenderPass {};
	vkc(vk_create_render_pass(m_device, &info, nullptr, &pass));
	return pass;
}

[[nodiscard]] auto Device::create_pipeline_layout(VkPipelineLayoutCreateInfo info) const
    -> VkPipelineLayout
{
	auto *pipeline_layout = VkPipelineLayout {};
	vkc(vk_create_pipeline_layout(m_device, &info, nullptr, &pipeline_layout));
	return pipeline_layout;
}

[[nodiscard]] auto Device::create_shader_module(VkShaderModuleCreateInfo info) const
    -> VkShaderModule
{
	auto *module = VkShaderModule {};
	vkc(vk_create_shader_module(m_device, &info, m_allocator, &module));
	return module;
}

[[nodiscard]] auto Device::create_command_pool(VkCommandPoolCreateInfo info) const -> VkCommandPool
{
	auto *command_pool = VkCommandPool {};
	vkc(vk_create_command_pool(m_device, &info, m_allocator, &command_pool));
	return command_pool;
}

[[nodiscard]] auto Device::create_semaphores(uint32_t count) const -> std::vector<VkSemaphore>
{
	auto info = VkSemaphoreCreateInfo {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};

	auto semaphores = std::vector<VkSemaphore>(count);
	for (auto &semaphore : semaphores)
	{
		vk_create_semaphore(m_device, &info, m_allocator, &semaphore);
	}
	return semaphores;
}

[[nodiscard]] auto Device::create_fences(VkFenceCreateInfo info, uint32_t count) const
    -> std::vector<VkFence>
{
	auto fences = std::vector<VkFence>(count);
	for (auto &fence : fences)
	{
		vk_create_fence(m_device, &info, m_allocator, &fence);
	}
	return fences;
}

[[nodiscard]] auto Device::allocate_command_buffers(VkCommandBufferAllocateInfo info) const
    -> std::vector<VkCommandBuffer>
{
	auto command_buffers = std::vector<VkCommandBuffer>(info.commandBufferCount);
	vkc(vk_allocate_command_buffers(m_device, &info, command_buffers.data()));
	return command_buffers;
}

void Device::destroy_swapchain(VkSwapchainKHR swapchain) const
{
	vk_destroy_swapchain_khr(m_device, swapchain, m_allocator);
}

void Device::destroy_framebuffer(VkFramebuffer framebuffer) const
{
	vk_destroy_frame_buffer(m_device, framebuffer, m_allocator);
}

void Device::destroy_framebuffers(std::span<VkFramebuffer> framebuffers) const
{
	for (auto &framebuffer : framebuffers)
	{
		destroy_framebuffer(framebuffer);
	}
}

void Device::destroy_image_view(VkImageView image_view) const
{
	vk_destroy_image_view(m_device, image_view, m_allocator);
}

void Device::destroy_image_views(std::span<VkImageView> image_views) const
{
	for (auto &image_view : image_views)
	{
		destroy_image_view(image_view);
	}
}

void Device::destroy_pipeline(VkPipeline pipeline) const
{
	vk_destroy_pipeline(m_device, pipeline, m_allocator);
}

void Device::destroy_pass(VkRenderPass pass) const
{
	vk_destroy_render_pass(m_device, pass, m_allocator);
}

void Device::destroy_pipeline_layout(VkPipelineLayout pipeline_layout) const
{
	vk_destroy_pipeline_layout(m_device, pipeline_layout, m_allocator);
}

void Device::destroy_shader_module(VkShaderModule shader_module) const
{
	vk_destroy_shader_module(m_device, shader_module, m_allocator);
}

void Device::destroy_command_pool(VkCommandPool command_pool) const
{
	vk_destroy_command_pool(m_device, command_pool, m_allocator);
}

void Device::destroy_semaphore(VkSemaphore semaphore) const
{
	vk_destroy_semaphore(m_device, semaphore, m_allocator);
}

void Device::destroy_semaphores(std::span<VkSemaphore> semaphores) const
{
	for (auto &semaphore : semaphores)
	{
		destroy_semaphore(semaphore);
	}
}

void Device::destroy_fence(VkFence fence) const
{
	vk_destroy_fence(m_device, fence, m_allocator);
}

void Device::destroy_fences(std::span<VkFence> fences) const
{
	for (auto &fence : fences)
	{
		destroy_fence(fence);
	}
}

} // namespace lt::renderer::vk

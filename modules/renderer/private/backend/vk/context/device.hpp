#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/backend/vk/vulkan.hpp>
#include <renderer/frontend/context/device.hpp>
#include <renderer/frontend/context/gpu.hpp>
#include <renderer/frontend/context/surface.hpp>

namespace lt::renderer::vk {

class Device: public IDevice
{
public:
	Device(IGpu *gpu, ISurface *surface);

	~Device() override;

	Device(Device &&) = default;

	Device(const Device &) = delete;

	auto operator=(Device &&) -> Device & = default;

	auto operator=(const Device &) const -> Device & = delete;

	[[nodiscard]] auto vk() const -> VkDevice
	{
		return m_device;
	}

	[[nodiscard]] auto get_family_indices() const -> std::array<uint32_t, 2>
	{
		return { m_graphics_queue_family_index, m_present_queue_family_index };
	}

	[[nodiscard]] auto get_graphics_queue() const -> VkQueue
	{
		return m_graphics_queue;
	}

	[[nodiscard]] auto get_present_queue() const -> VkQueue
	{
		return m_present_queue;
	}

	/** utilities */
	template<typename T, typename... Args>
	void name(const T &object, std::format_string<Args...> fmt, Args &&...args)
	{
		const auto name = std::format(fmt, std::forward<Args>(args)...);
		auto info = VkDebugUtilsObjectNameInfoEXT {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
			.objectType = get_object_type(object),
			.objectHandle = (uint64_t)(object),
			.pObjectName = name.c_str(),
		};

		vk_set_debug_object_name(m_device, &info);
	}

	template<typename T>
	void name(const T &object, const char *name)
	{
		auto info = VkDebugUtilsObjectNameInfoEXT {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
			.objectType = get_object_type(object),
			.objectHandle = (uint64_t)(object),
			.pObjectName = name,
		};

		vk_set_debug_object_name(m_device, &info);
	}


	/** work functions */
	void submit(VkSubmitInfo info, VkFence fence) const;

	void present(VkPresentInfoKHR info) const;

	void wait_idle() const;

	void wait_for_fence(VkFence fence) const;

	void wait_for_fences(std::span<VkFence> fences) const;

	void reset_fence(VkFence fence) const;

	void reset_fences(std::span<VkFence> fences) const;

	/** getter functions */
	[[nodiscard]] auto acquire_image(
	    VkSwapchainKHR swapchain,
	    VkSemaphore semaphore,
	    uint64_t timeout = 1'000'000
	) -> std::optional<uint32_t>;

	[[nodiscard]] auto get_swapchain_images(VkSwapchainKHR swapchain) const -> std::vector<VkImage>;

	/** create functions */
	[[nodiscard]] auto create_swapchain(VkSwapchainCreateInfoKHR info) const -> VkSwapchainKHR;

	[[nodiscard]] auto create_framebuffer(VkFramebufferCreateInfo info) const -> VkFramebuffer;

	[[nodiscard]] auto create_image_view(VkImageViewCreateInfo info) const -> VkImageView;

	[[nodiscard]] auto create_graphics_pipeline(VkGraphicsPipelineCreateInfo info) const
	    -> VkPipeline;

	[[nodiscard]] auto create_pass(VkRenderPassCreateInfo info) const -> VkRenderPass;

	[[nodiscard]] auto create_pipeline_layout(VkPipelineLayoutCreateInfo info) const
	    -> VkPipelineLayout;

	[[nodiscard]] auto create_shader_module(VkShaderModuleCreateInfo info) const -> VkShaderModule;

	[[nodiscard]] auto create_command_pool(VkCommandPoolCreateInfo info) const -> VkCommandPool;

	[[nodiscard]] auto create_semaphores(uint32_t count) const -> std::vector<VkSemaphore>;

	[[nodiscard]] auto create_fences(VkFenceCreateInfo info, uint32_t count) const
	    -> std::vector<VkFence>;

	/** allocation functions */
	[[nodiscard]] auto allocate_command_buffers(VkCommandBufferAllocateInfo info) const
	    -> std::vector<VkCommandBuffer>;

	/** destroy functions */
	void destroy_swapchain(VkSwapchainKHR swapchain) const;

	void destroy_framebuffer(VkFramebuffer framebuffer) const;

	void destroy_framebuffers(std::span<VkFramebuffer> framebuffers) const;

	void destroy_image_view(VkImageView image_view) const;

	void destroy_image_views(std::span<VkImageView> image_views) const;

	void destroy_pipeline(VkPipeline pipeline) const;

	void destroy_pass(VkRenderPass pass) const;

	void destroy_pipeline_layout(VkPipelineLayout pipeline_layout) const;

	void destroy_shader_module(VkShaderModule shader_module) const;

	void destroy_command_pool(VkCommandPool command_pool) const;

	void destroy_semaphore(VkSemaphore semaphore) const;

	void destroy_semaphores(std::span<VkSemaphore> semaphores) const;

	void destroy_fence(VkFence fence) const;

	void destroy_fences(std::span<VkFence> fences) const;

private:
	template<typename T>
	static auto get_object_type(const T &object) -> VkObjectType
	{
		std::ignore = object;

		if constexpr (std::is_same_v<T, VkQueue>)
		{
			return VK_OBJECT_TYPE_QUEUE;
		}

		if constexpr (std::is_same_v<T, VkFence>)
		{
			return VK_OBJECT_TYPE_FENCE;
		}

		if constexpr (std::is_same_v<T, VkSemaphore>)
		{
			return VK_OBJECT_TYPE_SEMAPHORE;
		}

		if constexpr (std::is_same_v<T, VkSwapchainKHR>)
		{
			return VK_OBJECT_TYPE_SWAPCHAIN_KHR;
		}

		if constexpr (std::is_same_v<T, VkImage>)
		{
			return VK_OBJECT_TYPE_IMAGE;
		}

		if constexpr (std::is_same_v<T, VkImageView>)
		{
			return VK_OBJECT_TYPE_IMAGE_VIEW;
		}

		static_assert("invalid type");
	}


	void initialize_physical_device();

	void initialize_logical_device();

	void initialize_queue_indices();

	[[nodiscard]] auto find_suitable_queue_family() const -> uint32_t;

	memory::NullOnMove<class Gpu *> m_gpu {};

	class Surface *m_surface {};

	VkAllocationCallbacks *m_allocator = nullptr;

	VkDevice m_device = VK_NULL_HANDLE;

	VkQueue m_graphics_queue = VK_NULL_HANDLE;

	VkQueue m_present_queue = VK_NULL_HANDLE;

	uint32_t m_graphics_queue_family_index = VK_QUEUE_FAMILY_IGNORED;

	uint32_t m_present_queue_family_index = VK_QUEUE_FAMILY_IGNORED;
};

} // namespace lt::renderer::vk

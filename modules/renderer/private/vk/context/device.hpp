#pragma once

#include <memory/pointer_types/null_on_move.hpp>
#include <renderer/vk/vulkan.hpp>

namespace lt::renderer::vk {

class Device
{
public:
	Device(const class Surface &surface);

	~Device();

	Device(Device &&) = default;

	Device(const Device &) = delete;

	auto operator=(Device &&) -> Device & = default;

	auto operator=(const Device &) const -> Device & = delete;

	[[nodiscard]] auto vk() const -> VkDevice
	{
		return m_device;
	}

	[[nodiscard]] auto physical() const -> VkPhysicalDevice
	{
		return m_physical_device;
	}

	[[nodiscard]] auto get_family_indices() const -> std::array<uint32_t, 2>
	{
		return { m_graphics_queue_family_index, m_present_queue_family_index };
	}

private:
	void initialize_physical_device();

	void initialize_logical_device();

	void initialize_queue(const class Surface &surface);

	[[nodiscard]] auto find_suitable_queue_family() const -> uint32_t;

	// logical device
	memory::NullOnMove<VkPhysicalDevice> m_physical_device = VK_NULL_HANDLE;

	memory::NullOnMove<VkDevice> m_device = VK_NULL_HANDLE;

	memory::NullOnMove<VkQueue> m_queue = VK_NULL_HANDLE;

	uint32_t m_graphics_queue_family_index = VK_QUEUE_FAMILY_IGNORED;

	uint32_t m_present_queue_family_index = VK_QUEUE_FAMILY_IGNORED;
};

} // namespace lt::renderer::vk

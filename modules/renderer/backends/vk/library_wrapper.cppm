module;
#define VK_NO_PROTOTYPES
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_xlib.h>

#if defined(_WIN32)
	#error "Unsupported platform"
#elif defined(__unix__)
	#include <dlfcn.h>
#endif

export module renderer.backend.vk.library_wrapper;
import memory.null_on_move;
import math.vec3;
import debug.assertions;
import std;

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

export namespace lt::renderer::vk {

using Bool32 = VkBool32;

namespace constants {

constexpr auto application_version = VK_MAKE_VERSION(1, 0, 0);
constexpr auto engine_version = VK_MAKE_VERSION(1, 0, 0);
constexpr auto api_version = VK_API_VERSION_1_4;
constexpr auto engine_name = std::string_view { "light_engine_vulkan_renderer" };

constexpr auto max_physical_device_name = VK_MAX_PHYSICAL_DEVICE_NAME_SIZE;
constexpr auto max_memory_types = VK_MAX_MEMORY_TYPES;
constexpr auto max_memory_heaps = VK_MAX_MEMORY_HEAPS;
constexpr auto uuid_size = VK_UUID_SIZE;

} // namespace constants


namespace instance_layer_names {

constexpr auto validation = "VK_LAYER_KHRONOS_validation";

}

namespace instance_extension_names {

constexpr auto debug_utils = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
constexpr auto surface = VK_KHR_SURFACE_EXTENSION_NAME;
constexpr auto xlib_surface = VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
constexpr auto physical_device_properties_2
    = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;

} // namespace instance_extension_names

namespace device_extension_names {

constexpr auto xlib_surface = VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
constexpr auto swapchain = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
constexpr auto dynamic_rendering = VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME;
constexpr auto descriptor_indexing = VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME;

}; // namespace device_extension_names


void load_library();

void unload_library();

void load_global_functions();

void load_device_functions(VkDevice device);

using Version_T = uint32_t;

struct ApplicationInfo
{
	std::string_view name;

	Version_T version;

	std::string_view engine_name;

	Version_T engine_version;

	Version_T api_version;
};

namespace QueueFlags {
enum T : std::underlying_type_t<VkQueueFlagBits> // NOLINT
{
	graphics_bit = VK_QUEUE_GRAPHICS_BIT,
	compute_bit = VK_QUEUE_COMPUTE_BIT,
	transfer_bit = VK_QUEUE_TRANSFER_BIT,
	sparse_binding_bit = VK_QUEUE_SPARSE_BINDING_BIT,
	protected_bit = VK_QUEUE_PROTECTED_BIT,
	video_decode_bit_khr = VK_QUEUE_VIDEO_DECODE_BIT_KHR,
	video_encode_bit_khr = VK_QUEUE_VIDEO_ENCODE_BIT_KHR,
	optical_flow_bit_nv = VK_QUEUE_OPTICAL_FLOW_BIT_NV,
};
}

namespace MemoryHeapFlags {
enum T : std::underlying_type_t<VkMemoryHeapFlagBits> // NOLINT
{

	device_local_bit = VK_MEMORY_HEAP_DEVICE_LOCAL_BIT,
	multi_instance_bit = VK_MEMORY_HEAP_MULTI_INSTANCE_BIT,
	tile_memory_bit = VK_MEMORY_HEAP_TILE_MEMORY_BIT_QCOM,
};
};

namespace MemoryPropertyFlags {
enum T : std::underlying_type_t<VkMemoryPropertyFlagBits> // NOLINT
{

	device_local_bit = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
	host_visible_bit = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
	host_coherent_bit = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
	host_cached_bit = VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
	lazily_allocated_bit = VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT,
	protected_bit = VK_MEMORY_PROPERTY_PROTECTED_BIT,
	device_coherent_bit_amd = VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD,
	device_uncached_bit_amd = VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD,
	rdma_capable_bit_nv = VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV,
};
}

class Instance
{
public:
	friend class Surface;
	friend class Gpu;

	struct Layer
	{
		struct Setting
		{
			std::string name;
			std::variant<std::vector<const char *>, std::uint32_t, bool> values;
		};

		std::string name;

		std::vector<Setting> settings;
	};

	using Extension = std::string;

	struct CreateInfo
	{
		ApplicationInfo application_info;

		std::vector<Layer> layers;

		std::vector<Extension> extensions;
	};

	Instance() = default;

	Instance(CreateInfo info);

	Instance(Instance &&) = default;

	Instance(const Instance &) = delete;

	auto operator=(Instance &&) -> Instance & = default;

	auto operator=(const Instance &) = delete;

	~Instance();

	void load_functions();

	[[nodiscard]] operator bool() const
	{
		return m_instance != VK_NULL_HANDLE;
	}

private:
	memory::NullOnMove<VkInstance> m_instance {};
};

class Surface
{
public:
	friend class Gpu;

	struct XlibCreateInfo
	{
		Display *display;

		Window window;
	};

	Surface() = default;

	Surface(const Instance &instance, const XlibCreateInfo &info);

	Surface(Surface &&) = default;

	Surface(const Surface &) = delete;

	auto operator=(Surface &&) -> Surface & = default;

	auto operator=(const Surface &) -> Surface & = delete;

	~Surface();

	[[nodiscard]] operator bool() const
	{
		return m_surface != VK_NULL_HANDLE;
	}

private:
	memory::NullOnMove<VkSurfaceKHR> m_surface {};

	VkInstance m_instance {};
};

class Gpu
{
public:
	enum class Type : uint8_t
	{
		other = 0,
		integrated_gpu = 1,
		discrete_gpu = 2,
		virtual_gpu = 3,
		cpu = 4,
	};

	struct Features
	{
		Bool32 robust_buffer_access;
		Bool32 full_draw_index_uint32;
		Bool32 image_cube_array;
		Bool32 independent_blend;
		Bool32 geometry_shader;
		Bool32 tessellation_shader;
		Bool32 sample_rate_shading;
		Bool32 dual_src_blend;
		Bool32 logic_op;
		Bool32 multi_draw_indirect;
		Bool32 draw_indirect_first_instance;
		Bool32 depth_clamp;
		Bool32 depth_bias_clamp;
		Bool32 fill_mode_non_solid;
		Bool32 depth_bounds;
		Bool32 wide_lines;
		Bool32 large_points;
		Bool32 alpha_to_one;
		Bool32 multi_viewport;
		Bool32 sampler_anisotropy;
		Bool32 texture_compression_etc2;
		Bool32 texture_compression_astc_ldr;
		Bool32 texture_compression_bc;
		Bool32 occlusion_query_precise;
		Bool32 pipeline_statistics_query;
		Bool32 vertex_pipeline_stores_and_atomics;
		Bool32 fragment_stores_and_atomics;
		Bool32 shader_tessellation_and_geometry_point_size;
		Bool32 shader_image_gather_extended;
		Bool32 shader_storage_image_extended_formats;
		Bool32 shader_storage_image_multisample;
		Bool32 shader_storage_image_read_without_format;
		Bool32 shader_storage_image_write_without_format;
		Bool32 shader_uniform_buffer_array_dynamic_indexing;
		Bool32 shader_sampled_image_array_dynamic_indexing;
		Bool32 shader_storage_buffer_array_dynamic_indexing;
		Bool32 shader_storage_image_array_dynamic_indexing;
		Bool32 shader_clip_distance;
		Bool32 shader_cull_distance;
		Bool32 shader_float64;
		Bool32 shader_int64;
		Bool32 shader_int16;
		Bool32 shader_resource_residency;
		Bool32 shader_resource_min_lod;
		Bool32 sparse_binding;
		Bool32 sparse_residency_buffer;
		Bool32 sparse_residency_image_2d;
		Bool32 sparse_residency_image_3d;
		Bool32 sparse_residency_2_samples;
		Bool32 sparse_residency_4_samples;
		Bool32 sparse_residency_8_samples;
		Bool32 sparse_residency_16_samples;
		Bool32 sparse_residency_aliased;
		Bool32 variable_multisample_rate;
		Bool32 inherited_queries;
	};

	struct Limits
	{
		std::uint32_t max_image_dimension_1d;
		std::uint32_t max_image_dimension_2d;
		std::uint32_t max_image_dimension_3d;
		std::uint32_t max_image_dimension_cube;
		std::uint32_t max_image_array_layers;
		std::uint32_t max_texel_buffer_elements;
		std::uint32_t max_uniform_buffer_range;
		std::uint32_t max_storage_buffer_range;
		std::uint32_t max_push_constants_size;
		std::uint32_t max_memory_allocation_count;
		std::uint32_t max_sampler_allocation_count;
		std::size_t buffer_image_granularity;
		std::size_t sparse_address_space_size;
		std::uint32_t max_bound_descriptor_sets;
		std::uint32_t max_per_stage_descriptor_samplers;
		std::uint32_t max_per_stage_descriptor_uniform_buffers;
		std::uint32_t max_per_stage_descriptor_storage_buffers;
		std::uint32_t max_per_stage_descriptor_sampled_images;
		std::uint32_t max_per_stage_descriptor_storage_images;
		std::uint32_t max_per_stage_descriptor_input_attachments;
		std::uint32_t max_per_stage_resources;
		std::uint32_t max_descriptor_set_samplers;
		std::uint32_t max_descriptor_set_uniform_buffers;
		std::uint32_t max_descriptor_set_uniform_buffers_dynamic;
		std::uint32_t max_descriptor_set_storage_buffers;
		std::uint32_t max_descriptor_set_storage_buffers_dynamic;
		std::uint32_t max_descriptor_set_sampled_images;
		std::uint32_t max_descriptor_set_storage_images;
		std::uint32_t max_descriptor_set_input_attachments;
		std::uint32_t max_vertex_input_attributes;
		std::uint32_t max_vertex_input_bindings;
		std::uint32_t max_vertex_input_attribute_offset;
		std::uint32_t max_vertex_input_binding_stride;
		std::uint32_t max_vertex_output_components;
		std::uint32_t max_tessellation_generation_level;
		std::uint32_t max_tessellation_patch_size;
		std::uint32_t max_tessellation_control_per_vertex_input_components;
		std::uint32_t max_tessellation_control_per_vertex_output_components;
		std::uint32_t max_tessellation_control_per_patch_output_components;
		std::uint32_t max_tessellation_control_total_output_components;
		std::uint32_t max_tessellation_evaluation_input_components;
		std::uint32_t max_tessellation_evaluation_output_components;
		std::uint32_t max_geometry_shader_invocations;
		std::uint32_t max_geometry_input_components;
		std::uint32_t max_geometry_output_components;
		std::uint32_t max_geometry_output_vertices;
		std::uint32_t max_geometry_total_output_components;
		std::uint32_t max_fragment_input_components;
		std::uint32_t max_fragment_output_attachments;
		std::uint32_t max_fragment_dual_src_attachments;
		std::uint32_t max_fragment_combined_output_resources;
		std::uint32_t max_compute_shared_memory_size;
		std::array<std::uint32_t, 3> max_compute_work_group_count;
		std::uint32_t max_compute_work_group_invocations;
		std::array<std::uint32_t, 3> max_compute_work_group_size;
		std::uint32_t sub_pixel_precision_bits;
		std::uint32_t sub_texel_precision_bits;
		std::uint32_t mipmap_precision_bits;
		std::uint32_t max_draw_indexed_index_value;
		std::uint32_t max_draw_indirect_count;
		float max_sampler_lod_bias;
		float max_sampler_anisotropy;
		std::uint32_t max_viewports;
		std::array<std::uint32_t, 2> max_viewport_dimensions;
		std::array<float, 2> viewport_bounds_range;
		std::uint32_t viewport_sub_pixel_bits;
		std::size_t min_memory_map_alignment;
		VkDeviceSize min_texel_buffer_offset_alignment;
		VkDeviceSize min_uniform_buffer_offset_alignment;
		VkDeviceSize min_storage_buffer_offset_alignment;
		std::int32_t min_texel_offset;
		std::uint32_t max_texel_offset;
		std::int32_t min_texel_gather_offset;
		std::uint32_t max_texel_gather_offset;
		float min_interpolation_offset;
		float max_interpolation_offset;
		std::uint32_t sub_pixel_interpolation_offset_bits;
		std::uint32_t max_framebuffer_width;
		std::uint32_t max_framebuffer_height;
		std::uint32_t max_framebuffer_layers;
		VkSampleCountFlags framebuffer_color_sample_counts;
		VkSampleCountFlags framebuffer_depth_sample_counts;
		VkSampleCountFlags framebuffer_stencil_sample_counts;
		VkSampleCountFlags framebuffer_no_attachments_sample_counts;
		std::uint32_t max_color_attachments;
		VkSampleCountFlags sampled_image_color_sample_counts;
		VkSampleCountFlags sampled_image_integer_sample_counts;
		VkSampleCountFlags sampled_image_depth_sample_counts;
		VkSampleCountFlags sampled_image_stencil_sample_counts;
		VkSampleCountFlags storage_image_sample_counts;
		std::uint32_t max_sample_mask_words;
		Bool32 timestamp_compute_and_graphics;
		float timestamp_period;
		std::uint32_t max_clip_distances;
		std::uint32_t max_cull_distances;
		std::uint32_t max_combined_clip_and_cull_distances;
		std::uint32_t discrete_queue_priorities;
		std::array<float, 2> point_size_range;
		std::array<float, 2> line_width_range;
		float point_size_granularity;
		float line_width_granularity;
		Bool32 strict_lines;
		Bool32 standard_sample_locations;
		std::size_t optimal_buffer_copy_offset_alignment;
		std::size_t optimal_buffer_copy_row_pitch_alignment;
		std::size_t non_coherent_atom_size;
	};

	struct SparseProperties
	{
		Bool32 residency_standard_2d_block_shape;
		Bool32 residency_standard_2d_multisample_block_shape;
		Bool32 residency_standard_3d_block_shape;
		Bool32 residency_aligned_mip_size;
		Bool32 residency_non_resident_strict;
	};

	struct Properties
	{
		std::uint32_t api_version;
		std::uint32_t driver_version;
		std::uint32_t vendor_id;
		std::uint32_t device_id;
		Type device_type;
		std::array<char, constants::max_physical_device_name> device_name;
		std::array<std::uint8_t, constants::uuid_size> pipeline_cache_uuid;
		Limits limits;
		SparseProperties sparse_properties;
	};

	struct MemoryType
	{
		MemoryPropertyFlags::T property_flags;
		std::uint32_t heap_idx;
	};

	struct MemoryHeap
	{
		std::size_t size;
		MemoryHeapFlags::T flags;
	};

	struct MemoryProperties
	{
		std::uint32_t memory_type_count;
		std::array<MemoryType, constants::max_memory_types> memory_types;

		std::uint32_t memory_heap_count;
		std::array<MemoryHeap, constants::max_memory_heaps> memory_heaps;
	};

	struct QueueFamilyProperties
	{
		QueueFlags::T queue_flags {};
		std::uint32_t queue_count {};
		std::uint32_t timestamp_valid_bits {};
		math::uvec3 min_image_transfer_granularity;
	};

	[[nodiscard]]
	static auto enumerate(const Instance &instance) -> std::vector<Gpu>;

	Gpu() = default;

	Gpu(Gpu &&) = default;

	Gpu(const Gpu &) = default;

	auto operator=(Gpu &&) -> Gpu & = default;

	auto operator=(const Gpu &) -> Gpu & = default;

	~Gpu();

	[[nodiscard]] auto get_properties() const -> Properties;

	[[nodiscard]] auto get_features() const -> Features;

	[[nodiscard]] auto get_memory_properties() const -> MemoryProperties;

	[[nodiscard]] auto get_queue_family_properties() const -> std::vector<QueueFamilyProperties>;

	[[nodiscard]] auto queue_family_supports_surface(
	    const Surface &surface,
	    std::uint32_t queue_family_idx
	) const -> bool;

	[[nodiscard]] operator bool() const
	{
		return m_physical_device != VK_NULL_HANDLE;
	}

private:
	VkPhysicalDevice m_physical_device {};

	VkInstance m_instance {};
};

class Device
{
public:
	struct CreateInfo
	{
		std::set<std::uint32_t> queue_indices;

		std::vector<std::string> extensions;

		Gpu::Features required_gpu_features;
	};

	Device() = default;

	Device(CreateInfo info);

	Device(Device &&) = default;

	Device(const Device &) = delete;

	auto operator=(Device &&) -> Device & = default;

	auto operator=(const Device &) -> Device & = delete;

	~Device();

private:
	memory::NullOnMove<VkDevice> m_device {};
};

[[nodiscard]]
auto enumerate_instance_extension_properties() -> std::vector<VkExtensionProperties>;


} // namespace lt::renderer::vk

module :private;
using namespace lt::renderer::vk;

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// global functions
PFN_vkGetInstanceProcAddr vk_get_instance_proc_address {};
PFN_vkCreateInstance vk_create_instance {};
PFN_vkEnumerateInstanceExtensionProperties vk_enumerate_instance_extension_properties {};
PFN_vkEnumerateInstanceLayerProperties vk_enumerate_instance_layer_properties {};

// instance functions
PFN_vkDestroyInstance vk_destroy_instance {};
PFN_vkEnumeratePhysicalDevices vk_enumerate_physical_devices {};

PFN_vkGetPhysicalDeviceProperties vk_get_physical_device_properties {};
PFN_vkGetPhysicalDeviceQueueFamilyProperties vk_get_physical_device_queue_family_properties {};
PFN_vkCreateDevice vk_create_device {};
PFN_vkGetDeviceProcAddr vk_get_device_proc_address {};
PFN_vkDestroyDevice vk_destroy_device {};
PFN_vkGetPhysicalDeviceFeatures2 vk_get_physical_device_features {};
PFN_vkEnumerateDeviceExtensionProperties vk_enumerate_device_extension_properties {};
PFN_vkGetPhysicalDeviceMemoryProperties vk_get_physical_device_memory_properties {};

// extension instance functions
PFN_vkCmdBeginDebugUtilsLabelEXT vk_cmd_begin_debug_label {};
PFN_vkCmdEndDebugUtilsLabelEXT vk_cmd_end_debug_label {};
PFN_vkCmdInsertDebugUtilsLabelEXT vk_cmd_insert_debug_label {};
PFN_vkCreateDebugUtilsMessengerEXT vk_create_debug_messenger {};
PFN_vkDestroyDebugUtilsMessengerEXT vk_destroy_debug_messenger {};
PFN_vkQueueBeginDebugUtilsLabelEXT vk_queue_begin_debug_label {};
PFN_vkQueueEndDebugUtilsLabelEXT vk_queue_end_debug_label {};
PFN_vkQueueInsertDebugUtilsLabelEXT vk_queue_insert_debug_label {};
PFN_vkSetDebugUtilsObjectNameEXT vk_set_debug_object_name {};
PFN_vkSetDebugUtilsObjectTagEXT vk_set_debug_object_tag {};
PFN_vkSubmitDebugUtilsMessageEXT vk_submit_debug_message {};

// surface instance functions
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vk_get_physical_device_surface_support {};
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vk_get_physical_device_surface_capabilities {};
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vk_get_physical_device_surface_formats {};

// device functions
PFN_vkGetDeviceQueue vk_get_device_queue {};
PFN_vkCreateCommandPool vk_create_command_pool {};
PFN_vkDestroyCommandPool vk_destroy_command_pool {};
PFN_vkAllocateCommandBuffers vk_allocate_command_buffers {};
PFN_vkFreeCommandBuffers vk_free_command_buffers {};
PFN_vkBeginCommandBuffer vk_begin_command_buffer {};
PFN_vkEndCommandBuffer vk_end_command_buffer {};
PFN_vkCmdPipelineBarrier vk_cmd_pipeline_barrier {};
PFN_vkQueueSubmit vk_queue_submit {};
PFN_vkQueueWaitIdle vk_queue_wait_idle {};
PFN_vkDeviceWaitIdle vk_device_wait_idle {};
PFN_vkCreateFence vk_create_fence {};
PFN_vkDestroyFence vk_destroy_fence {};
PFN_vkWaitForFences vk_wait_for_fences {};
PFN_vkResetFences vk_reset_fences {};
PFN_vkCreateSemaphore vk_create_semaphore {};
PFN_vkDestroySemaphore vk_destroy_semaphore {};
PFN_vkCreateSwapchainKHR vk_create_swapchain_khr {};
PFN_vkDestroySwapchainKHR vk_destroy_swapchain_khr {};
PFN_vkGetSwapchainImagesKHR vk_get_swapchain_images_khr {};
PFN_vkAcquireNextImageKHR vk_acquire_next_image_khr {};
PFN_vkQueuePresentKHR vk_queue_present_khr {};
PFN_vkCreateImageView vk_create_image_view {};
PFN_vkDestroyImageView vk_destroy_image_view {};
PFN_vkCreateRenderPass vk_create_render_pass {};
PFN_vkDestroyRenderPass vk_destroy_render_pass {};
PFN_vkCreateFramebuffer vk_create_frame_buffer {};
PFN_vkDestroyFramebuffer vk_destroy_frame_buffer {};
PFN_vkCreateShaderModule vk_create_shader_module {};
PFN_vkDestroyShaderModule vk_destroy_shader_module {};
PFN_vkCreatePipelineLayout vk_create_pipeline_layout {};
PFN_vkDestroyPipelineLayout vk_destroy_pipeline_layout {};
PFN_vkCreateGraphicsPipelines vk_create_graphics_pipelines {};
PFN_vkDestroyPipeline vk_destroy_pipeline {};
PFN_vkCmdBeginRenderPass vk_cmd_begin_render_pass {};
PFN_vkCmdEndRenderPass vk_cmd_end_render_pass {};
PFN_vkCmdBindPipeline vk_cmd_bind_pipeline {};
PFN_vkCmdDraw vk_cmd_draw {};
PFN_vkCmdSetViewport vk_cmd_set_viewport {};
PFN_vkCmdSetScissor vk_cmd_set_scissors {};
PFN_vkCmdPushConstants vk_cmd_push_constants {};
PFN_vkCmdCopyBuffer vk_cmd_copy_buffer {};

PFN_vkCreateDescriptorSetLayout vk_create_descriptor_set_layout {};
PFN_vkDestroyDescriptorSetLayout vk_destroy_descriptor_set_layout {};
PFN_vkCreateDescriptorPool vk_create_descriptor_pool {};
PFN_vkDestroyDescriptorPool vk_destroy_descriptor_pool {};
PFN_vkAllocateDescriptorSets vk_allocate_descriptor_sets {};
PFN_vkFreeDescriptorSets vk_free_descriptor_sets {};

PFN_vkCreateBuffer vk_create_buffer {};
PFN_vkDestroyBuffer vk_destroy_buffer {};
PFN_vkGetBufferMemoryRequirements vk_get_buffer_memory_requirements {};
PFN_vkAllocateMemory vk_allocate_memory {};
PFN_vkBindBufferMemory vk_bind_buffer_memory {};
PFN_vkMapMemory vk_map_memory {};
PFN_vkUnmapMemory vk_unmap_memory {};
PFN_vkFreeMemory vk_free_memory {};

PFN_vkResetCommandBuffer vk_reset_command_buffer {};

PFN_vkCmdBeginRendering vk_cmd_begin_rendering {};
PFN_vkCmdEndRendering vk_cmd_end_rendering {};

PFN_vkCreateXlibSurfaceKHR vk_create_xlib_surface_khr {};
PFN_vkDestroySurfaceKHR vk_destroy_surface_khr {};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

namespace {
void *library = nullptr; // NOLINT
}

void load_library()
{
	constexpr auto runtime_loader_flags = RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE;
	library = dlopen("libvulkan.so.1", runtime_loader_flags);
	if (!library)
	{
		library = dlopen("libvulkan.so", runtime_loader_flags);
	}
	lt::debug::ensure(library, "Failed to dlopen vulkan library");

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	vk_get_instance_proc_address = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
	    dlsym(library, "vkGetInstanceProcAddr")
	);
	lt::debug::ensure(
	    vk_get_instance_proc_address,
	    "Failed to load vulkan function: vkGetInstanceProcAddr"
	);
}

void vkc(VkResult result)
{
	if (result)
	{
		throw std::runtime_error {
			std::format("Vulkan call failed with result: {}", std::to_underlying(result))
		};
	}
}

void unload_library()
{
	if (!library)
	{
		return;
	}

	// calling dlclose causes many issues with runtime analyzers
	// eg. https://github.com/google/sanitizers/issues/89
	// with no noticable gains, so we just don't bother closing it.

	// dlclose(library);
	// library = nullptr;
}

void load_global_functions()
{
	constexpr auto load_fn = []<typename T>(T &pfn, const char *fn_name) {
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		pfn = reinterpret_cast<T>(vk_get_instance_proc_address(nullptr, fn_name));
		lt::debug::ensure(pfn, "Failed to load vulkan global function: {}", fn_name);
		// log::trace("Loaded global function: {}", fn_name);
	};

	load_fn(vk_create_instance, "vkCreateInstance");
	load_fn(vk_enumerate_instance_extension_properties, "vkEnumerateInstanceExtensionProperties");
	load_fn(vk_enumerate_instance_layer_properties, "vkEnumerateInstanceLayerProperties");
}

void Instance::load_functions()
{
	const auto load_fn = [this]<typename T>(T &pfn, const char *fn_name) {
		pfn = std::bit_cast<T>(vk_get_instance_proc_address(m_instance, fn_name));
		lt::debug::ensure(pfn, "Failed to load vulkan instance function: {}", fn_name);
	};

	load_fn(vk_destroy_instance, "vkDestroyInstance");
	load_fn(vk_enumerate_physical_devices, "vkEnumeratePhysicalDevices");
	load_fn(vk_get_physical_device_properties, "vkGetPhysicalDeviceProperties");
	load_fn(
	    vk_get_physical_device_queue_family_properties,
	    "vkGetPhysicalDeviceQueueFamilyProperties"
	);
	load_fn(vk_create_device, "vkCreateDevice");
	load_fn(vk_get_device_proc_address, "vkGetDeviceProcAddr");
	load_fn(vk_destroy_device, "vkDestroyDevice");
	load_fn(vk_get_physical_device_features, "vkGetPhysicalDeviceFeatures");
	load_fn(vk_enumerate_device_extension_properties, "vkEnumerateDeviceExtensionProperties");
	load_fn(vk_get_physical_device_memory_properties, "vkGetPhysicalDeviceMemoryProperties");

	load_fn(vk_cmd_begin_debug_label, "vkCmdBeginDebugUtilsLabelEXT");
	load_fn(vk_cmd_end_debug_label, "vkCmdEndDebugUtilsLabelEXT");
	load_fn(vk_cmd_insert_debug_label, "vkCmdInsertDebugUtilsLabelEXT");
	load_fn(vk_create_debug_messenger, "vkCreateDebugUtilsMessengerEXT");
	load_fn(vk_destroy_debug_messenger, "vkDestroyDebugUtilsMessengerEXT");
	load_fn(vk_queue_begin_debug_label, "vkQueueBeginDebugUtilsLabelEXT");
	load_fn(vk_queue_end_debug_label, "vkQueueEndDebugUtilsLabelEXT");
	load_fn(vk_queue_insert_debug_label, "vkQueueInsertDebugUtilsLabelEXT");
	load_fn(vk_set_debug_object_name, "vkSetDebugUtilsObjectNameEXT");
	load_fn(vk_set_debug_object_tag, "vkSetDebugUtilsObjectTagEXT");
	load_fn(vk_submit_debug_message, "vkSubmitDebugUtilsMessageEXT");

	load_fn(vk_get_physical_device_surface_support, "vkGetPhysicalDeviceSurfaceSupportKHR");
	load_fn(
	    vk_get_physical_device_surface_capabilities,
	    "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"
	);
	load_fn(vk_get_physical_device_surface_formats, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	load_fn(vk_create_xlib_surface_khr, "vkCreateXlibSurfaceKHR");
	load_fn(vk_destroy_surface_khr, "vkDestroySurfaceKHR");
}

void load_device_functions(VkDevice device)
{
	const auto load_fn = [device]<typename T>(T &pfn, const char *fn_name) {
		pfn = std::bit_cast<T>(vk_get_device_proc_address(device, fn_name));
		lt::debug::ensure(pfn, "Failed to load vulkan device function: {}", fn_name);
	};

	load_fn(vk_get_device_queue, "vkGetDeviceQueue");
	load_fn(vk_create_command_pool, "vkCreateCommandPool");
	load_fn(vk_destroy_command_pool, "vkDestroyCommandPool");
	load_fn(vk_allocate_command_buffers, "vkAllocateCommandBuffers");
	load_fn(vk_free_command_buffers, "vkFreeCommandBuffers");
	load_fn(vk_begin_command_buffer, "vkBeginCommandBuffer");
	load_fn(vk_end_command_buffer, "vkEndCommandBuffer");
	load_fn(vk_cmd_pipeline_barrier, "vkCmdPipelineBarrier");
	load_fn(vk_queue_submit, "vkQueueSubmit");
	load_fn(vk_queue_wait_idle, "vkQueueWaitIdle");
	load_fn(vk_device_wait_idle, "vkDeviceWaitIdle");
	load_fn(vk_create_fence, "vkCreateFence");
	load_fn(vk_destroy_fence, "vkDestroyFence");
	load_fn(vk_wait_for_fences, "vkWaitForFences");
	load_fn(vk_reset_fences, "vkResetFences");
	load_fn(vk_create_semaphore, "vkCreateSemaphore");
	load_fn(vk_destroy_semaphore, "vkDestroySemaphore");
	load_fn(vk_create_swapchain_khr, "vkCreateSwapchainKHR");
	load_fn(vk_destroy_swapchain_khr, "vkDestroySwapchainKHR");
	load_fn(vk_get_swapchain_images_khr, "vkGetSwapchainImagesKHR");
	load_fn(vk_acquire_next_image_khr, "vkAcquireNextImageKHR");
	load_fn(vk_queue_present_khr, "vkQueuePresentKHR");
	load_fn(vk_create_image_view, "vkCreateImageView");
	load_fn(vk_destroy_image_view, "vkDestroyImageView");
	load_fn(vk_create_render_pass, "vkCreateRenderPass");
	load_fn(vk_destroy_render_pass, "vkDestroyRenderPass");
	load_fn(vk_create_frame_buffer, "vkCreateFramebuffer");
	load_fn(vk_destroy_frame_buffer, "vkDestroyFramebuffer");
	load_fn(vk_create_shader_module, "vkCreateShaderModule");
	load_fn(vk_destroy_shader_module, "vkDestroyShaderModule");
	load_fn(vk_create_pipeline_layout, "vkCreatePipelineLayout");
	load_fn(vk_destroy_pipeline_layout, "vkDestroyPipelineLayout");
	load_fn(vk_create_graphics_pipelines, "vkCreateGraphicsPipelines");
	load_fn(vk_destroy_pipeline, "vkDestroyPipeline");
	load_fn(vk_cmd_begin_render_pass, "vkCmdBeginRenderPass");
	load_fn(vk_cmd_end_render_pass, "vkCmdEndRenderPass");
	load_fn(vk_cmd_bind_pipeline, "vkCmdBindPipeline");
	load_fn(vk_cmd_draw, "vkCmdDraw");
	load_fn(vk_cmd_set_viewport, "vkCmdSetViewport");
	load_fn(vk_cmd_set_scissors, "vkCmdSetScissor");
	load_fn(vk_cmd_push_constants, "vkCmdPushConstants");
	load_fn(vk_cmd_copy_buffer, "vkCmdCopyBuffer");
	load_fn(vk_create_descriptor_set_layout, "vkCreateDescriptorSetLayout");
	load_fn(vk_destroy_descriptor_set_layout, "vkDestroyDescriptorSetLayout");
	load_fn(vk_create_descriptor_pool, "vkCreateDescriptorPool");
	load_fn(vk_destroy_descriptor_pool, "vkDestroyDescriptorPool");
	load_fn(vk_allocate_descriptor_sets, "vkAllocateDescriptorSets");
	load_fn(vk_free_descriptor_sets, "vkFreeDescriptorSets");
	load_fn(vk_create_buffer, "vkCreateBuffer");
	load_fn(vk_destroy_buffer, "vkDestroyBuffer");
	load_fn(vk_allocate_memory, "vkAllocateMemory");
	load_fn(vk_bind_buffer_memory, "vkBindBufferMemory");
	load_fn(vk_map_memory, "vkMapMemory");
	load_fn(vk_unmap_memory, "vkUnmapMemory");
	load_fn(vk_free_memory, "vkFreeMemory");
	load_fn(vk_get_buffer_memory_requirements, "vkGetBufferMemoryRequirements");
	load_fn(vk_reset_command_buffer, "vkResetCommandBuffer");

	load_fn(vk_cmd_begin_rendering, "vkCmdBeginRendering");
	load_fn(vk_cmd_end_rendering, "vkCmdEndRendering");
}

Instance::Instance(CreateInfo info)
{
	const auto layer_setting_type_visitor = overloads {
		[](const std::vector<const char *> &) { return VK_LAYER_SETTING_TYPE_STRING_EXT; },
		[](std::uint32_t) { return VK_LAYER_SETTING_TYPE_UINT32_EXT; },
		[](bool) { return VK_LAYER_SETTING_TYPE_BOOL32_EXT; },
	};

	const auto layer_setting_value_visitor = overloads {
		[](std::vector<const char *> values) { return std::bit_cast<void *>(values.data()); },
		[](std::uint32_t value) { return std::bit_cast<void *>(&value); },
		[](bool value) { return std::bit_cast<void *>(&value); },
	};

	auto layer_settings = std::vector<VkLayerSettingEXT> {};
	auto layer_names = std::vector<const char *> {};
	auto extension_names = std::vector<const char *> {};

	for (const auto &layer : info.layers)
	{
		layer_names.emplace_back(layer.name.c_str());
		for (const auto &setting : layer.settings)
		{
			layer_settings.emplace_back(
			    VkLayerSettingEXT {
			        .pLayerName = layer.name.c_str(),
			        .pSettingName = setting.name.c_str(),
			        .type = std::visit(layer_setting_type_visitor, setting.values),
			        .valueCount = 1u,
			        .pValues = std::visit(layer_setting_value_visitor, setting.values),
			    }
			);
		}
	}

	const auto layer_settings_create_info = VkLayerSettingsCreateInfoEXT {
		.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
		.settingCount = static_cast<uint32_t>(layer_settings.size()),
		.pSettings = layer_settings.data(),
	};

	auto vk_info = VkInstanceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = &layer_settings_create_info,
		.flags = {},
		.enabledLayerCount = static_cast<uint32_t>(info.layers.size()),
		.ppEnabledLayerNames = layer_names.data(),
		.enabledExtensionCount = static_cast<uint32_t>(info.extensions.size()),
		.ppEnabledExtensionNames = extension_names.data(),
	};

	vkc(vk_create_instance(&vk_info, nullptr, &m_instance));
	debug::ensure(m_instance, "Failed to create vulkan instance");
}

Surface::Surface(const Instance &instance, const XlibCreateInfo &info)
    : m_instance(instance.m_instance)
{
	const auto vk_info = VkXlibSurfaceCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
		.pNext = {},
		.flags = {},
		.dpy = info.display,
		.window = info.window,
	};

	vkc(vk_create_xlib_surface_khr(instance.m_instance, &vk_info, nullptr, &m_surface));
}

Surface::~Surface()
{
	vk_destroy_surface_khr(m_instance, m_surface, nullptr);
}


[[nodiscard]]
/* static */ auto Gpu::enumerate(const Instance &instance) -> std::vector<Gpu>
{
	auto count = 0u;
	vkc(vk_enumerate_physical_devices(instance.m_instance, &count, nullptr));
	debug::ensure(count != 0u, "Failed to find any gpus with Vulkan support");

	auto vk_gpus = std::vector<VkPhysicalDevice>(count);
	vkc(vk_enumerate_physical_devices(instance.m_instance, &count, vk_gpus.data()));

	auto gpus = std::vector<Gpu>(count);
	for (auto [vk_gpu, gpu] : std::views::zip(vk_gpus, gpus))
	{
		gpu.m_instance = instance.m_instance;
		gpu.m_physical_device = vk_gpu;
	}

	return gpus;
}

[[nodiscard]] auto Gpu::queue_family_supports_surface(
    const Surface &surface,
    std::uint32_t queue_family_idx
) const -> bool
{
	auto supported = VkBool32 { false };
	vkc(vk_get_physical_device_surface_support(
	    m_physical_device,
	    queue_family_idx,
	    surface.m_surface,
	    &supported
	));
	return supported;
}

Device::Device(CreateInfo info)
{
}

Device::~Device()
{
	if (m_device)
	{
		vk_destroy_device(m_device, nullptr);
	}
}

[[nodiscard]]
auto enumerate_instance_extension_properties() -> std::vector<VkExtensionProperties>
{
	auto count = 0u;
	vkc(vk_enumerate_instance_extension_properties(nullptr, &count, nullptr));

	auto extensions = std::vector<VkExtensionProperties>(count);
	std::memset(extensions.data(), 0, extensions.size() * sizeof(VkExtensionProperties));
	vkc(vk_enumerate_instance_extension_properties(nullptr, &count, extensions.data()));

	return extensions;
}

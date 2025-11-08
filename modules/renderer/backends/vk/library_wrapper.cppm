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

constexpr auto queue_family_ignored = VK_QUEUE_FAMILY_IGNORED;

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

constexpr auto swapchain = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
constexpr auto dynamic_rendering = VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME;
constexpr auto descriptor_indexing = VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME;

}; // namespace device_extension_names


void load_library();

void unload_library();

void load_global_functions();

[[nodiscard]]
auto enumerate_instance_extension_properties() -> std::vector<VkExtensionProperties>;

using Version_T = uint32_t;

struct ApplicationInfo
{
	std::string_view name;

	Version_T version;

	std::string_view engine_name;

	Version_T engine_version;

	Version_T api_version;
};

namespace PipelineStageFlags {
enum T : VkFlags // NOLINT
{
	top_of_pipe_bit = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
	draw_indirect_bit = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
	vertex_input_bit = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
	vertex_shader_bit = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
	tessellation_control_shader_bit = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT,
	tessellation_evaluation_shader_bit = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT,
	geometry_shader_bit = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
	fragment_shader_bit = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
	early_fragment_tests_bit = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
	late_fragment_tests_bit = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
	color_attachment_output_bit = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
	compute_shader_bit = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
	transfer_bit = VK_PIPELINE_STAGE_TRANSFER_BIT,
	bottom_of_pipe_bit = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
	host_bit = VK_PIPELINE_STAGE_HOST_BIT,
	all_graphics_bit = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
	all_commands_bit = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
	none = VK_PIPELINE_STAGE_NONE,
	transform_feedback_bit_ext = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT,
	conditional_rendering_bit_ext = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT,
	acceleration_structure_build_bit_khr = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
	ray_tracing_shader_bit_khr = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
	fragment_density_process_bit_ext = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT,
	fragment_shading_rate_attachment_bit_khr
	= VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
	task_shader_bit_ext = VK_PIPELINE_STAGE_TASK_SHADER_BIT_EXT,
	mesh_shader_bit_ext = VK_PIPELINE_STAGE_MESH_SHADER_BIT_EXT,
	command_preprocess_bit_ext = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_EXT,
	shading_rate_image_bit_nv = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV,
	ray_tracing_shader_bit_nv = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV,
	acceleration_structure_build_bit_nv = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV,
	task_shader_bit_nv = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV,
	mesh_shader_bit_nv = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV,
	command_preprocess_bit_nv = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV,
	none_khr = VK_PIPELINE_STAGE_NONE_KHR,
};
};

namespace QueueFlags {
enum T : VkFlags // NOLINT
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
enum T : VkFlags // NOLINT
{

	device_local_bit = VK_MEMORY_HEAP_DEVICE_LOCAL_BIT,
	multi_instance_bit = VK_MEMORY_HEAP_MULTI_INSTANCE_BIT,
	tile_memory_bit = VK_MEMORY_HEAP_TILE_MEMORY_BIT_QCOM,
};
};

namespace MemoryPropertyFlags {
enum T : VkFlags // NOLINT
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
	friend class Device;

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

	struct DynamicRenderingFeatures
	{
		bool enabled;
	};

	struct DescriptorIndexingFeatures
	{
		Bool32 shader_input_attachment_array_dynamic_indexing;
		Bool32 shader_uniform_texel_buffer_array_dynamic_indexing;
		Bool32 shader_storage_texel_buffer_array_dynamic_indexing;
		Bool32 shader_uniform_buffer_array_non_uniform_indexing;
		Bool32 shader_sampled_image_array_non_uniform_indexing;
		Bool32 shader_storage_buffer_array_non_uniform_indexing;
		Bool32 shader_storage_image_array_non_uniform_indexing;
		Bool32 shader_input_attachment_array_non_uniform_indexing;
		Bool32 shader_uniform_texel_buffer_array_non_uniform_indexing;
		Bool32 shader_storage_texel_buffer_array_non_uniform_indexing;
		Bool32 descriptor_binding_uniform_buffer_update_after_bind;
		Bool32 descriptor_binding_sampled_image_update_after_bind;
		Bool32 descriptor_binding_storage_image_update_after_bind;
		Bool32 descriptor_binding_storage_buffer_update_after_bind;
		Bool32 descriptor_binding_uniform_texel_buffer_update_after_bind;
		Bool32 descriptor_binding_storage_texel_buffer_update_after_bind;
		Bool32 descriptor_binding_update_unused_while_pending;
		Bool32 descriptor_binding_partially_bound;
		Bool32 descriptor_binding_variable_descriptor_count;
		Bool32 runtime_descriptor_array;
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
		std::array<MemoryType, constants::max_memory_types> memory_types;
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

	[[nodiscard]] auto get_features() const -> Features;

	[[nodiscard]] auto get_supported_dynamic_rendering_features() const -> DynamicRenderingFeatures;

	[[nodiscard]] auto get_supported_descriptor_indexing_features() const
	    -> DescriptorIndexingFeatures;

	[[nodiscard]] auto get_properties() const -> Properties;

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


class Semaphore
{
public:
	friend class Device;
	friend class Queue;

	Semaphore() = default;

	Semaphore(Semaphore &&) = default;

	Semaphore(const Semaphore &) = delete;

	auto operator=(Semaphore &&) -> Semaphore & = default;

	auto operator=(const Semaphore &) -> Semaphore & = delete;

	~Semaphore();

	auto operator&() -> VkSemaphore *
	{
		return &m_semaphore;
	}

private:
	VkDevice m_device;

	VkSemaphore m_semaphore;
};

class Fence
{
public:
	friend class Device;
	friend class Queue;

	Fence() = default;

	Fence(Fence &&) = default;

	Fence(const Fence &) = delete;

	auto operator=(Fence &&) -> Fence & = default;

	auto operator=(const Fence &) -> Fence & = delete;

	~Fence();

	auto operator&() -> VkFence *
	{
		return &m_fence;
	}

	operator VkFence()
	{
		return m_fence;
	}

private:
	VkDevice m_device;

	VkFence m_fence;
};

class Swapchain
{
public:
	friend class Device;

	auto operator&() -> VkSwapchainKHR *
	{
		return &m_swapchain;
	}

	auto VkSwapchainKHR()
	{
		return m_swapchain;
	}

private:
	::VkSwapchainKHR m_swapchain;
};

class CommandBuffer
{
public:
	friend class Device;

	auto operator&() -> VkCommandBuffer *
	{
		return &m_command_buffer;
	}

private:
	VkCommandBuffer m_command_buffer;
};

class Device
{
public:
	friend class Queue;

	struct CreateInfo
	{
		std::set<std::uint32_t> queue_indices;

		std::vector<std::string> extensions;

		Gpu::Features features;

		std::optional<Gpu::DynamicRenderingFeatures> dynamic_rendering_features;

		std::optional<Gpu::DescriptorIndexingFeatures> descriptor_indexing_features;
	};

	Device() = default;

	Device(const Gpu &gpu, CreateInfo info);

	Device(Device &&) = default;

	Device(const Device &) = delete;

	auto operator=(Device &&) -> Device & = default;

	auto operator=(const Device &) -> Device & = delete;

	~Device();

	void load_functions();

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
	    uint64_t timeout = 100'000'000
	) -> std::optional<uint32_t>;

	[[nodiscard]] auto get_swapchain_images(VkSwapchainKHR swapchain) const -> std::vector<VkImage>;

	[[nodiscard]] auto get_memory_requirements(VkBuffer buffer) const -> VkMemoryRequirements;

	/** binders / mappers  */
	void bind_memory(VkBuffer buffer, VkDeviceMemory memory, size_t offset = 0u) const;

	[[nodiscard]] auto map_memory(VkDeviceMemory memory, size_t size, size_t offset) const
	    -> std::span<std::byte>;

	void unmap_memory(VkDeviceMemory memory);

	/** create functions */
	[[nodiscard]] auto create_swapchain(VkSwapchainCreateInfoKHR info) const -> VkSwapchainKHR;

	[[nodiscard]] auto create_framebuffer(VkFramebufferCreateInfo info) const -> VkFramebuffer;

	[[nodiscard]] auto create_image_view(VkImageViewCreateInfo info) const -> VkImageView;

	[[nodiscard]] auto create_graphics_pipeline(VkGraphicsPipelineCreateInfo info) const
	    -> VkPipeline;

	[[nodiscard]] auto create_pass(VkRenderPassCreateInfo info) const -> VkRenderPass;

	[[nodiscard]] auto create_pipeline_layout(
	    std::vector<VkDescriptorSetLayout> descriptor_set_layout,
	    std::vector<VkPushConstantRange> push_constant_ranges
	) const -> VkPipelineLayout;

	[[nodiscard]] auto create_shader_module(VkShaderModuleCreateInfo info) const -> VkShaderModule;

	[[nodiscard]] auto create_command_pool(VkCommandPoolCreateInfo info) const -> VkCommandPool;

	[[nodiscard]] auto create_semaphores(uint32_t count) const -> std::vector<VkSemaphore>;

	[[nodiscard]] auto create_fences(VkFenceCreateInfo info, uint32_t count) const
	    -> std::vector<VkFence>;

	[[nodiscard]] auto create_buffer(VkBufferCreateInfo info) const -> VkBuffer;

	[[nodiscard]] auto create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo info) const
	    -> VkDescriptorSetLayout;

	[[nodiscard]] auto create_desscriptor_pool(VkDescriptorPoolCreateInfo info) const
	    -> VkDescriptorPool;

	/** allocation functions */
	[[nodiscard]] auto allocate_memory(VkMemoryAllocateInfo info) const -> VkDeviceMemory;

	[[nodiscard]] auto allocate_command_buffers(VkCommandBufferAllocateInfo info) const
	    -> std::vector<VkCommandBuffer>;

	[[nodiscard]] auto allocate_descriptor_set(VkDescriptorSetAllocateInfo info) const
	    -> VkDescriptorSet;

	/** de-allocation functions */
	void free_memory(VkDeviceMemory memory) const;

	void free_descriptor_set(
	    VkDescriptorPool descriptor_pool,
	    VkDescriptorSet descriptor_set
	) const;

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

	void destroy_buffer(VkBuffer buffer) const;

	void destroy_descriptor_set_layout(VkDescriptorSetLayout layout) const;

	void destroy_descriptor_pool(VkDescriptorPool pool) const;

	/** utilities */
	template<typename T, typename... Args>
	void name(T &object, std::format_string<Args...> fmt, Args &&...args);

	template<typename T>
	void name(T &object, const char *name);

private:
	memory::NullOnMove<VkDevice> m_device {};
};

class Queue
{
public:
	friend class Device;

	constexpr static auto object_type = VK_OBJECT_TYPE_QUEUE;

	struct SubmitInfo
	{
		CommandBuffer command_buffer;

		PipelineStageFlags::T wait_stages;

		Semaphore wait_semaphore;

		Semaphore signal_semaphore;

		Fence signal_fence;
	};

	struct PresentInfo
	{
		Semaphore wait_semaphore;

		Swapchain swapchain;

		uint32_t image_idx;
	};

	Queue() = default;

	Queue(Device &device, uint32_t queue_family_idx, uint32_t queue_idx);

	Queue(Queue &&) = default;

	Queue(const Queue &) = delete;

	auto operator=(Queue &&) -> Queue & = default;

	auto operator=(const Queue &) -> Queue & = delete;

	~Queue();

	void submit(SubmitInfo info) const;

	void present(PresentInfo info) const;

private:
	[[nodiscard]] auto get_vk_handle() -> VkQueue
	{
		return m_queue;
	}

	memory::NullOnMove<VkDevice> m_device;

	VkQueue m_queue;
};

} // namespace lt::renderer::vk


/** ================================ **/
/** Private Template Implementations **/
/** ================================ **/
PFN_vkSetDebugUtilsObjectNameEXT vk_set_debug_object_name {}; // NOLINT
namespace lt::renderer::vk {

void vkc(VkResult result)
{
	if (result)
	{
		throw std::runtime_error {
			std::format("Vulkan call failed with result: {}", std::to_underlying(result))
		};
	}
}

template<typename T, typename... Args>
void Device::name(T &object, std::format_string<Args...> fmt, Args &&...args)
{
	const auto name = std::format(fmt, std::forward<Args>(args)...);
	auto info = VkDebugUtilsObjectNameInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
		.objectType = T::object_type,
		.objectHandle = (uint64_t)(object.get_vk_handle()),
		.pObjectName = name.c_str(),
	};

	vkc(vk_set_debug_object_name(m_device, &info));
}

template<typename T>
void Device::name(T &object, const char *name)
{
	auto info = VkDebugUtilsObjectNameInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
		.objectType = T::object_type,
		.objectHandle = (uint64_t)(object.get_vk_handle()),
		.pObjectName = name,
	};

	vkc(vk_set_debug_object_name(m_device, &info));
}

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

void Device::load_functions()
{
	const auto load_fn = [this]<typename T>(T &pfn, const char *fn_name) {
		pfn = std::bit_cast<T>(vk_get_device_proc_address(m_device, fn_name));
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

[[nodiscard]] auto Gpu::get_features() const -> Features
{
	auto features_2 = VkPhysicalDeviceFeatures2 {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
	};
	vk_get_physical_device_features(m_physical_device, &features_2);
	const auto features = features_2.features;

	return Features {
		// clang-format off
		 .robust_buffer_access = features.robustBufferAccess,
		 .full_draw_index_uint32 = features.fullDrawIndexUint32,
		 .image_cube_array = features.imageCubeArray,
		 .independent_blend = features.independentBlend,
		 .geometry_shader = features.geometryShader,
		 .tessellation_shader = features.tessellationShader,
		 .sample_rate_shading = features.sampleRateShading,
		 .dual_src_blend = features.dualSrcBlend,
		 .logic_op = features.logicOp,
		 .multi_draw_indirect = features.multiDrawIndirect,
		 .draw_indirect_first_instance = features.drawIndirectFirstInstance,
		 .depth_clamp = features.depthClamp,
		 .depth_bias_clamp = features.depthBiasClamp,
		 .fill_mode_non_solid = features.fillModeNonSolid,
		 .depth_bounds = features.depthBounds,
		 .wide_lines = features.wideLines,
		 .large_points = features.largePoints,
		 .alpha_to_one = features.alphaToOne,
		 .multi_viewport = features.multiViewport,
		 .sampler_anisotropy = features.samplerAnisotropy,
		 .texture_compression_etc2 = features.textureCompressionETC2,
		 .texture_compression_astc_ldr = features.textureCompressionASTC_LDR,
		 .texture_compression_bc = features.textureCompressionBC,
		 .occlusion_query_precise = features.occlusionQueryPrecise,
		 .pipeline_statistics_query = features.pipelineStatisticsQuery,
		 .vertex_pipeline_stores_and_atomics = features.vertexPipelineStoresAndAtomics,
		 .fragment_stores_and_atomics = features.fragmentStoresAndAtomics,
		 .shader_tessellation_and_geometry_point_size = features.shaderTessellationAndGeometryPointSize,
		 .shader_image_gather_extended = features.shaderImageGatherExtended,
		 .shader_storage_image_extended_formats = features.shaderStorageImageExtendedFormats,
		 .shader_storage_image_multisample = features.shaderStorageImageMultisample,
		 .shader_storage_image_read_without_format = features.shaderStorageImageReadWithoutFormat,
		 .shader_storage_image_write_without_format = features.shaderStorageImageWriteWithoutFormat,
		 .shader_uniform_buffer_array_dynamic_indexing = features.shaderUniformBufferArrayDynamicIndexing,
		 .shader_sampled_image_array_dynamic_indexing = features.shaderSampledImageArrayDynamicIndexing,
		 .shader_storage_buffer_array_dynamic_indexing = features.shaderStorageBufferArrayDynamicIndexing,
		 .shader_storage_image_array_dynamic_indexing = features.shaderStorageImageArrayDynamicIndexing,
		 .shader_clip_distance = features.shaderClipDistance,
		 .shader_cull_distance = features.shaderCullDistance,
		 .shader_float64 = features.shaderFloat64,
		 .shader_int64 = features.shaderInt64,
		 .shader_int16 = features.shaderInt16,
		 .shader_resource_residency = features.shaderResourceResidency,
		 .shader_resource_min_lod = features.shaderResourceMinLod,
		 .sparse_binding = features.sparseBinding,
		 .sparse_residency_buffer = features.sparseResidencyBuffer,
		 .sparse_residency_image_2d = features.sparseResidencyImage2D,
		 .sparse_residency_image_3d = features.sparseResidencyImage3D,
		 .sparse_residency_2_samples = features.sparseResidency2Samples,
		 .sparse_residency_4_samples = features.sparseResidency4Samples,
		 .sparse_residency_8_samples = features.sparseResidency8Samples,
		 .sparse_residency_16_samples = features.sparseResidency16Samples,
		 .sparse_residency_aliased = features.sparseResidencyAliased,
		 .variable_multisample_rate = features.variableMultisampleRate,
		 .inherited_queries = features.inheritedQueries,
		// clang-format on
	};
}

[[nodiscard]] auto Gpu::get_supported_dynamic_rendering_features() const -> DynamicRenderingFeatures
{
	auto features = VkPhysicalDeviceDynamicRenderingFeatures {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
	};

	auto features_2 = VkPhysicalDeviceFeatures2 {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
		.pNext = &features,
	};

	vk_get_physical_device_features(m_physical_device, &features_2);
	return DynamicRenderingFeatures {
		.enabled = !!features.dynamicRendering,
	};
}

[[nodiscard]] auto Gpu::get_supported_descriptor_indexing_features() const
    -> DescriptorIndexingFeatures
{
	auto features = VkPhysicalDeviceDescriptorIndexingFeatures {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES,
	};

	auto features_2 = VkPhysicalDeviceFeatures2 {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
		.pNext = &features,
	};

	vk_get_physical_device_features(m_physical_device, &features_2);
	return DescriptorIndexingFeatures {
		// clang-format off
		.shader_input_attachment_array_dynamic_indexing = features.shaderInputAttachmentArrayDynamicIndexing,
		.shader_uniform_texel_buffer_array_dynamic_indexing = features.shaderUniformTexelBufferArrayDynamicIndexing,
		.shader_storage_texel_buffer_array_dynamic_indexing = features.shaderStorageTexelBufferArrayDynamicIndexing,
		.shader_uniform_buffer_array_non_uniform_indexing = features.shaderUniformBufferArrayNonUniformIndexing,
		.shader_sampled_image_array_non_uniform_indexing = features.shaderSampledImageArrayNonUniformIndexing,
		.shader_storage_buffer_array_non_uniform_indexing = features.shaderStorageBufferArrayNonUniformIndexing,
		.shader_storage_image_array_non_uniform_indexing = features.shaderStorageImageArrayNonUniformIndexing,
		.shader_input_attachment_array_non_uniform_indexing = features.shaderInputAttachmentArrayNonUniformIndexing,
		.shader_uniform_texel_buffer_array_non_uniform_indexing = features.shaderUniformTexelBufferArrayNonUniformIndexing,
		.shader_storage_texel_buffer_array_non_uniform_indexing = features.shaderStorageTexelBufferArrayNonUniformIndexing,
		.descriptor_binding_uniform_buffer_update_after_bind = features.descriptorBindingUniformBufferUpdateAfterBind,
		.descriptor_binding_sampled_image_update_after_bind = features.descriptorBindingSampledImageUpdateAfterBind,
		.descriptor_binding_storage_image_update_after_bind = features.descriptorBindingStorageImageUpdateAfterBind,
		.descriptor_binding_storage_buffer_update_after_bind = features.descriptorBindingStorageBufferUpdateAfterBind,
		.descriptor_binding_uniform_texel_buffer_update_after_bind = features.descriptorBindingUniformTexelBufferUpdateAfterBind,
		.descriptor_binding_storage_texel_buffer_update_after_bind = features.descriptorBindingStorageTexelBufferUpdateAfterBind,
		.descriptor_binding_update_unused_while_pending = features.descriptorBindingUpdateUnusedWhilePending,
		.descriptor_binding_partially_bound = features.descriptorBindingPartiallyBound, 
        .descriptor_binding_variable_descriptor_count = features.descriptorBindingVariableDescriptorCount,
        .runtime_descriptor_array = features.runtimeDescriptorArray,
		// clang-format on
	};
}

[[nodiscard]] auto Gpu::get_properties() const -> Properties
{
	auto vk_properties = VkPhysicalDeviceProperties {};
	vk_get_physical_device_properties(m_physical_device, &vk_properties);

	auto properties = Gpu::Properties {
		.api_version = vk_properties.apiVersion,
		.driver_version = vk_properties.driverVersion,
		.vendor_id = vk_properties.vendorID,
		.device_id = vk_properties.deviceID,
		.device_type = static_cast<Gpu::Type>(vk_properties.deviceType),
		.device_name = {},
		.pipeline_cache_uuid = {},
		.limits = {},
		.sparse_properties = {},
	};

	std::memcpy(
	    properties.device_name.data(),
	    static_cast<char *>(vk_properties.deviceName),
	    constants::max_physical_device_name
	);

	std::memcpy(
	    properties.pipeline_cache_uuid.data(),
	    static_cast<std::uint8_t *>(vk_properties.pipelineCacheUUID),
	    constants::uuid_size
	);

	const auto vk_limits = vk_properties.limits;
	properties.limits = Gpu::Limits {
		// clang-format off
        .max_image_dimension_1d = vk_limits.maxImageDimension1D,
        .max_image_dimension_2d = vk_limits.maxImageDimension2D,
        .max_image_dimension_3d = vk_limits.maxImageDimension3D,
        .max_image_dimension_cube = vk_limits.maxImageDimensionCube,
        .max_image_array_layers = vk_limits.maxImageArrayLayers,
        .max_texel_buffer_elements = vk_limits.maxTexelBufferElements,
        .max_uniform_buffer_range = vk_limits.maxUniformBufferRange,
        .max_storage_buffer_range = vk_limits.maxStorageBufferRange,
        .max_push_constants_size = vk_limits.maxPushConstantsSize,
        .max_memory_allocation_count = vk_limits.maxMemoryAllocationCount,
        .max_sampler_allocation_count = vk_limits.maxSamplerAllocationCount,
        .buffer_image_granularity = vk_limits.bufferImageGranularity,
        .sparse_address_space_size = vk_limits.sparseAddressSpaceSize,
        .max_bound_descriptor_sets = vk_limits.maxBoundDescriptorSets,
        .max_per_stage_descriptor_samplers = vk_limits.maxPerStageDescriptorSamplers,
        .max_per_stage_descriptor_uniform_buffers = vk_limits.maxPerStageDescriptorUniformBuffers,
        .max_per_stage_descriptor_storage_buffers = vk_limits.maxPerStageDescriptorStorageBuffers,
        .max_per_stage_descriptor_sampled_images = vk_limits.maxPerStageDescriptorSampledImages,
        .max_per_stage_descriptor_storage_images = vk_limits.maxPerStageDescriptorStorageImages,
        .max_per_stage_descriptor_input_attachments = vk_limits.maxPerStageDescriptorInputAttachments,
        .max_per_stage_resources = vk_limits.maxPerStageResources,
        .max_descriptor_set_samplers = vk_limits.maxDescriptorSetSamplers,
        .max_descriptor_set_uniform_buffers = vk_limits.maxDescriptorSetUniformBuffers,
        .max_descriptor_set_uniform_buffers_dynamic = vk_limits.maxDescriptorSetUniformBuffersDynamic,
        .max_descriptor_set_storage_buffers = vk_limits.maxDescriptorSetStorageBuffers,
        .max_descriptor_set_storage_buffers_dynamic = vk_limits.maxDescriptorSetStorageBuffersDynamic,
        .max_descriptor_set_sampled_images = vk_limits.maxDescriptorSetSampledImages,
        .max_descriptor_set_storage_images = vk_limits.maxDescriptorSetStorageImages,
        .max_descriptor_set_input_attachments = vk_limits.maxDescriptorSetInputAttachments,
        .max_vertex_input_attributes = vk_limits.maxVertexInputAttributes,
        .max_vertex_input_bindings = vk_limits.maxVertexInputBindings,
        .max_vertex_input_attribute_offset = vk_limits.maxVertexInputAttributeOffset,
        .max_vertex_input_binding_stride = vk_limits.maxVertexInputBindingStride,
        .max_vertex_output_components = vk_limits.maxVertexOutputComponents,
        .max_tessellation_generation_level = vk_limits.maxTessellationGenerationLevel,
        .max_tessellation_patch_size = vk_limits.maxTessellationPatchSize,
        .max_tessellation_control_per_vertex_input_components = vk_limits.maxTessellationControlPerVertexInputComponents,
        .max_tessellation_control_per_vertex_output_components = vk_limits.maxTessellationControlPerVertexOutputComponents,
        .max_tessellation_control_per_patch_output_components = vk_limits.maxTessellationControlPerPatchOutputComponents,
        .max_tessellation_control_total_output_components = vk_limits.maxTessellationControlTotalOutputComponents,
        .max_tessellation_evaluation_input_components = vk_limits.maxTessellationEvaluationInputComponents,
        .max_tessellation_evaluation_output_components = vk_limits.maxTessellationEvaluationOutputComponents,
        .max_geometry_shader_invocations = vk_limits.maxGeometryShaderInvocations,
        .max_geometry_input_components = vk_limits.maxGeometryInputComponents,
        .max_geometry_output_components = vk_limits.maxGeometryOutputComponents,
        .max_geometry_output_vertices = vk_limits.maxGeometryOutputVertices,
        .max_geometry_total_output_components = vk_limits.maxGeometryTotalOutputComponents,
        .max_fragment_input_components = vk_limits.maxFragmentInputComponents,
        .max_fragment_output_attachments = vk_limits.maxFragmentOutputAttachments,
        .max_fragment_dual_src_attachments = vk_limits.maxFragmentDualSrcAttachments,
        .max_fragment_combined_output_resources = vk_limits.maxFragmentCombinedOutputResources,
        .max_compute_shared_memory_size = vk_limits.maxComputeSharedMemorySize,
        .max_compute_work_group_count = {vk_limits.maxComputeWorkGroupCount[3]},
        .max_compute_work_group_invocations = vk_limits.maxComputeWorkGroupInvocations,
        .max_compute_work_group_size = {vk_limits.maxComputeWorkGroupSize[3]},
        .sub_pixel_precision_bits = vk_limits.subPixelPrecisionBits,
        .sub_texel_precision_bits = vk_limits.subTexelPrecisionBits,
        .mipmap_precision_bits = vk_limits.mipmapPrecisionBits,
        .max_draw_indexed_index_value = vk_limits.maxDrawIndexedIndexValue,
        .max_draw_indirect_count = vk_limits.maxDrawIndirectCount,
        .max_sampler_lod_bias = vk_limits.maxSamplerLodBias,
        .max_sampler_anisotropy = vk_limits.maxSamplerAnisotropy,
        .max_viewports = vk_limits.maxViewports,
        .max_viewport_dimensions = {vk_limits.maxViewportDimensions[2]},
        .viewport_bounds_range = {vk_limits.viewportBoundsRange[2]},
        .viewport_sub_pixel_bits = vk_limits.viewportSubPixelBits,
        .min_memory_map_alignment = vk_limits.minMemoryMapAlignment,
        .min_texel_buffer_offset_alignment = vk_limits.minTexelBufferOffsetAlignment,
        .min_uniform_buffer_offset_alignment = vk_limits.minUniformBufferOffsetAlignment,
        .min_storage_buffer_offset_alignment = vk_limits.minStorageBufferOffsetAlignment,
        .min_texel_offset = vk_limits.minTexelOffset,
        .max_texel_offset = vk_limits.maxTexelOffset,
        .min_texel_gather_offset = vk_limits.minTexelGatherOffset,
        .max_texel_gather_offset = vk_limits.maxTexelGatherOffset,
        .min_interpolation_offset = vk_limits.minInterpolationOffset,
        .max_interpolation_offset = vk_limits.maxInterpolationOffset,
        .sub_pixel_interpolation_offset_bits = vk_limits.subPixelInterpolationOffsetBits,
        .max_framebuffer_width = vk_limits.maxFramebufferWidth,
        .max_framebuffer_height = vk_limits.maxFramebufferHeight,
        .max_framebuffer_layers = vk_limits.maxFramebufferLayers,
        .framebuffer_color_sample_counts = vk_limits.framebufferColorSampleCounts,
        .framebuffer_depth_sample_counts = vk_limits.framebufferDepthSampleCounts,
        .framebuffer_stencil_sample_counts = vk_limits.framebufferStencilSampleCounts,
        .framebuffer_no_attachments_sample_counts = vk_limits.framebufferNoAttachmentsSampleCounts,
        .max_color_attachments = vk_limits.maxColorAttachments,
        .sampled_image_color_sample_counts = vk_limits.sampledImageColorSampleCounts,
        .sampled_image_integer_sample_counts = vk_limits.sampledImageIntegerSampleCounts,
        .sampled_image_depth_sample_counts = vk_limits.sampledImageDepthSampleCounts,
        .sampled_image_stencil_sample_counts = vk_limits.sampledImageStencilSampleCounts,
        .storage_image_sample_counts = vk_limits.storageImageSampleCounts,
        .max_sample_mask_words = vk_limits.maxSampleMaskWords,
        .timestamp_compute_and_graphics = vk_limits.timestampComputeAndGraphics,
        .timestamp_period = vk_limits.timestampPeriod,
        .max_clip_distances = vk_limits.maxClipDistances,
        .max_cull_distances = vk_limits.maxCullDistances,
        .max_combined_clip_and_cull_distances = vk_limits.maxCombinedClipAndCullDistances,
        .discrete_queue_priorities = vk_limits.discreteQueuePriorities,
        .point_size_range = {vk_limits.pointSizeRange[2]},
        .line_width_range = {vk_limits.lineWidthRange[2]},
        .point_size_granularity = vk_limits.pointSizeGranularity,
        .line_width_granularity = vk_limits.lineWidthGranularity,
        .strict_lines = vk_limits.strictLines,
        .standard_sample_locations = vk_limits.standardSampleLocations,
        .optimal_buffer_copy_offset_alignment = vk_limits.optimalBufferCopyOffsetAlignment,
        .optimal_buffer_copy_row_pitch_alignment = vk_limits.optimalBufferCopyRowPitchAlignment,
        .non_coherent_atom_size = vk_limits.nonCoherentAtomSize,
		// clang-format on
	};

	const auto vk_sparse_properties = vk_properties.sparseProperties;
	properties.sparse_properties = Gpu::SparseProperties {
		// clang-format off
		.residency_standard_2d_block_shape = vk_sparse_properties.residencyStandard2DBlockShape ,
		.residency_standard_2d_multisample_block_shape = vk_sparse_properties.residencyStandard2DMultisampleBlockShape ,
		.residency_standard_3d_block_shape = vk_sparse_properties.residencyStandard3DBlockShape ,
		.residency_aligned_mip_size = vk_sparse_properties.residencyAlignedMipSize ,
		.residency_non_resident_strict = vk_sparse_properties.residencyNonResidentStrict ,
		// clang-format on
	};

	return properties;
}

[[nodiscard]] auto Gpu::get_memory_properties() const -> MemoryProperties
{
	auto vk_memory_properties = VkPhysicalDeviceMemoryProperties {};
	vk_get_physical_device_memory_properties(m_physical_device, &vk_memory_properties);

	auto memory_properties = MemoryProperties {};

	std::memcpy(
	    memory_properties.memory_heaps.data(),
	    static_cast<VkMemoryHeap *>(vk_memory_properties.memoryHeaps),
	    sizeof(VkMemoryHeap) * vk_memory_properties.memoryHeapCount
	);

	std::memcpy(
	    memory_properties.memory_types.data(),
	    static_cast<VkMemoryType *>(vk_memory_properties.memoryTypes),
	    sizeof(VkMemoryType) * vk_memory_properties.memoryTypeCount
	);

	return memory_properties;
}

[[nodiscard]] auto Gpu::get_queue_family_properties() const -> std::vector<QueueFamilyProperties>
{
	auto count = std::uint32_t {};

	vk_get_physical_device_queue_family_properties(m_physical_device, &count, {});

	auto vk_properties = std::vector<VkQueueFamilyProperties>(count);
	vk_get_physical_device_queue_family_properties(m_physical_device, &count, vk_properties.data());

	auto properties = std::vector<QueueFamilyProperties>(count);

	for (auto [property, vk_property] : std::views::zip(properties, vk_properties))
	{
		property = QueueFamilyProperties {
			.queue_flags = static_cast<QueueFlags::T>(vk_property.queueFlags),
			.queue_count = vk_property.queueCount,
			.timestamp_valid_bits = vk_property.timestampValidBits,
			.min_image_transfer_granularity = math::uvec3{
                vk_property.minImageTransferGranularity.width,
                vk_property.minImageTransferGranularity.height,
                vk_property.minImageTransferGranularity.depth,
            },
		};
	}

	return properties;
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

Semaphore::~Semaphore()
{
	vk_destroy_semaphore(m_device, m_semaphore, nullptr);
}

Fence::~Fence()
{
	vk_destroy_fence(m_device, m_fence, nullptr);
}

Device::Device(const Gpu &gpu, CreateInfo info)
{
	const auto priorities = .0f;
	auto vk_queue_infos = std::vector<VkDeviceQueueCreateInfo> {};
	for (auto queue_family : info.queue_indices)
	{
		vk_queue_infos.emplace_back(
		    VkDeviceQueueCreateInfo {
		        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		        .queueFamilyIndex = queue_family,
		        .queueCount = 1u,
		        .pQueuePriorities = &priorities,
		    }
		);
	}

	auto vk_extension_names = std::vector<const char *>(info.extensions.size());
	for (const auto &extension : info.extensions)
	{
		vk_extension_names.emplace_back(extension.c_str());
	}

	const auto vk_features = VkPhysicalDeviceFeatures {
		// clang-format off
		.robustBufferAccess = info.features.robust_buffer_access,
		.fullDrawIndexUint32 = info.features.full_draw_index_uint32,
		.imageCubeArray = info.features.image_cube_array,
		.independentBlend = info.features.independent_blend,
		.geometryShader = info.features.geometry_shader,
		.tessellationShader = info.features.tessellation_shader,
		.sampleRateShading = info.features.sample_rate_shading,
		.dualSrcBlend = info.features.dual_src_blend,
		.logicOp = info.features.logic_op,
		.multiDrawIndirect = info.features.multi_draw_indirect,
		.drawIndirectFirstInstance = info.features.draw_indirect_first_instance,
		.depthClamp = info.features.depth_clamp,
		.depthBiasClamp = info.features.depth_bias_clamp,
		.fillModeNonSolid = info.features.fill_mode_non_solid,
		.depthBounds = info.features.depth_bounds,
		.wideLines = info.features.wide_lines,
		.largePoints = info.features.large_points,
		.alphaToOne = info.features.alpha_to_one,
		.multiViewport = info.features.multi_viewport,
		.samplerAnisotropy = info.features.sampler_anisotropy,
		.textureCompressionETC2 = info.features.texture_compression_etc2,
		.textureCompressionASTC_LDR = info.features.texture_compression_astc_ldr,
		.textureCompressionBC = info.features.texture_compression_bc,
		.occlusionQueryPrecise = info.features.occlusion_query_precise,
		.pipelineStatisticsQuery = info.features.pipeline_statistics_query,
		.vertexPipelineStoresAndAtomics = info.features.vertex_pipeline_stores_and_atomics,
		.fragmentStoresAndAtomics = info.features.fragment_stores_and_atomics,
		.shaderTessellationAndGeometryPointSize = info.features .shader_tessellation_and_geometry_point_size,
		.shaderImageGatherExtended = info.features.shader_image_gather_extended,
		.shaderStorageImageExtendedFormats = info.features.shader_storage_image_extended_formats,
		.shaderStorageImageMultisample = info.features.shader_storage_image_multisample,
		.shaderStorageImageReadWithoutFormat = info.features .shader_storage_image_read_without_format,
		.shaderStorageImageWriteWithoutFormat = info.features .shader_storage_image_write_without_format,
		.shaderUniformBufferArrayDynamicIndexing = info.features.shader_uniform_buffer_array_dynamic_indexing,
		.shaderSampledImageArrayDynamicIndexing = info.features .shader_sampled_image_array_dynamic_indexing,
		.shaderStorageBufferArrayDynamicIndexing = info.features.shader_storage_buffer_array_dynamic_indexing,
		.shaderStorageImageArrayDynamicIndexing = info.features .shader_storage_image_array_dynamic_indexing,
		.shaderClipDistance = info.features.shader_clip_distance,
		.shaderCullDistance = info.features.shader_cull_distance,
		.shaderFloat64 = info.features.shader_float64,
		.shaderInt64 = info.features.shader_int64,
		.shaderInt16 = info.features.shader_int16,
		.shaderResourceResidency = info.features.shader_resource_residency,
		.shaderResourceMinLod = info.features.shader_resource_min_lod,
		.sparseBinding = info.features.sparse_binding,
		.sparseResidencyBuffer = info.features.sparse_residency_buffer,
		.sparseResidencyImage2D = info.features.sparse_residency_image_2d,
		.sparseResidencyImage3D = info.features.sparse_residency_image_3d,
		.sparseResidency2Samples = info.features.sparse_residency_2_samples,
		.sparseResidency4Samples = info.features.sparse_residency_4_samples,
		.sparseResidency8Samples = info.features.sparse_residency_8_samples,
		.sparseResidency16Samples = info.features.sparse_residency_16_samples,
		.sparseResidencyAliased = info.features.sparse_residency_aliased,
		.variableMultisampleRate = info.features.variable_multisample_rate,
		.inheritedQueries = info.features.inherited_queries,
		// clang-format on
	};

	auto vk_features_2 = VkPhysicalDeviceFeatures2 {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
		.pNext = {},
		.features = vk_features,
	};

	auto vk_descriptor_indexing_features = VkPhysicalDeviceDescriptorIndexingFeatures {};
	auto vk_dynamic_rendering_features = VkPhysicalDeviceDynamicRenderingFeatures {};
	void **last_p_next = &vk_features_2.pNext;

	if (info.dynamic_rendering_features)
	{
		vk_dynamic_rendering_features = VkPhysicalDeviceDynamicRenderingFeatures {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
			.pNext = {},
			.dynamicRendering = (*info.dynamic_rendering_features).enabled,
		};

		*last_p_next = &vk_descriptor_indexing_features;
		last_p_next = &vk_descriptor_indexing_features.pNext;
	}

	if (info.descriptor_indexing_features)
	{
		const auto features = *info.descriptor_indexing_features;
		vk_descriptor_indexing_features = VkPhysicalDeviceDescriptorIndexingFeatures {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES,
			.pNext = {},
			// clang-format off
			.shaderInputAttachmentArrayDynamicIndexing = features.shader_input_attachment_array_dynamic_indexing,
			.shaderUniformTexelBufferArrayDynamicIndexing = features.shader_uniform_texel_buffer_array_dynamic_indexing,
			.shaderStorageTexelBufferArrayDynamicIndexing = features.shader_storage_texel_buffer_array_dynamic_indexing,
			.shaderUniformBufferArrayNonUniformIndexing = features.shader_uniform_buffer_array_non_uniform_indexing,
			.shaderSampledImageArrayNonUniformIndexing = features.shader_sampled_image_array_non_uniform_indexing,
			.shaderStorageBufferArrayNonUniformIndexing = features.shader_storage_buffer_array_non_uniform_indexing,
			.shaderStorageImageArrayNonUniformIndexing = features.shader_storage_image_array_non_uniform_indexing,
			.shaderInputAttachmentArrayNonUniformIndexing = features.shader_input_attachment_array_non_uniform_indexing,
			.shaderUniformTexelBufferArrayNonUniformIndexing = features.shader_uniform_texel_buffer_array_non_uniform_indexing,
			.shaderStorageTexelBufferArrayNonUniformIndexing = features.shader_storage_texel_buffer_array_non_uniform_indexing,
			.descriptorBindingUniformBufferUpdateAfterBind = features.descriptor_binding_uniform_buffer_update_after_bind,
			.descriptorBindingSampledImageUpdateAfterBind = features.descriptor_binding_sampled_image_update_after_bind,
			.descriptorBindingStorageImageUpdateAfterBind = features.descriptor_binding_storage_image_update_after_bind,
			.descriptorBindingStorageBufferUpdateAfterBind = features.descriptor_binding_storage_buffer_update_after_bind,
			.descriptorBindingUniformTexelBufferUpdateAfterBind = features.descriptor_binding_uniform_texel_buffer_update_after_bind,
			.descriptorBindingStorageTexelBufferUpdateAfterBind = features.descriptor_binding_storage_texel_buffer_update_after_bind,
			.descriptorBindingUpdateUnusedWhilePending = features.descriptor_binding_update_unused_while_pending,
			.descriptorBindingPartiallyBound = features.descriptor_binding_partially_bound,
			.descriptorBindingVariableDescriptorCount = features.descriptor_binding_variable_descriptor_count,
			.runtimeDescriptorArray = features.runtime_descriptor_array,
			// clang-format on
		};

		*last_p_next = &vk_descriptor_indexing_features;
		last_p_next = &vk_descriptor_indexing_features.pNext;
	}

	auto vk_info = VkDeviceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &vk_features_2,
		.queueCreateInfoCount = static_cast<uint32_t>(vk_queue_infos.size()),
		.pQueueCreateInfos = vk_queue_infos.data(),
		.enabledExtensionCount = static_cast<uint32_t>(vk_extension_names.size()),
		.ppEnabledExtensionNames = vk_extension_names.data(),
		.pEnabledFeatures = nullptr, // replaced with VkPhysicalDeviceFeatures2
	};

	vkc(vk_create_device(gpu.m_physical_device, &vk_info, nullptr, &m_device));
}

Device::~Device()
{
	if (m_device)
	{
		vk_destroy_device(m_device, nullptr);
	}
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
	debug::ensure(count != 0u, "Failed to get swapchain images");

	auto images = std::vector<VkImage>(count);
	vkc(vk_get_swapchain_images_khr(m_device, swapchain, &count, images.data()));
	return images;
}

[[nodiscard]] auto Device::get_memory_requirements(VkBuffer buffer) const -> VkMemoryRequirements
{
	auto requirements = VkMemoryRequirements {};
	vk_get_buffer_memory_requirements(m_device, buffer, &requirements);
	return requirements;
}

void Device::bind_memory(VkBuffer buffer, VkDeviceMemory memory, size_t offset /* = 0u */) const
{
	vkc(vk_bind_buffer_memory(m_device, buffer, memory, offset));
}

[[nodiscard]] auto Device::map_memory(VkDeviceMemory memory, size_t size, size_t offset) const
    -> std::span<std::byte>
{
	void *data = {};
	vkc(vk_map_memory(m_device, memory, offset, size, {}, &data));
	return { std::bit_cast<std::byte *>(data), size };
}

void Device::unmap_memory(VkDeviceMemory memory)
{
	vk_unmap_memory(m_device, memory);
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
	vkc(vk_create_frame_buffer(m_device, &info, nullptr, &framebuffer));
	return framebuffer;
}

[[nodiscard]] auto Device::create_image_view(VkImageViewCreateInfo info) const -> VkImageView
{
	auto *view = VkImageView {};
	vkc(vk_create_image_view(m_device, &info, nullptr, &view));
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
	    nullptr,
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

[[nodiscard]] auto Device::create_pipeline_layout(
    std::vector<VkDescriptorSetLayout> descriptor_set_layout,
    std::vector<VkPushConstantRange> push_constant_ranges
) const -> VkPipelineLayout
{
	auto info = VkPipelineLayoutCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = static_cast<uint32_t>(descriptor_set_layout.size()),
		.pSetLayouts = descriptor_set_layout.data(),
		.pushConstantRangeCount = static_cast<uint32_t>(push_constant_ranges.size()),
		.pPushConstantRanges = push_constant_ranges.data(),
	};

	auto *pipeline_layout = VkPipelineLayout {};
	vkc(vk_create_pipeline_layout(m_device, &info, nullptr, &pipeline_layout));
	return pipeline_layout;
}

[[nodiscard]] auto Device::create_shader_module(VkShaderModuleCreateInfo info) const
    -> VkShaderModule
{
	auto *module = VkShaderModule {};
	vkc(vk_create_shader_module(m_device, &info, nullptr, &module));
	return module;
}

[[nodiscard]] auto Device::create_command_pool(VkCommandPoolCreateInfo info) const -> VkCommandPool
{
	auto *command_pool = VkCommandPool {};
	vkc(vk_create_command_pool(m_device, &info, nullptr, &command_pool));
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
		vk_create_semaphore(m_device, &info, nullptr, &semaphore);
	}
	return semaphores;
}

[[nodiscard]] auto Device::create_fences(VkFenceCreateInfo info, uint32_t count) const
    -> std::vector<VkFence>
{
	auto fences = std::vector<VkFence>(count);
	for (auto &fence : fences)
	{
		vk_create_fence(m_device, &info, nullptr, &fence);
	}
	return fences;
}

[[nodiscard]] auto Device::create_buffer(VkBufferCreateInfo info) const -> VkBuffer
{
	auto *buffer = VkBuffer {};
	vkc(vk_create_buffer(m_device, &info, nullptr, &buffer));
	return buffer;
}
[[nodiscard]] auto Device::create_desscriptor_pool(VkDescriptorPoolCreateInfo info) const
    -> VkDescriptorPool
{
	auto *pool = VkDescriptorPool {};
	vkc(vk_create_descriptor_pool(m_device, &info, nullptr, &pool));
	return pool;
}

[[nodiscard]] auto Device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo info) const
    -> VkDescriptorSetLayout
{
	auto *layout = VkDescriptorSetLayout {};
	vkc(vk_create_descriptor_set_layout(m_device, &info, nullptr, &layout));
	return layout;
}

[[nodiscard]] auto Device::allocate_command_buffers(VkCommandBufferAllocateInfo info) const
    -> std::vector<VkCommandBuffer>
{
	auto command_buffers = std::vector<VkCommandBuffer>(info.commandBufferCount);
	vkc(vk_allocate_command_buffers(m_device, &info, command_buffers.data()));
	return command_buffers;
}

[[nodiscard]] auto Device::allocate_memory(VkMemoryAllocateInfo info) const -> VkDeviceMemory
{
	auto *memory = VkDeviceMemory {};
	vkc(vk_allocate_memory(m_device, &info, nullptr, &memory));
	return memory;
}

[[nodiscard]] auto Device::allocate_descriptor_set(VkDescriptorSetAllocateInfo info) const
    -> VkDescriptorSet
{
	auto *descriptor_set = VkDescriptorSet {};
	vkc(vk_allocate_descriptor_sets(m_device, &info, &descriptor_set));
	return descriptor_set;
}

void Device::free_memory(VkDeviceMemory memory) const
{
	vk_free_memory(m_device, memory, nullptr);
}

void Device::free_descriptor_set(
    VkDescriptorPool descriptor_pool,
    VkDescriptorSet descriptor_set
) const
{
	vkc(vk_free_descriptor_sets(m_device, descriptor_pool, 1, &descriptor_set));
}

void Device::destroy_swapchain(VkSwapchainKHR swapchain) const
{
	vk_destroy_swapchain_khr(m_device, swapchain, nullptr);
}

void Device::destroy_framebuffer(VkFramebuffer framebuffer) const
{
	vk_destroy_frame_buffer(m_device, framebuffer, nullptr);
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
	vk_destroy_image_view(m_device, image_view, nullptr);
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
	vk_destroy_pipeline(m_device, pipeline, nullptr);
}

void Device::destroy_pass(VkRenderPass pass) const
{
	vk_destroy_render_pass(m_device, pass, nullptr);
}

void Device::destroy_pipeline_layout(VkPipelineLayout pipeline_layout) const
{
	vk_destroy_pipeline_layout(m_device, pipeline_layout, nullptr);
}

void Device::destroy_shader_module(VkShaderModule shader_module) const
{
	vk_destroy_shader_module(m_device, shader_module, nullptr);
}

void Device::destroy_command_pool(VkCommandPool command_pool) const
{
	vk_destroy_command_pool(m_device, command_pool, nullptr);
}

void Device::destroy_semaphore(VkSemaphore semaphore) const
{
	vk_destroy_semaphore(m_device, semaphore, nullptr);
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
	vk_destroy_fence(m_device, fence, nullptr);
}

void Device::destroy_fences(std::span<VkFence> fences) const
{
	for (auto &fence : fences)
	{
		destroy_fence(fence);
	}
}

void Device::destroy_buffer(VkBuffer buffer) const
{
	vk_destroy_buffer(m_device, buffer, nullptr);
}

void Device::destroy_descriptor_set_layout(VkDescriptorSetLayout layout) const
{
	vk_destroy_descriptor_set_layout(m_device, layout, nullptr);
}

void Device::destroy_descriptor_pool(VkDescriptorPool pool) const
{
	vk_destroy_descriptor_pool(m_device, pool, nullptr);
}

[[nodiscard]] auto addressof_underlying(auto &enum_value)
    -> std::underlying_type_t<std::decay_t<decltype(enum_value)>> *
{
	using underlying_type = std::underlying_type_t<std::decay_t<decltype(enum_value)>>;
	return std::bit_cast<underlying_type *>(&enum_value);
}

Queue::Queue(Device &device, uint32_t queue_family_idx, uint32_t queue_idx)
    : m_device(device.m_device.get())
    , m_queue()
{
	vk_get_device_queue(m_device, queue_family_idx, queue_idx, &m_queue);
}

Queue::~Queue()
{
}

void Queue::submit(SubmitInfo info) const
{
	const auto vk_info = VkSubmitInfo {

		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1u,
		.pWaitSemaphores = &info.wait_semaphore,
		.pWaitDstStageMask = addressof_underlying(info.wait_stages),

		.commandBufferCount = 1u,
		.pCommandBuffers = &info.command_buffer,
		.signalSemaphoreCount = 1u,
		.pSignalSemaphores = &info.signal_semaphore,
	};

	vkc(vk_queue_submit(m_queue, 1u, &vk_info, info.signal_fence));
}

void Queue::present(PresentInfo info) const
{
	auto result = VkResult {};

	const auto vk_info = VkPresentInfoKHR {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1u,
		.pWaitSemaphores = &info.wait_semaphore,
		.swapchainCount = 1u,
		.pSwapchains = &info.swapchain,
		.pImageIndices = &info.image_idx,
		.pResults = &result,
	};

	vkc(vk_queue_present_khr(m_queue, &vk_info));
	vkc(result);
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

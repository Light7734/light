/** For lack of a better word, the way things are implemented is pretty F'ed up...
 * BUT... it works... and the exported interface simplifies everything for the consumer
 *
 *
 * Why did I do this?
 * To reduce as much complexity from the API,
 * Which should make the Renderer code simpler.
 * In the long run, it should pay off...
 */
module;

#define VK_NO_PROTOTYPES
#if defined(LIGHT_PLATFORM_LINUX)
	#define VK_USE_PLATFORM_WAYLAND_KHR
#elif defined(LIGHT_PLATFORM_WINDOWS)
	#define VK_USE_PLATFORM_WIN32_KHR
#else
	#error "Unsupported platform"
#endif

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#if defined(LIGHT_PLATFORM_LINUX)
struct wl_display;
struct wl_surface;
	#include <vulkan/vulkan_wayland.h>
	#include <wayland-client.h>
#endif
#if defined(LIGHT_PLATFORM_WINDOWS)
	#include <Windows.h>
	#undef max
	#undef min
	#undef MIN
	#undef MAX
#elif defined(LIGHT_PLATFORM_LINUX)
	#include <dlfcn.h>
#else
	#error "Unsupported platform"
#endif

export module renderer.vk.api_wrapper;
import preliminary;
import memory.null_on_move;
import math.vec3;
import math.vec2;
import debug.assertions;
import logger;

template<class... Ts>
struct overloads: Ts...
{
	using Ts::operator()...;
};

export namespace lt::renderer::vk {

using Bool32 = VkBool32;
using Flags = VkFlags;

namespace constants {

constexpr auto application_version = VK_MAKE_VERSION(1, 0, 0);
constexpr auto engine_version = VK_MAKE_VERSION(1, 0, 0);
constexpr auto api_version = VK_API_VERSION_1_4;
constexpr auto app_name = "Wayland Vulkan Example";
constexpr auto engine_name = "Wayland Vulkan Example";

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
constexpr auto physical_device_properties_2
    = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;

constexpr auto surface = VK_KHR_SURFACE_EXTENSION_NAME;
#if defined(LIGHT_PLATFORM_LINUX)
constexpr auto platform_surface = VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME;
#elif defined(LIGHT_PLATFORM_WINDOWS)
constexpr auto platform_surface = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;

#else
	#error "Unsupported platform"
#endif

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

namespace ColorComponentFlags {
enum T : VkFlags // NOLINT
{
	r_bit = VK_COLOR_COMPONENT_R_BIT,
	g_bit = VK_COLOR_COMPONENT_G_BIT,
	b_bit = VK_COLOR_COMPONENT_B_BIT,
	a_bit = VK_COLOR_COMPONENT_A_BIT,
};
};

namespace SampleCountFlags {
enum T : VkFlags // NOLINT
{
	_1_bit = VK_SAMPLE_COUNT_1_BIT,
	_2_bit = VK_SAMPLE_COUNT_2_BIT,
	_4_bit = VK_SAMPLE_COUNT_4_BIT,
	_8_bit = VK_SAMPLE_COUNT_8_BIT,
	_16_bit = VK_SAMPLE_COUNT_16_BIT,
	_32_bit = VK_SAMPLE_COUNT_32_BIT,
	_64_bit = VK_SAMPLE_COUNT_64_BIT,
};
}

namespace CompositeAlpha {
enum T : VkFlags // NOLINT
{
	opaque_bit = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	pre_multiplied_bit = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
	post_multiplied_bit = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
	inherit_bit = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
};
}

namespace CullModeFlags {
enum T : VkFlags // NOLINT
{
	none = VK_CULL_MODE_NONE,
	front_bit = VK_CULL_MODE_FRONT_BIT,
	back_bit = VK_CULL_MODE_BACK_BIT,
	front_and_back = VK_CULL_MODE_FRONT_AND_BACK,
};
}

namespace ShaderStageFlags {
enum T : VkFlags // NOLINT
{
	vertex_bit = VK_SHADER_STAGE_VERTEX_BIT,
	tessellation_control_bit = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
	tessellation_evaluation_bit = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
	geometry_bit = VK_SHADER_STAGE_GEOMETRY_BIT,
	fragment_bit = VK_SHADER_STAGE_FRAGMENT_BIT,
	compute_bit = VK_SHADER_STAGE_COMPUTE_BIT,
	all_graphics = VK_SHADER_STAGE_ALL_GRAPHICS,
	all = VK_SHADER_STAGE_ALL,
	raygen_bit_khr = VK_SHADER_STAGE_RAYGEN_BIT_KHR,
	any_hit_bit_khr = VK_SHADER_STAGE_ANY_HIT_BIT_KHR,
	closest_hit_bit_khr = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
	miss_bit_khr = VK_SHADER_STAGE_MISS_BIT_KHR,
	intersection_bit_khr = VK_SHADER_STAGE_INTERSECTION_BIT_KHR,
	callable_bit_khr = VK_SHADER_STAGE_CALLABLE_BIT_KHR,
	task_bit_ext = VK_SHADER_STAGE_TASK_BIT_EXT,
	mesh_bit_ext = VK_SHADER_STAGE_MESH_BIT_EXT,
};

}

enum class SharingMode : std::underlying_type_t<VkSharingMode>
{
	exclusive = VK_SHARING_MODE_EXCLUSIVE,
	concurrent = VK_SHARING_MODE_CONCURRENT,
};

enum class PolygonMode
{
	fill = VK_POLYGON_MODE_FILL,
	line = VK_POLYGON_MODE_LINE,
	point = VK_POLYGON_MODE_POINT,
};

enum class FrontFace : std::underlying_type_t<VkFrontFace>
{
	counter_clockwise = VK_FRONT_FACE_COUNTER_CLOCKWISE,
	clockwise = VK_FRONT_FACE_CLOCKWISE,
};

enum class BlendFactor : std::underlying_type_t<VkBlendFactor>
{
	zero = VK_BLEND_FACTOR_ZERO,
	one = VK_BLEND_FACTOR_ONE,
	src_color = VK_BLEND_FACTOR_SRC_COLOR,
	one_minus_src_color = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
	dst_color = VK_BLEND_FACTOR_DST_COLOR,
	one_minus_dst_color = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
	src_alpha = VK_BLEND_FACTOR_SRC_ALPHA,
	one_minus_src_alpha = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
	dst_alpha = VK_BLEND_FACTOR_DST_ALPHA,
	one_minus_dst_alpha = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
	constant_color = VK_BLEND_FACTOR_CONSTANT_COLOR,
	one_minus_constant_color = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
	constant_alpha = VK_BLEND_FACTOR_CONSTANT_ALPHA,
	one_minus_constant_alpha = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
	src_alpha_saturate = VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,
	src1_color = VK_BLEND_FACTOR_SRC1_COLOR,
	one_minus_src1_color = VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
	src1_alpha = VK_BLEND_FACTOR_SRC1_ALPHA,
	one_minus_src1_alpha = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
};

enum class PrimitiveTopology : std::underlying_type_t<VkPrimitiveTopology>
{
	point_list = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
	line_list = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
	line_strip = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
	triangle_list = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	triangle_strip = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
	triangle_fan = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
	line_list_with_adjacency = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
	line_strip_with_adjacency = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
	triangle_list_with_adjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
	triangle_strip_with_adjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
	patch_list = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,

};

enum class BlendOperation : std::underlying_type_t<VkBlendOp>
{
	add = VK_BLEND_OP_ADD,
	subtract = VK_BLEND_OP_SUBTRACT,
	reverse_subtract = VK_BLEND_OP_REVERSE_SUBTRACT,
	min = VK_BLEND_OP_MIN,
	max = VK_BLEND_OP_MAX,
	zero = VK_BLEND_OP_ZERO_EXT,
	src = VK_BLEND_OP_SRC_EXT,
	dst = VK_BLEND_OP_DST_EXT,
	src_over = VK_BLEND_OP_SRC_OVER_EXT,
	dst_over = VK_BLEND_OP_DST_OVER_EXT,
	src_in = VK_BLEND_OP_SRC_IN_EXT,
	dst_in = VK_BLEND_OP_DST_IN_EXT,
	src_out = VK_BLEND_OP_SRC_OUT_EXT,
	dst_out = VK_BLEND_OP_DST_OUT_EXT,
	src_atop = VK_BLEND_OP_SRC_ATOP_EXT,
	dst_atop = VK_BLEND_OP_DST_ATOP_EXT,
	_xor = VK_BLEND_OP_XOR_EXT,
	multiply = VK_BLEND_OP_MULTIPLY_EXT,
	screen = VK_BLEND_OP_SCREEN_EXT,
	overlay = VK_BLEND_OP_OVERLAY_EXT,
	darken = VK_BLEND_OP_DARKEN_EXT,
	lighten = VK_BLEND_OP_LIGHTEN_EXT,
	colordodge = VK_BLEND_OP_COLORDODGE_EXT,
	colorburn = VK_BLEND_OP_COLORBURN_EXT,
	hardlight = VK_BLEND_OP_HARDLIGHT_EXT,
	softlight = VK_BLEND_OP_SOFTLIGHT_EXT,
	difference = VK_BLEND_OP_DIFFERENCE_EXT,
	exclusion = VK_BLEND_OP_EXCLUSION_EXT,
	invert = VK_BLEND_OP_INVERT_EXT,
	invert_rgb = VK_BLEND_OP_INVERT_RGB_EXT,
	lineardodge = VK_BLEND_OP_LINEARDODGE_EXT,
	linearburn = VK_BLEND_OP_LINEARBURN_EXT,
	vividlight = VK_BLEND_OP_VIVIDLIGHT_EXT,
	linearlight = VK_BLEND_OP_LINEARLIGHT_EXT,
	pinlight = VK_BLEND_OP_PINLIGHT_EXT,
	hardmix = VK_BLEND_OP_HARDMIX_EXT,
	hsl_hue = VK_BLEND_OP_HSL_HUE_EXT,
	hsl_saturation = VK_BLEND_OP_HSL_SATURATION_EXT,
	hsl_color = VK_BLEND_OP_HSL_COLOR_EXT,
	hsl_luminosity = VK_BLEND_OP_HSL_LUMINOSITY_EXT,
	plus = VK_BLEND_OP_PLUS_EXT,
	plus_clamped = VK_BLEND_OP_PLUS_CLAMPED_EXT,
	plus_clamped_alpha = VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,
	plus_darker = VK_BLEND_OP_PLUS_DARKER_EXT,
	minus = VK_BLEND_OP_MINUS_EXT,
	minus_clamped = VK_BLEND_OP_MINUS_CLAMPED_EXT,
	contrast = VK_BLEND_OP_CONTRAST_EXT,
	invert_ovg = VK_BLEND_OP_INVERT_OVG_EXT,
	red = VK_BLEND_OP_RED_EXT,
	green = VK_BLEND_OP_GREEN_EXT,
	blue = VK_BLEND_OP_BLUE_EXT,
};

enum class ColorSpace : std::underlying_type_t<VkColorSpaceKHR>
{
	srgb_nonlinear = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
	display_p3_nonlinear = VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT,
	extended_srgb_linear = VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT,
	display_p3_linear = VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT,
	dci_p3_nonlinear = VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT,
	bt709_linear = VK_COLOR_SPACE_BT709_LINEAR_EXT,
	bt709_nonlinear = VK_COLOR_SPACE_BT709_NONLINEAR_EXT,
	bt2020_linear = VK_COLOR_SPACE_BT2020_LINEAR_EXT,
	hdr10_st2084 = VK_COLOR_SPACE_HDR10_ST2084_EXT,
	hdr10_hlg = VK_COLOR_SPACE_HDR10_HLG_EXT,
	adobe_rgb_linear = VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT,
	adobe_rgb_nonlinear = VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT,
	pass_through = VK_COLOR_SPACE_PASS_THROUGH_EXT,
	extended_srgb_nonlinear = VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT,
	display_native = VK_COLOR_SPACE_DISPLAY_NATIVE_AMD,
};

enum class Format : std::underlying_type_t<VkFormat>
{
	undefined = VK_FORMAT_UNDEFINED,
	r4g4_unorm_pack8 = VK_FORMAT_R4G4_UNORM_PACK8,
	r4g4b4a4_unorm_pack16 = VK_FORMAT_R4G4B4A4_UNORM_PACK16,
	b4g4r4a4_unorm_pack16 = VK_FORMAT_B4G4R4A4_UNORM_PACK16,
	r5g6b5_unorm_pack16 = VK_FORMAT_R5G6B5_UNORM_PACK16,
	b5g6r5_unorm_pack16 = VK_FORMAT_B5G6R5_UNORM_PACK16,
	r5g5b5a1_unorm_pack16 = VK_FORMAT_R5G5B5A1_UNORM_PACK16,
	b5g5r5a1_unorm_pack16 = VK_FORMAT_B5G5R5A1_UNORM_PACK16,
	a1r5g5b5_unorm_pack16 = VK_FORMAT_A1R5G5B5_UNORM_PACK16,
	r8_unorm = VK_FORMAT_R8_UNORM,
	r8_snorm = VK_FORMAT_R8_SNORM,
	r8_uscaled = VK_FORMAT_R8_USCALED,
	r8_sscaled = VK_FORMAT_R8_SSCALED,
	r8_uint = VK_FORMAT_R8_UINT,
	r8_sint = VK_FORMAT_R8_SINT,
	r8_srgb = VK_FORMAT_R8_SRGB,
	r8g8_unorm = VK_FORMAT_R8G8_UNORM,
	r8g8_snorm = VK_FORMAT_R8G8_SNORM,
	r8g8_uscaled = VK_FORMAT_R8G8_USCALED,
	r8g8_sscaled = VK_FORMAT_R8G8_SSCALED,
	r8g8_uint = VK_FORMAT_R8G8_UINT,
	r8g8_sint = VK_FORMAT_R8G8_SINT,
	r8g8_srgb = VK_FORMAT_R8G8_SRGB,
	r8g8b8_unorm = VK_FORMAT_R8G8B8_UNORM,
	r8g8b8_snorm = VK_FORMAT_R8G8B8_SNORM,
	r8g8b8_uscaled = VK_FORMAT_R8G8B8_USCALED,
	r8g8b8_sscaled = VK_FORMAT_R8G8B8_SSCALED,
	r8g8b8_uint = VK_FORMAT_R8G8B8_UINT,
	r8g8b8_sint = VK_FORMAT_R8G8B8_SINT,
	r8g8b8_srgb = VK_FORMAT_R8G8B8_SRGB,
	b8g8r8_unorm = VK_FORMAT_B8G8R8_UNORM,
	b8g8r8_snorm = VK_FORMAT_B8G8R8_SNORM,
	b8g8r8_uscaled = VK_FORMAT_B8G8R8_USCALED,
	b8g8r8_sscaled = VK_FORMAT_B8G8R8_SSCALED,
	b8g8r8_uint = VK_FORMAT_B8G8R8_UINT,
	b8g8r8_sint = VK_FORMAT_B8G8R8_SINT,
	b8g8r8_srgb = VK_FORMAT_B8G8R8_SRGB,
	r8g8b8a8_unorm = VK_FORMAT_R8G8B8A8_UNORM,
	r8g8b8a8_snorm = VK_FORMAT_R8G8B8A8_SNORM,
	r8g8b8a8_uscaled = VK_FORMAT_R8G8B8A8_USCALED,
	r8g8b8a8_sscaled = VK_FORMAT_R8G8B8A8_SSCALED,
	r8g8b8a8_uint = VK_FORMAT_R8G8B8A8_UINT,
	r8g8b8a8_sint = VK_FORMAT_R8G8B8A8_SINT,
	r8g8b8a8_srgb = VK_FORMAT_R8G8B8A8_SRGB,
	b8g8r8a8_unorm = VK_FORMAT_B8G8R8A8_UNORM,
	b8g8r8a8_snorm = VK_FORMAT_B8G8R8A8_SNORM,
	b8g8r8a8_uscaled = VK_FORMAT_B8G8R8A8_USCALED,
	b8g8r8a8_sscaled = VK_FORMAT_B8G8R8A8_SSCALED,
	b8g8r8a8_uint = VK_FORMAT_B8G8R8A8_UINT,
	b8g8r8a8_sint = VK_FORMAT_B8G8R8A8_SINT,
	b8g8r8a8_srgb = VK_FORMAT_B8G8R8A8_SRGB,
	a8b8g8r8_unorm_pack32 = VK_FORMAT_A8B8G8R8_UNORM_PACK32,
	a8b8g8r8_snorm_pack32 = VK_FORMAT_A8B8G8R8_SNORM_PACK32,
	a8b8g8r8_uscaled_pack32 = VK_FORMAT_A8B8G8R8_USCALED_PACK32,
	a8b8g8r8_sscaled_pack32 = VK_FORMAT_A8B8G8R8_SSCALED_PACK32,
	a8b8g8r8_uint_pack32 = VK_FORMAT_A8B8G8R8_UINT_PACK32,
	a8b8g8r8_sint_pack32 = VK_FORMAT_A8B8G8R8_SINT_PACK32,
	a8b8g8r8_srgb_pack32 = VK_FORMAT_A8B8G8R8_SRGB_PACK32,
	a2r10g10b10_unorm_pack32 = VK_FORMAT_A2R10G10B10_UNORM_PACK32,
	a2r10g10b10_snorm_pack32 = VK_FORMAT_A2R10G10B10_SNORM_PACK32,
	a2r10g10b10_uscaled_pack32 = VK_FORMAT_A2R10G10B10_USCALED_PACK32,
	a2r10g10b10_sscaled_pack32 = VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
	a2r10g10b10_uint_pack32 = VK_FORMAT_A2R10G10B10_UINT_PACK32,
	a2r10g10b10_sint_pack32 = VK_FORMAT_A2R10G10B10_SINT_PACK32,
	a2b10g10r10_unorm_pack32 = VK_FORMAT_A2B10G10R10_UNORM_PACK32,
	a2b10g10r10_snorm_pack32 = VK_FORMAT_A2B10G10R10_SNORM_PACK32,
	a2b10g10r10_uscaled_pack32 = VK_FORMAT_A2B10G10R10_USCALED_PACK32,
	a2b10g10r10_sscaled_pack32 = VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
	a2b10g10r10_uint_pack32 = VK_FORMAT_A2B10G10R10_UINT_PACK32,
	a2b10g10r10_sint_pack32 = VK_FORMAT_A2B10G10R10_SINT_PACK32,
	r16_unorm = VK_FORMAT_R16_UNORM,
	r16_snorm = VK_FORMAT_R16_SNORM,
	r16_uscaled = VK_FORMAT_R16_USCALED,
	r16_sscaled = VK_FORMAT_R16_SSCALED,
	r16_uint = VK_FORMAT_R16_UINT,
	r16_sint = VK_FORMAT_R16_SINT,
	r16_sf32 = VK_FORMAT_R16_SFLOAT,
	r16g16_unorm = VK_FORMAT_R16G16_UNORM,
	r16g16_snorm = VK_FORMAT_R16G16_SNORM,
	r16g16_uscaled = VK_FORMAT_R16G16_USCALED,
	r16g16_sscaled = VK_FORMAT_R16G16_SSCALED,
	r16g16_uint = VK_FORMAT_R16G16_UINT,
	r16g16_sint = VK_FORMAT_R16G16_SINT,
	r16g16_sf32 = VK_FORMAT_R16G16_SFLOAT,
	r16g16b16_unorm = VK_FORMAT_R16G16B16_UNORM,
	r16g16b16_snorm = VK_FORMAT_R16G16B16_SNORM,
	r16g16b16_uscaled = VK_FORMAT_R16G16B16_USCALED,
	r16g16b16_sscaled = VK_FORMAT_R16G16B16_SSCALED,
	r16g16b16_uint = VK_FORMAT_R16G16B16_UINT,
	r16g16b16_sint = VK_FORMAT_R16G16B16_SINT,
	r16g16b16_sf32 = VK_FORMAT_R16G16B16_SFLOAT,
	r16g16b16a16_unorm = VK_FORMAT_R16G16B16A16_UNORM,
	r16g16b16a16_snorm = VK_FORMAT_R16G16B16A16_SNORM,
	r16g16b16a16_uscaled = VK_FORMAT_R16G16B16A16_USCALED,
	r16g16b16a16_sscaled = VK_FORMAT_R16G16B16A16_SSCALED,
	r16g16b16a16_uint = VK_FORMAT_R16G16B16A16_UINT,
	r16g16b16a16_sint = VK_FORMAT_R16G16B16A16_SINT,
	r16g16b16a16_sf32 = VK_FORMAT_R16G16B16A16_SFLOAT,
	r32_uint = VK_FORMAT_R32_UINT,
	r32_sint = VK_FORMAT_R32_SINT,
	r32_sf32 = VK_FORMAT_R32_SFLOAT,
	r32g32_uint = VK_FORMAT_R32G32_UINT,
	r32g32_sint = VK_FORMAT_R32G32_SINT,
	r32g32_sf32 = VK_FORMAT_R32G32_SFLOAT,
	r32g32b32_uint = VK_FORMAT_R32G32B32_UINT,
	r32g32b32_sint = VK_FORMAT_R32G32B32_SINT,
	r32g32b32_sf32 = VK_FORMAT_R32G32B32_SFLOAT,
	r32g32b32a32_uint = VK_FORMAT_R32G32B32A32_UINT,
	r32g32b32a32_sint = VK_FORMAT_R32G32B32A32_SINT,
	r32g32b32a32_sf32 = VK_FORMAT_R32G32B32A32_SFLOAT,
	r64_uint = VK_FORMAT_R64_UINT,
	r64_sint = VK_FORMAT_R64_SINT,
	r64_sf32 = VK_FORMAT_R64_SFLOAT,
	r64g64_uint = VK_FORMAT_R64G64_UINT,
	r64g64_sint = VK_FORMAT_R64G64_SINT,
	r64g64_sf32 = VK_FORMAT_R64G64_SFLOAT,
	r64g64b64_uint = VK_FORMAT_R64G64B64_UINT,
	r64g64b64_sint = VK_FORMAT_R64G64B64_SINT,
	r64g64b64_sf32 = VK_FORMAT_R64G64B64_SFLOAT,
	r64g64b64a64_uint = VK_FORMAT_R64G64B64A64_UINT,
	r64g64b64a64_sint = VK_FORMAT_R64G64B64A64_SINT,
	r64g64b64a64_sf32 = VK_FORMAT_R64G64B64A64_SFLOAT,
	b10g11r11_ufloat_pack32 = VK_FORMAT_B10G11R11_UFLOAT_PACK32,
	e5b9g9r9_ufloat_pack32 = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
	d16_unorm = VK_FORMAT_D16_UNORM,
	x8_d24_unorm_pack32 = VK_FORMAT_X8_D24_UNORM_PACK32,
	d32_sf32 = VK_FORMAT_D32_SFLOAT,
	s8_uint = VK_FORMAT_S8_UINT,
	d16_unorm_s8_uint = VK_FORMAT_D16_UNORM_S8_UINT,
	d24_unorm_s8_uint = VK_FORMAT_D24_UNORM_S8_UINT,
	d32_sfloat_s8_uint = VK_FORMAT_D32_SFLOAT_S8_UINT,
	bc1_rgb_unorm_block = VK_FORMAT_BC1_RGB_UNORM_BLOCK,
	bc1_rgb_srgb_block = VK_FORMAT_BC1_RGB_SRGB_BLOCK,
	bc1_rgba_unorm_block = VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
	bc1_rgba_srgb_block = VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
	bc2_unorm_block = VK_FORMAT_BC2_UNORM_BLOCK,
	bc2_srgb_block = VK_FORMAT_BC2_SRGB_BLOCK,
	bc3_unorm_block = VK_FORMAT_BC3_UNORM_BLOCK,
	bc3_srgb_block = VK_FORMAT_BC3_SRGB_BLOCK,
	bc4_unorm_block = VK_FORMAT_BC4_UNORM_BLOCK,
	bc4_snorm_block = VK_FORMAT_BC4_SNORM_BLOCK,
	bc5_unorm_block = VK_FORMAT_BC5_UNORM_BLOCK,
	bc5_snorm_block = VK_FORMAT_BC5_SNORM_BLOCK,
	bc6h_ufloat_block = VK_FORMAT_BC6H_UFLOAT_BLOCK,
	bc6h_sfloat_block = VK_FORMAT_BC6H_SFLOAT_BLOCK,
	bc7_unorm_block = VK_FORMAT_BC7_UNORM_BLOCK,
	bc7_srgb_block = VK_FORMAT_BC7_SRGB_BLOCK,
	etc2_r8g8b8_unorm_block = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
	etc2_r8g8b8_srgb_block = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
	etc2_r8g8b8a1_unorm_block = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
	etc2_r8g8b8a1_srgb_block = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
	etc2_r8g8b8a8_unorm_block = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
	etc2_r8g8b8a8_srgb_block = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
	eac_r11_unorm_block = VK_FORMAT_EAC_R11_UNORM_BLOCK,
	eac_r11_snorm_block = VK_FORMAT_EAC_R11_SNORM_BLOCK,
	eac_r11g11_unorm_block = VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
	eac_r11g11_snorm_block = VK_FORMAT_EAC_R11G11_SNORM_BLOCK,
	astc_4X4_unorm_block = VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
	astc_4X4_srgb_block = VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
	astc_5X4_unorm_block = VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
	astc_5X4_srgb_block = VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
	astc_5X5_unorm_block = VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
	astc_5X5_srgb_block = VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
	astc_6X5_unorm_block = VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
	astc_6X5_srgb_block = VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
	astc_6X6_unorm_block = VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
	astc_6X6_srgb_block = VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
	astc_8X5_unorm_block = VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
	astc_8X5_srgb_block = VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
	astc_8X6_unorm_block = VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
	astc_8X6_srgb_block = VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
	astc_8X8_unorm_block = VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
	astc_8X8_srgb_block = VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
	astc_10X5_unorm_block = VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
	astc_10X5_srgb_block = VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
	astc_10X6_unorm_block = VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
	astc_10X6_srgb_block = VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
	astc_10X8_unorm_block = VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
	astc_10X8_srgb_block = VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
	astc_10X10_unorm_block = VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
	astc_10X10_srgb_block = VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
	astc_12X10_unorm_block = VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
	astc_12X10_srgb_block = VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
	astc_12X12_unorm_block = VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
	astc_12X12_srgb_block = VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
	g8b8g8r8_422_unorm = VK_FORMAT_G8B8G8R8_422_UNORM,
	b8g8r8g8_422_unorm = VK_FORMAT_B8G8R8G8_422_UNORM,
	g8_b8_r8_3plane_420_unorm = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
	g8_b8r8_2plane_420_unorm = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
	g8_b8_r8_3plane_422_unorm = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
	g8_b8r8_2plane_422_unorm = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
	g8_b8_r8_3plane_444_unorm = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
	r10x6_unorm_pack16 = VK_FORMAT_R10X6_UNORM_PACK16,
	r10x6g10x6_unorm_2pack16 = VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
	r10x6g10x6b10x6a10x6_unorm_4pack16 = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
	g10x6b10x6g10x6r10x6_422_unorm_4pack16 = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
	b10x6g10x6r10x6g10x6_422_unorm_4pack16 = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
	g10x6_b10x6_r10x6_3plane_420_unorm_3pack16
	= VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
	g10x6_b10x6r10x6_2plane_420_unorm_3pack16 = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
	g10x6_b10x6_r10x6_3plane_422_unorm_3pack16
	= VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
	g10x6_b10x6r10x6_2plane_422_unorm_3pack16 = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
	g10x6_b10x6_r10x6_3plane_444_unorm_3pack16
	= VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
	r12x4_unorm_pack16 = VK_FORMAT_R12X4_UNORM_PACK16,
	r12x4g12x4_unorm_2pack16 = VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
	r12x4g12x4b12x4a12x4_unorm_4pack16 = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
	g12x4b12x4g12x4r12x4_422_unorm_4pack16 = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
	b12x4g12x4r12x4g12x4_422_unorm_4pack16 = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
	g12x4_b12x4_r12x4_3plane_420_unorm_3pack16
	= VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
	g12x4_b12x4r12x4_2plane_420_unorm_3pack16 = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
	g12x4_b12x4_r12x4_3plane_422_unorm_3pack16
	= VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
	g12x4_b12x4r12x4_2plane_422_unorm_3pack16 = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
	g12x4_b12x4_r12x4_3plane_444_unorm_3pack16
	= VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
	g16b16g16r16_422_unorm = VK_FORMAT_G16B16G16R16_422_UNORM,
	b16g16r16g16_422_unorm = VK_FORMAT_B16G16R16G16_422_UNORM,
	g16_b16_r16_3plane_420_unorm = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
	g16_b16r16_2plane_420_unorm = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
	g16_b16_r16_3plane_422_unorm = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
	g16_b16r16_2plane_422_unorm = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
	g16_b16_r16_3plane_444_unorm = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
	g8_b8r8_2plane_444_unorm = VK_FORMAT_G8_B8R8_2PLANE_444_UNORM,
	g10x6_b10x6r10x6_2plane_444_unorm_3pack16 = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16,
	g12x4_b12x4r12x4_2plane_444_unorm_3pack16 = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16,
	g16_b16r16_2plane_444_unorm = VK_FORMAT_G16_B16R16_2PLANE_444_UNORM,
	a4r4g4b4_unorm_pack16 = VK_FORMAT_A4R4G4B4_UNORM_PACK16,
	a4b4g4r4_unorm_pack16 = VK_FORMAT_A4B4G4R4_UNORM_PACK16,
	astc_4X4_sfloat_block = VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK,
	astc_5X4_sfloat_block = VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK,
	astc_5X5_sfloat_block = VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK,
	astc_6X5_sfloat_block = VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK,
	astc_6X6_sfloat_block = VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK,
	astc_8X5_sfloat_block = VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK,
	astc_8X6_sfloat_block = VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK,
	astc_8X8_sfloat_block = VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK,
	astc_10X5_sfloat_block = VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK,
	astc_10X6_sfloat_block = VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK,
	astc_10X8_sfloat_block = VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK,
	astc_10X10_sfloat_block = VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK,
	astc_12X10_sfloat_block = VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK,
	astc_12X12_sfloat_block = VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK,
	a1b5g5r5_unorm_pack16 = VK_FORMAT_A1B5G5R5_UNORM_PACK16,
	a8_unorm = VK_FORMAT_A8_UNORM,
	pvrtc1_2bpp_unorm_block_img = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG,
	pvrtc1_4bpp_unorm_block_img = VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG,
	pvrtc2_2bpp_unorm_block_img = VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG,
	pvrtc2_4bpp_unorm_block_img = VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG,
	pvrtc1_2bpp_srgb_block_img = VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG,
	pvrtc1_4bpp_srgb_block_img = VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG,
	pvrtc2_2bpp_srgb_block_img = VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG,
	pvrtc2_4bpp_srgb_block_img = VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG,
	r8_bool_arm = VK_FORMAT_R8_BOOL_ARM,
	r16g16_sfixed5_nv = VK_FORMAT_R16G16_SFIXED5_NV,
	r10x6_uint_pack16_arm = VK_FORMAT_R10X6_UINT_PACK16_ARM,
	r10x6g10x6_uint_2pack16_arm = VK_FORMAT_R10X6G10X6_UINT_2PACK16_ARM,
	r10x6g10x6b10x6a10x6_uint_4pack16_arm = VK_FORMAT_R10X6G10X6B10X6A10X6_UINT_4PACK16_ARM,
	r12x4_uint_pack16_arm = VK_FORMAT_R12X4_UINT_PACK16_ARM,
	r12x4g12x4_uint_2pack16_arm = VK_FORMAT_R12X4G12X4_UINT_2PACK16_ARM,
	r12x4g12x4b12x4a12x4_uint_4pack16_arm = VK_FORMAT_R12X4G12X4B12X4A12X4_UINT_4PACK16_ARM,
	r14x2_uint_pack16_arm = VK_FORMAT_R14X2_UINT_PACK16_ARM,
	r14x2g14x2_uint_2pack16_arm = VK_FORMAT_R14X2G14X2_UINT_2PACK16_ARM,
	r14x2g14x2b14x2a14x2_uint_4pack16_arm = VK_FORMAT_R14X2G14X2B14X2A14X2_UINT_4PACK16_ARM,
	r14x2_unorm_pack16_arm = VK_FORMAT_R14X2_UNORM_PACK16_ARM,
	r14x2g14x2_unorm_2pack16_arm = VK_FORMAT_R14X2G14X2_UNORM_2PACK16_ARM,
	r14x2g14x2b14x2a14x2_unorm_4pack16_arm = VK_FORMAT_R14X2G14X2B14X2A14X2_UNORM_4PACK16_ARM,
	g14x2_b14x2r14x2_2plane_420_unorm_3pack16_arm
	= VK_FORMAT_G14X2_B14X2R14X2_2PLANE_420_UNORM_3PACK16_ARM,
	g14x2_b14x2r14x2_2plane_422_unorm_3pack16_arm
	= VK_FORMAT_G14X2_B14X2R14X2_2PLANE_422_UNORM_3PACK16_ARM,

};

struct Viewport
{
	math::vec2 origin;

	math::vec2 extent;

	f32 min_depth {};

	f32 max_depth {};
};

struct Rect2d
{
	math::ivec2 offset;

	math::uvec2 extent;
};

/** There is no global state in Vulkan and all per-application state is stored in a VkInstance
 * object. Creating a VkInstance object initializes the Vulkan library and allows the application to
 * pass information about itself to the implementation.
 */
class Instance
{
public:
	friend class Surface;
	friend class Gpu;
	friend class Messenger;

	struct Layer
	{
		struct Setting
		{
			std::string name;
			std::variant<std::vector<const char *>, u32, bool> values;
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

	~Instance()
	{
		// WIP;
	}

	void load_functions();

	[[nodiscard]] operator bool() const
	{
		return m_instance != VK_NULL_HANDLE;
	}

private:
	[[nodiscard]] auto get_vk_handle() const -> VkInstance
	{
		return m_instance;
	}

	memory::NullOnMove<VkInstance> m_instance {};
};

class Surface
{
public:
	friend class Gpu;

	friend class Swapchain;

	enum Transform : VkFlags
	{
		identity_bit = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		rotate_90_bit = VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR,
		rotate_180_bit = VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,
		rotate_270_bit = VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR,
		horizontal_mirror_bit = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR,
		horizontal_mirror_rotate_90_bit = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR,
		horizontal_mirror_rotate_180_bit
		= VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR,
		horizontal_mirror_rotate_270_bit
		= VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR,
		inherit_bit = VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR,
	};

	struct Format
	{
		::lt::renderer::vk::Format format;
		ColorSpace color_space;
	};

	struct Capabilities
	{
		u32 min_image_count;

		u32 max_image_count;

		math::uvec2 current_extent;

		math::uvec2 min_image_extent;

		math::uvec2 max_image_extent;

		u32 max_image_array_layers;

		std::underlying_type_t<Transform> supported_transforms;

		Transform current_transform;

		CompositeAlpha::T supported_composite_alpha;

		VkImageUsageFlags supported_usage_flags;
	};

	struct CreateInfo
	{
#if defined(LIGHT_PLATFORM_LINUX)
		wl_display *display;

		wl_surface *surface;
#elif defined(LIGHT_PLATFORM_WINDOWS)
		HWND window;
#else
	#error "Unsupported platform"
#endif
	};

	Surface() = default;

	Surface(const Instance &instance, const CreateInfo &info);

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
	[[nodiscard]] auto get_vk_handle() -> VkSurfaceKHR
	{
		return m_surface;
	}

	memory::NullOnMove<VkInstance> m_instance {};

	VkSurfaceKHR m_surface {};
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
		u32 max_image_dimension_1d;
		u32 max_image_dimension_2d;
		u32 max_image_dimension_3d;
		u32 max_image_dimension_cube;
		u32 max_image_array_layers;
		u32 max_texel_buffer_elements;
		u32 max_uniform_buffer_range;
		u32 max_storage_buffer_range;
		u32 max_push_constants_size;
		u32 max_memory_allocation_count;
		u32 max_sampler_allocation_count;
		size_t buffer_image_granularity;
		size_t sparse_address_space_size;
		u32 max_bound_descriptor_sets;
		u32 max_per_stage_descriptor_samplers;
		u32 max_per_stage_descriptor_uniform_buffers;
		u32 max_per_stage_descriptor_storage_buffers;
		u32 max_per_stage_descriptor_sampled_images;
		u32 max_per_stage_descriptor_storage_images;
		u32 max_per_stage_descriptor_input_attachments;
		u32 max_per_stage_resources;
		u32 max_descriptor_set_samplers;
		u32 max_descriptor_set_uniform_buffers;
		u32 max_descriptor_set_uniform_buffers_dynamic;
		u32 max_descriptor_set_storage_buffers;
		u32 max_descriptor_set_storage_buffers_dynamic;
		u32 max_descriptor_set_sampled_images;
		u32 max_descriptor_set_storage_images;
		u32 max_descriptor_set_input_attachments;
		u32 max_vertex_input_attributes;
		u32 max_vertex_input_bindings;
		u32 max_vertex_input_attribute_offset;
		u32 max_vertex_input_binding_stride;
		u32 max_vertex_output_components;
		u32 max_tessellation_generation_level;
		u32 max_tessellation_patch_size;
		u32 max_tessellation_control_per_vertex_input_components;
		u32 max_tessellation_control_per_vertex_output_components;
		u32 max_tessellation_control_per_patch_output_components;
		u32 max_tessellation_control_total_output_components;
		u32 max_tessellation_evaluation_input_components;
		u32 max_tessellation_evaluation_output_components;
		u32 max_geometry_shader_invocations;
		u32 max_geometry_input_components;
		u32 max_geometry_output_components;
		u32 max_geometry_output_vertices;
		u32 max_geometry_total_output_components;
		u32 max_fragment_input_components;
		u32 max_fragment_output_attachments;
		u32 max_fragment_dual_src_attachments;
		u32 max_fragment_combined_output_resources;
		u32 max_compute_shared_memory_size;
		std::array<u32, 3> max_compute_work_group_count;
		u32 max_compute_work_group_invocations;
		std::array<u32, 3> max_compute_work_group_size;
		u32 sub_pixel_precision_bits;
		u32 sub_texel_precision_bits;
		u32 mipmap_precision_bits;
		u32 max_draw_indexed_index_value;
		u32 max_draw_indirect_count;
		f32 max_sampler_lod_bias;
		f32 max_sampler_anisotropy;
		u32 max_viewports;
		std::array<u32, 2> max_viewport_dimensions;
		std::array<f32, 2> viewport_bounds_range;
		u32 viewport_sub_pixel_bits;
		size_t min_memory_map_alignment;
		VkDeviceSize min_texel_buffer_offset_alignment;
		VkDeviceSize min_uniform_buffer_offset_alignment;
		VkDeviceSize min_storage_buffer_offset_alignment;
		i32 min_texel_offset;
		u32 max_texel_offset;
		i32 min_texel_gather_offset;
		u32 max_texel_gather_offset;
		f32 min_interpolation_offset;
		f32 max_interpolation_offset;
		u32 sub_pixel_interpolation_offset_bits;
		u32 max_framebuffer_width;
		u32 max_framebuffer_height;
		u32 max_framebuffer_layers;
		VkSampleCountFlags framebuffer_color_sample_counts;
		VkSampleCountFlags framebuffer_depth_sample_counts;
		VkSampleCountFlags framebuffer_stencil_sample_counts;
		VkSampleCountFlags framebuffer_no_attachments_sample_counts;
		u32 max_color_attachments;
		VkSampleCountFlags sampled_image_color_sample_counts;
		VkSampleCountFlags sampled_image_integer_sample_counts;
		VkSampleCountFlags sampled_image_depth_sample_counts;
		VkSampleCountFlags sampled_image_stencil_sample_counts;
		VkSampleCountFlags storage_image_sample_counts;
		u32 max_sample_mask_words;
		Bool32 timestamp_compute_and_graphics;
		f32 timestamp_period;
		u32 max_clip_distances;
		u32 max_cull_distances;
		u32 max_combined_clip_and_cull_distances;
		u32 discrete_queue_priorities;
		std::array<f32, 2> point_size_range;
		std::array<f32, 2> line_width_range;
		f32 point_size_granularity;
		f32 line_width_granularity;
		Bool32 strict_lines;
		Bool32 standard_sample_locations;
		size_t optimal_buffer_copy_offset_alignment;
		size_t optimal_buffer_copy_row_pitch_alignment;
		size_t non_coherent_atom_size;
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
		u32 api_version;
		u32 driver_version;
		u32 vendor_id;
		u32 device_id;
		Type device_type;
		std::array<char, constants::max_physical_device_name> device_name;
		std::array<u8, constants::uuid_size> pipeline_cache_uuid;
		Limits limits;
		SparseProperties sparse_properties;
	};

	struct MemoryType
	{
		MemoryPropertyFlags::T property_flags;
		u32 heap_idx;
	};

	struct MemoryHeap
	{
		size_t size;
		MemoryHeapFlags::T flags;
	};

	struct MemoryProperties
	{
		std::vector<MemoryType> memory_types;
		std::vector<MemoryHeap> memory_heaps;
	};

	struct QueueFamilyProperties
	{
		QueueFlags::T queue_flags {};
		u32 queue_count {};
		u32 timestamp_valid_bits {};
		math::uvec3 min_image_transfer_granularity;
	};

	[[nodiscard]]
	static auto enumerate(const Instance &instance) -> std::vector<Gpu>;

	Gpu() = default;

	Gpu(Gpu &&) = default;

	Gpu(const Gpu &) = default;

	auto operator=(Gpu &&) -> Gpu & = default;

	auto operator=(const Gpu &) -> Gpu & = default;

	~Gpu()
	{
		// WIP;
	}

	[[nodiscard]] auto get_features() const -> Features;

	[[nodiscard]] auto get_supported_dynamic_rendering_features() const -> DynamicRenderingFeatures;

	[[nodiscard]] auto get_supported_descriptor_indexing_features() const
	    -> DescriptorIndexingFeatures;

	[[nodiscard]] auto get_properties() const -> Properties;

	[[nodiscard]] auto get_memory_properties() const -> MemoryProperties;

	[[nodiscard]] auto get_queue_family_properties() const -> std::vector<QueueFamilyProperties>;

	[[nodiscard]] auto queue_family_supports_surface(
	    const Surface &surface,
	    u32 queue_family_idx
	) const -> bool;

	[[nodiscard]] auto get_surface_capabilities(Surface &surface) const -> Surface::Capabilities;

	[[nodiscard]] auto get_surface_formats(Surface &surface) const -> std::vector<Surface::Format>;

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
	friend class Queue;
	friend class Memory;
	friend class Buffer;
	friend class Swapchain;
	friend class Image;
	friend class ImageView;
	friend class Pipeline;
	friend class Semaphore;
	friend class Fence;
	friend class ShaderModule;
	friend class DescriptorSetLayout;
	friend class PipelineLayout;
	friend class CommandPool;
	friend class DescriptorPool;

	struct CreateInfo
	{
		std::set<u32> queue_indices;

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
	    -> std::span<byte>;

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
	[[nodiscard]] auto get_vk_handle() -> VkDevice
	{
		return m_device.get();
	}

	memory::NullOnMove<VkDevice> m_device {};
};

class Semaphore
{
public:
	friend class Device;
	friend class Swapchain;
	friend class Queue;

	static constexpr auto object_type = VK_OBJECT_TYPE_SEMAPHORE;

	Semaphore() = default;

	Semaphore(Device &device);

	Semaphore(Semaphore &&) = default;

	Semaphore(const Semaphore &) = delete;

	auto operator=(Semaphore &&) -> Semaphore & = default;

	auto operator=(const Semaphore &) -> Semaphore & = delete;

	~Semaphore();

private:
	[[nodiscard]] auto get_vk_handle() -> VkSemaphore
	{
		return m_semaphore;
	}

	[[nodiscard]] auto get_addressof_vk_handle() -> VkSemaphore *
	{
		return &m_semaphore;
	}

	memory::NullOnMove<VkDevice> m_device;

	VkSemaphore m_semaphore;
};

class Fence
{
public:
	friend class Queue;

	static constexpr auto object_type = VK_OBJECT_TYPE_FENCE;

	struct CreateInfo
	{
		bool signaled;
	};

	Fence() = default;

	Fence(Device &device, CreateInfo info);

	Fence(Fence &&) = default;

	Fence(const Fence &) = delete;

	auto operator=(Fence &&) -> Fence & = default;

	auto operator=(const Fence &) -> Fence & = delete;

	~Fence();

	operator VkFence()
	{
		return m_fence;
	}

	void wait();

	void reset();

private:
	[[nodiscard]] auto get_vk_handle() -> VkFence
	{
		return m_fence;
	}

	[[nodiscard]] auto get_addressof_vk_handle() -> VkFence *
	{
		return &m_fence;
	}

	memory::NullOnMove<VkDevice> m_device;

	VkFence m_fence;
};

class Buffer
{
public:
	friend class Device;
	friend class Memory;
	friend class CommandBuffer;

	static constexpr auto object_type = VK_OBJECT_TYPE_BUFFER;

	enum UsageFlags : VkFlags
	{
		transfer_src_bit = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		transfer_dst_bit = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		uniform_texel_buffer_bit = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
		storage_texel_buffer_bit = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
		uniform_buffer_bit = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		storage_buffer_bit = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		index_buffer_bit = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		vertex_buffer_bit = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		indirect_buffer_bit = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
		shader_device_address_bit = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
		video_decode_src_bit = VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR,
		video_decode_dst_bit = VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR,
		transform_feedback_buffer_bit = VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT,
		transform_feedback_counter_buffer_bit
		= VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT,
		conditional_rendering_bit = VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT,
		acceleration_structure_build_input_read_only_bit
		= VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
		acceleration_structure_storage_bit = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR,
		shader_binding_table_bit = VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR,
		video_encode_dst_bit = VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR,
		video_encode_src_bit = VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR,
		sampler_descriptor_buffer_bit = VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT,
		resource_descriptor_buffer_bit = VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT,
		push_descriptors_descriptor_buffer_bit
		= VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT,
		micromap_build_input_read_only_bit = VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT,
		micromap_storage_bit = VK_BUFFER_USAGE_MICROMAP_STORAGE_BIT_EXT,
		tile_memory_bit_qcom = VK_BUFFER_USAGE_TILE_MEMORY_BIT_QCOM,
	};

	struct MemoryRequirements
	{
		size_t size;
		size_t alignment;
		u32 memory_type_bits;
	};

	struct CreateInfo
	{
		size_t size;

		UsageFlags usage;

		SharingMode sharing_mode;

		std::vector<uint32_t> queue_family_indices;

		std::string_view name;
	};

	Buffer(Device &device, CreateInfo info);

	~Buffer();

	Buffer(Buffer &&) = default;

	Buffer(const Buffer &) = delete;

	auto operator=(Buffer &&) -> Buffer & = default;

	auto operator=(const Buffer &) -> Buffer & = delete;

	[[nodiscard]] auto get_memory_requirements() const -> MemoryRequirements;

private:
	[[nodiscard]] auto get_vk_handle() -> VkBuffer
	{
		return m_buffer;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkBuffer m_buffer {};
};

class Image
{
public:
	friend class Device;
	friend class Swapchain;
	friend class ImageView;
	friend class CommandBuffer;

	static constexpr auto object_type = VK_OBJECT_TYPE_IMAGE_VIEW;

	enum AspectFlags : VkFlags
	{
		color_bit = VK_IMAGE_ASPECT_COLOR_BIT,
		depth_bit = VK_IMAGE_ASPECT_DEPTH_BIT,
		stencil_bit = VK_IMAGE_ASPECT_STENCIL_BIT,
		metadata_bit = VK_IMAGE_ASPECT_METADATA_BIT,
		plane_0_bit = VK_IMAGE_ASPECT_PLANE_0_BIT,
		plane_1_bit = VK_IMAGE_ASPECT_PLANE_1_BIT,
		plane_2_bit = VK_IMAGE_ASPECT_PLANE_2_BIT,
		none = VK_IMAGE_ASPECT_NONE,
		memory_plane_0_bit = VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT,
		memory_plane_1_bit = VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT,
		memory_plane_2_bit = VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT,
		memory_plane_3_bit = VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT,
	};

	enum class Layout : std::underlying_type_t<VkImageLayout>
	{
		undefined = VK_IMAGE_LAYOUT_UNDEFINED,
		general = VK_IMAGE_LAYOUT_GENERAL,
		color_attachment_optimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		depth_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		depth_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		shader_read_only_optimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		transfer_src_optimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		transfer_dst_optimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		preinitialized = VK_IMAGE_LAYOUT_PREINITIALIZED,
		depth_read_only_stencil_attachment_optimal
		= VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		depth_attachment_stencil_read_only_optimal
		= VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		depth_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
		depth_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
		stencil_attachment_optimal = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
		stencil_read_only_optimal = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
		read_only_optimal = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL,
		attachment_optimal = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
		rendering_local_read = VK_IMAGE_LAYOUT_RENDERING_LOCAL_READ,
		present_src = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		video_decode_dst = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR,
		video_decode_src = VK_IMAGE_LAYOUT_VIDEO_DECODE_SRC_KHR,
		video_decode_dpb = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR,
		shared_present = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
		fragment_density_map_optimal = VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT,
		fragment_shading_rate_attachment_optimal
		= VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR,
		video_encode_dst = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DST_KHR,
		video_encode_src = VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR,
		video_encode_dpb = VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR,
		attachment_feedback_loop_optimal = VK_IMAGE_LAYOUT_ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT,
		tensor_aliasing_arm = VK_IMAGE_LAYOUT_TENSOR_ALIASING_ARM,
		video_encode_quantization_map = VK_IMAGE_LAYOUT_VIDEO_ENCODE_QUANTIZATION_MAP_KHR,
		zero_initialized = VK_IMAGE_LAYOUT_ZERO_INITIALIZED_EXT,
	};

	enum Usage : VkFlags
	{
		transfer_src_bit = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
		transfer_dst_bit = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		sampled_bit = VK_IMAGE_USAGE_SAMPLED_BIT,
		storage_bit = VK_IMAGE_USAGE_STORAGE_BIT,
		color_attachment_bit = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		depth_stencil_attachment_bit = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		transient_attachment_bit = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
		input_attachment_bit = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
		host_transfer_bit = VK_IMAGE_USAGE_HOST_TRANSFER_BIT,
		video_decode_dst_bit = VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR,
		video_decode_src_bit = VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR,
		video_decode_dpb_bit = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR,
		fragment_density_map_bit = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT,
		fragment_shading_rate_attachment_bit
		= VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
		video_encode_dst_bit = VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR,
		video_encode_src_bit = VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR,
		video_encode_dpb_bit = VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR,
		attachment_feedback_loop_bit = VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT,
		invocation_mask_bit_huawei = VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI,
		sample_weight_bit_qcom = VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM,
		sample_block_match_bit_qcom = VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM,
		tensor_aliasing_bit_arm = VK_IMAGE_USAGE_TENSOR_ALIASING_BIT_ARM,
		tile_memory_bit_qcom = VK_IMAGE_USAGE_TILE_MEMORY_BIT_QCOM,
		video_encode_quantization_delta_map_bit
		= VK_IMAGE_USAGE_VIDEO_ENCODE_QUANTIZATION_DELTA_MAP_BIT_KHR,
		video_encode_emphasis_map_bit = VK_IMAGE_USAGE_VIDEO_ENCODE_EMPHASIS_MAP_BIT_KHR,
	};

	struct Range
	{
		Image::AspectFlags aspect_flags;
		u32 base_mip_level;
		u32 level_count;
		u32 base_array_layer;
		u32 layer_count;
	};

	static constexpr auto full_color_range = Range {
		.aspect_flags = AspectFlags::color_bit,
		.base_mip_level = 0u,
		.level_count = VK_REMAINING_MIP_LEVELS,
		.base_array_layer = 0u,
		.layer_count = VK_REMAINING_ARRAY_LAYERS,
	};

	struct CreateInfo
	{
	};

	Image() = default;

	Image(Device &device, CreateInfo info);

	Image(Image &&) noexcept = default;

	Image(const Image &) = delete;

	auto operator=(Image &&) noexcept -> Image & = default;

	auto operator=(const Image &) -> Image & = delete;

	~Image();

private:
	Image(VkImage image) noexcept; // for swapchain images

	[[nodiscard]] auto get_vk_handle() -> VkImage
	{
		return m_image;
	}

	memory::NullOnMove<VkDevice> m_device;

	VkImage m_image;
};

class ImageView
{
public:
	friend class Device;
	friend class CommandBuffer;

	static constexpr auto object_type = VK_OBJECT_TYPE_IMAGE_VIEW;

	enum class Type
	{

		_1d = VK_IMAGE_VIEW_TYPE_1D,
		_2d = VK_IMAGE_VIEW_TYPE_2D,
		_3d = VK_IMAGE_VIEW_TYPE_3D,
		cube = VK_IMAGE_VIEW_TYPE_CUBE,
		_1d_array = VK_IMAGE_VIEW_TYPE_1D_ARRAY,
		_2d_array = VK_IMAGE_VIEW_TYPE_2D_ARRAY,
		cube_array = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,
	};

	enum class Swizzle
	{
		identity = VK_COMPONENT_SWIZZLE_IDENTITY,
		zero = VK_COMPONENT_SWIZZLE_ZERO,
		one = VK_COMPONENT_SWIZZLE_ONE,
		r = VK_COMPONENT_SWIZZLE_R,
		g = VK_COMPONENT_SWIZZLE_G,
		b = VK_COMPONENT_SWIZZLE_B,
		a = VK_COMPONENT_SWIZZLE_A,
	};

	struct CreateInfo
	{
		Type type;

		Format format;

		std::array<Swizzle, 4> components;

		Image::Range range;

		std::string_view name;
	};

	ImageView() = default;

	ImageView(Device &device, Image &image, CreateInfo info);

	ImageView(ImageView &&) = default;

	ImageView(const ImageView &) = delete;

	auto operator=(ImageView &&) -> ImageView & = default;

	auto operator=(const ImageView &) -> ImageView & = delete;

	~ImageView();

private:
	[[nodiscard]] auto get_vk_handle() -> VkImageView
	{
		return m_image_view;
	}

	memory::NullOnMove<VkDevice> m_device;

	VkImageView m_image_view;
};

class ShaderModule
{
public:
	friend class Device;
	friend class Pipeline;

	static constexpr auto object_type = VK_OBJECT_TYPE_SHADER_MODULE;

	struct CreateInfo
	{
		std::vector<byte> code;

		std::string_view name;
	};

	ShaderModule() = default;

	ShaderModule(Device &device, CreateInfo info);

	~ShaderModule();

	ShaderModule(ShaderModule &&) = default;

	ShaderModule(const ShaderModule &) = delete;

	auto operator=(ShaderModule &&) -> ShaderModule & = default;

	auto operator=(const ShaderModule &) -> ShaderModule & = delete;

private:
	[[nodiscard]] auto get_vk_handle()
	{
		return m_shader_module;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkShaderModule m_shader_module {};
};

class DescriptorSet
{
public:
	friend class Device;
	friend class DescriptorPool;
	friend class CommandBuffer;

	enum class Type : std::underlying_type_t<VkDescriptorType>
	{
		sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
		combined_image_sampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		sampled_image = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		storage_image = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		uniform_texel_buffer = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		storage_texel_buffer = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		uniform_buffer = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		storage_buffer = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		uniform_buffer_dynamic = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		storage_buffer_dynamic = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		input_attachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
		inline_uniform_block = VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK,
		acceleration_structure = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
		acceleration_structure_nv = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV,
		sample_weight_image_qcom = VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM,
		block_match_image_qcom = VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM,
		tensor_arm = VK_DESCRIPTOR_TYPE_TENSOR_ARM,
		_mutable = VK_DESCRIPTOR_TYPE_MUTABLE_EXT,
		partitioned_acceleration_structure_nv
		= VK_DESCRIPTOR_TYPE_PARTITIONED_ACCELERATION_STRUCTURE_NV,
	};

	DescriptorSet() = default;

	DescriptorSet(DescriptorSet &&) = default;

	DescriptorSet(const DescriptorSet &) = delete;

	auto operator=(DescriptorSet &&) -> DescriptorSet & = default;

	auto operator=(const DescriptorSet &) -> DescriptorSet & = delete;

	~DescriptorSet() = default;

private:
	[[nodiscard]] auto get_vk_handle() -> VkDescriptorSet
	{
		return m_descriptor_set;
	}

	[[nodiscard]] auto get_vk_handle_addr() -> VkDescriptorSet *
	{
		return &m_descriptor_set;
	}

	DescriptorSet(VkDescriptorSet descriptor_set);

	VkDescriptorSet m_descriptor_set {};
};

class DescriptorSetLayout
{
public:
	friend class Device;
	friend class PipelineLayout;
	friend class DescriptorPool;

	static constexpr auto object_type = VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT;

	struct Binding
	{
		enum FlagBits : std::underlying_type_t<VkDescriptorBindingFlagBits>
		{
			update_after_bind = VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT,
			update_unused_while_pending = VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT,
			partially_bound = VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT,
			variable_descriptor_count = VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT,
		};

		Flags flags;

		u32 idx;

		u32 count;

		DescriptorSet::Type type;

		ShaderStageFlags::T shader_stages;
	};

	struct CreateInfo
	{
		enum FlagBits : std::underlying_type_t<VkDescriptorSetLayoutCreateFlagBits>
		{
			update_after_bind_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT,
			push_descriptor = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT,
			descriptor_buffer = VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT,
			embedded_immutable_samplers
			= VK_DESCRIPTOR_SET_LAYOUT_CREATE_EMBEDDED_IMMUTABLE_SAMPLERS_BIT_EXT,
			indirect_bindable_nv = VK_DESCRIPTOR_SET_LAYOUT_CREATE_INDIRECT_BINDABLE_BIT_NV,
			host_only_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_EXT,
			per_stage_nv = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PER_STAGE_BIT_NV,
		};

		Flags flags;

		std::vector<Binding> bindings;

		std::string_view name;
	};

	DescriptorSetLayout() = default;

	DescriptorSetLayout(Device &device, CreateInfo info);

	DescriptorSetLayout(DescriptorSetLayout &&) = default;

	DescriptorSetLayout(const DescriptorSetLayout &) = delete;

	auto operator=(DescriptorSetLayout &&) -> DescriptorSetLayout & = default;

	auto operator=(const DescriptorSetLayout &) -> DescriptorSetLayout & = delete;

	~DescriptorSetLayout();

private:
	[[nodiscard]] auto get_vk_handle() -> VkDescriptorSetLayout
	{
		return m_descriptor_set_layout;
	}

	[[nodiscard]] auto get_vk_handle_addr() -> VkDescriptorSetLayout *
	{
		return &m_descriptor_set_layout;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkDescriptorSetLayout m_descriptor_set_layout {};
};

class DescriptorPool
{
public:
	friend class Device;

	static constexpr auto object_type = VK_OBJECT_TYPE_DESCRIPTOR_POOL;

	struct Size
	{
		DescriptorSet::Type type;

		u32 count;
	};

	struct CreateInfo
	{
		std::vector<Size> sizes;

		u32 max_sets;

		std::string_view name;
	};

	DescriptorPool() = default;

	DescriptorPool(Device &device, CreateInfo info);

	DescriptorPool(DescriptorPool &&) = default;

	DescriptorPool(const DescriptorPool &) = delete;

	auto operator=(DescriptorPool &&) -> DescriptorPool & = default;

	auto operator=(const DescriptorPool &) -> DescriptorPool & = delete;

	~DescriptorPool();

	[[nodiscard]] auto allocate(DescriptorSetLayout &layout) -> DescriptorSet;

private:
	[[nodiscard]] auto get_vk_handle() -> VkDescriptorPool
	{
		return m_descriptor_pool;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkDescriptorPool m_descriptor_pool {};
};

class Pipeline
{
public:
	friend class Device;
	friend class CommandBuffer;

	static constexpr auto object_type = VK_OBJECT_TYPE_PIPELINE;

	enum class BindPoint : std::underlying_type_t<VkPipelineBindPoint>
	{
		graphics = VK_PIPELINE_BIND_POINT_GRAPHICS,
		compute = VK_PIPELINE_BIND_POINT_COMPUTE,
		ray_tracing = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
		data_graph = VK_PIPELINE_BIND_POINT_DATA_GRAPH_ARM,
	};

	struct InputAssemblyState
	{
		PrimitiveTopology topology;

		bool primitive_restart_enabled;
	};

	struct ViewportState
	{
		u32 viewport_count;

		u32 scissor_count;
	};

	struct RasterizationState
	{
		bool depth_clamp_enabled;

		bool discard_enabled;

		PolygonMode polygon_mode;

		CullModeFlags::T cull_mode;

		FrontFace front_face;

		bool depth_bias_enabled;

		f32 depth_bias_constant_factor;

		f32 depth_bias_clamp;

		f32 depth_bias_slope_factor;

		f32 line_width;
	};

	struct MultisamplingState
	{
		SampleCountFlags::T rasterizer_samples;

		bool sample_shading_enabled;

		f32 min_sample_shading;

		bool alpha_to_coverage_enabled;

		bool alpha_to_one_enabled;
	};

	struct AttachmentState
	{
		struct Color
		{
			vk::Format format;

			bool blend_enabled;

			BlendFactor src_color;

			BlendFactor dst_color;

			BlendFactor src_alpha;

			BlendFactor dst_alpha;

			BlendOperation color_op;

			BlendOperation alpha_op;

			ColorComponentFlags::T color_write_mask;
		};

		std::vector<Color> color_attachments;

		std::optional<vk::Format> depth_attachment;

		std::optional<vk::Format> stencil_attachment;
	};

	struct CreateInfo
	{
		std::vector<std::pair<ShaderModule, ShaderStageFlags::T>> shaders;

		InputAssemblyState input_assembly_state;

		ViewportState viewport_state;

		RasterizationState rasterization_state;

		MultisamplingState multisampling_state;

		AttachmentState attachment_state;

		std::string_view debug_name;
	};

	Pipeline() = default;

	Pipeline(Device &device, class PipelineLayout &layout, CreateInfo info);

	Pipeline(Pipeline &&) = default;

	Pipeline(const Pipeline &) = delete;

	auto operator=(Pipeline &&) -> Pipeline & = default;

	auto operator=(const Pipeline &) -> Pipeline & = delete;

	~Pipeline();

private:
	[[nodiscard]] auto get_vk_handle() -> VkPipeline
	{
		return m_pipeline;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkPipeline m_pipeline {};
};

class PipelineLayout
{
public:
	friend class Pipeline;
	friend class Device;
	friend class CommandBuffer;

	static constexpr auto object_type = VK_OBJECT_TYPE_PIPELINE_LAYOUT;

	struct PushConstantRange
	{
		ShaderStageFlags::T shader_stages;
		u32 offset;
		u32 size;
	};

	struct CreateInfo
	{
		std::vector<DescriptorSetLayout *> descriptor_set_layouts;

		std::vector<PushConstantRange> push_constant_ranges;

		std::string_view name;
	};

	PipelineLayout() = default;

	PipelineLayout(Device &device, CreateInfo info);

	PipelineLayout(PipelineLayout &&) = default;

	PipelineLayout(const PipelineLayout &) = delete;

	auto operator=(PipelineLayout &&) -> PipelineLayout & = default;

	auto operator=(const PipelineLayout &) -> PipelineLayout & = delete;

	~PipelineLayout();

private:
	[[nodiscard]] auto get_vk_handle() -> VkPipelineLayout
	{
		return m_pipeline_layout;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkPipelineLayout m_pipeline_layout {};
};

class CommandBuffer
{
public:
	friend class Device;
	friend class Queue;
	friend class CommandPool;

	struct BeginInfo
	{
	};

	struct BufferCopyInfo
	{
		Buffer *src_buffer;

		Buffer *dst_buffer;

		size_t src_offset;

		size_t dst_offset;

		size_t size;
	};

	struct PushConstantsInfo
	{
		class PipelineLayout *layout;

		vk::ShaderStageFlags::T shader_stages;

		u32 offset;

		u32 size;

		void *data;
	};

	struct ImageBarrierInfo
	{
		enum AccessFlagBits : std::underlying_type_t<VkAccessFlagBits>
		{
			indirect_command_read = VK_ACCESS_INDIRECT_COMMAND_READ_BIT,
			index_read = VK_ACCESS_INDEX_READ_BIT,
			vertex_attribute_read = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
			uniform_read = VK_ACCESS_UNIFORM_READ_BIT,
			input_attachment_read = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
			shader_read = VK_ACCESS_SHADER_READ_BIT,
			shader_write = VK_ACCESS_SHADER_WRITE_BIT,
			color_attachment_read = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
			color_attachment_write = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
			depth_stencil_attachment_read = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
			depth_stencil_attachment_write = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			transfer_read = VK_ACCESS_TRANSFER_READ_BIT,
			transfer_write = VK_ACCESS_TRANSFER_WRITE_BIT,
			host_read = VK_ACCESS_HOST_READ_BIT,
			host_write = VK_ACCESS_HOST_WRITE_BIT,
			memory_read = VK_ACCESS_MEMORY_READ_BIT,
			memory_write = VK_ACCESS_MEMORY_WRITE_BIT,
			none = VK_ACCESS_NONE,
			transform_feedback_write = VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT,
			transform_feedback_counter_read = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT,
			transform_feedback_counter_write = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT,
			conditional_rendering_read = VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT,
			color_attachment_read_noncoherent = VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT,
			acceleration_structure_read_khr = VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR,
			acceleration_structure_write_khr = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR,
			fragment_density_map_read = VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT,
			fragment_shading_rate_attachment_read_khr
			= VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR,
			command_preprocess_read = VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_EXT,
			command_preprocess_write = VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_EXT,
		};

		class Image *image;

		Image::Range range;

		vk::PipelineStageFlags::T src_stages;

		vk::PipelineStageFlags::T dst_stages;

		Flags src_accesses;

		Flags dst_accesses;

		Image::Layout src_layout;

		Image::Layout dst_layout;
	};

	struct RenderingInfo
	{
		struct AttachmentInfo
		{
			enum class ResolveModeBits : std::underlying_type_t<VkResolveModeFlagBits>
			{
				none = VK_RESOLVE_MODE_NONE,
				sample_zero = VK_RESOLVE_MODE_SAMPLE_ZERO_BIT,
				average = VK_RESOLVE_MODE_AVERAGE_BIT,
				min = VK_RESOLVE_MODE_MIN_BIT,
				max = VK_RESOLVE_MODE_MAX_BIT,
			};

			enum class LoadOperation : std::underlying_type_t<VkAttachmentLoadOp>
			{
				load = VK_ATTACHMENT_LOAD_OP_LOAD,
				clear = VK_ATTACHMENT_LOAD_OP_CLEAR,
				dont_care = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				none = VK_ATTACHMENT_LOAD_OP_NONE,
			};

			enum class StoreOperation : std::underlying_type_t<VkAttachmentStoreOp>
			{
				store = VK_ATTACHMENT_STORE_OP_STORE,
				dont_care = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				none = VK_ATTACHMENT_STORE_OP_NONE,
			};

			ImageView *view;

			Image::Layout layout;

			LoadOperation load_operation;

			StoreOperation store_operation;

			std::array<f32, 4> color_clear_values;

			f32 depth_clear_value;

			u32 stencil_clear_value;

			Flags resolve_mode_flags;
		};

		math::ivec2 area_offset;

		math::uvec2 area_extent;

		std::vector<AttachmentInfo> color_attachments;
	};

	struct DrawInfo
	{
		u32 vertex_count;

		u32 instance_count;

		u32 first_vertex;

		u32 first_instance;
	};

	CommandBuffer() = default;

	CommandBuffer(CommandBuffer &&) = default;

	CommandBuffer(const CommandBuffer &) = delete;

	auto operator=(CommandBuffer &&) -> CommandBuffer & = default;

	auto operator=(const CommandBuffer &) -> CommandBuffer & = delete;

	void begin(BeginInfo info = {});

	void end();

	void copy(BufferCopyInfo info);

	void push_constants(PushConstantsInfo info);

	void image_barrier(ImageBarrierInfo info);

	void begin_rendering(RenderingInfo info);

	void end_rendering();

	void bind_pipeline(Pipeline &pipeline, Pipeline::BindPoint bind_point);

	void draw(DrawInfo info);

	void set_viewport(Viewport viewport);

	void set_scissor(Rect2d scissor);

	void bind_descriptor_set(
	    DescriptorSet &set,
	    Pipeline::BindPoint bind_point,
	    PipelineLayout &layout,
	    uint32_t idx
	);


private:
	CommandBuffer(VkCommandBuffer buffer);

	[[nodiscard]] auto get_vk_handle() -> VkCommandBuffer
	{
		return m_buffer;
	}

	[[nodiscard]] auto get_addressof_vk_handle() -> VkCommandBuffer *
	{
		return &m_buffer;
	}

	VkCommandBuffer m_buffer;
};

class CommandPool
{
public:
	friend class Device;

	static constexpr auto object_type = VK_OBJECT_TYPE_COMMAND_POOL;

	struct CreateInfo
	{
		enum FlagBits : std::underlying_type_t<VkCommandPoolCreateFlagBits>
		{
			transient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
			reset_command_buffer = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
			_protected = VK_COMMAND_POOL_CREATE_PROTECTED_BIT,
		};

		Flags flags;

		std::string_view name;
	};

	enum class BufferLevel
	{
		secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
		primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	};

	CommandPool() = default;

	CommandPool(Device &device, CreateInfo info);

	~CommandPool();

	CommandPool(CommandPool &&) = default;

	CommandPool(const CommandPool &) = delete;

	auto operator=(CommandPool &&) -> CommandPool & = default;

	auto operator=(const CommandPool &) -> CommandPool & = delete;

	[[nodiscard]] auto allocate(uint32_t count, BufferLevel level) -> std::vector<CommandBuffer>;

private:
	[[nodiscard]] auto get_vk_handle() -> VkCommandPool
	{
		return m_pool;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkCommandPool m_pool {};
};

class Swapchain
{
public:
	friend class Queue;
	friend class Device;

	static constexpr auto object_type = VK_OBJECT_TYPE_SWAPCHAIN_KHR;

	enum class PresentMode
	{
		immediate = VK_PRESENT_MODE_IMMEDIATE_KHR,
		mailbox = VK_PRESENT_MODE_MAILBOX_KHR,
		fifo = VK_PRESENT_MODE_FIFO_KHR,
		fifo_relaxed = VK_PRESENT_MODE_FIFO_RELAXED_KHR,
		shared_demand_refresh = VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
		shared_continuous_refresh = VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR,
		fifo_latest_ready = VK_PRESENT_MODE_FIFO_LATEST_READY_KHR,
	};

	struct CreateInfo
	{
		Format format;

		ColorSpace color_space;

		math::uvec2 extent;

		u32 min_image_count;

		std::vector<uint32_t> queue_family_indices;

		VkCompositeAlphaFlagBitsKHR compositeAlpha;

		PresentMode present_mode;

		Surface::Transform pre_transform;

		std::string_view name;
	};

	Swapchain() = default;

	Swapchain(Device &device, Surface &surface, CreateInfo info);

	Swapchain(Swapchain &&) = default;

	Swapchain(const Swapchain &) = delete;

	auto operator=(Swapchain &&) -> Swapchain & = default;

	auto operator=(const Swapchain &) -> Swapchain & = delete;

	~Swapchain();

	[[nodiscard]] auto get_images() -> std::vector<Image>;

	[[nodiscard]] auto acquire_image(Semaphore &semaphore, u64 timeout = 100'000'000) -> u32;

private:
	[[nodiscard]] auto get_vk_handle() -> VkSwapchainKHR
	{
		return m_swapchain;
	}

	[[nodiscard]] auto get_addressof_vk_handle() -> VkSwapchainKHR *
	{
		return &m_swapchain;
	}

	memory::NullOnMove<VkDevice> m_device;

	VkSwapchainKHR m_swapchain;
};

class Queue
{
public:
	friend class Device;

	constexpr static auto object_type = VK_OBJECT_TYPE_QUEUE;

	struct SubmitInfo
	{
		CommandBuffer *command_buffer;

		PipelineStageFlags::T wait_stages;

		Semaphore *wait_semaphore;

		Semaphore *signal_semaphore;

		Fence *signal_fence;
	};

	struct PresentInfo
	{
		Semaphore *wait_semaphore;

		Swapchain *swapchain;

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

class Memory
{
public:
	friend class Device;

	static constexpr auto object_type = VK_OBJECT_TYPE_DEVICE_MEMORY;

	enum PropertyFlags : VkFlags
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

	struct AllocateInfo
	{
		size_t size;

		u32 memory_type_idx;

		std::string_view name;
	};

	Memory(Device &device, Buffer &buffer, AllocateInfo info);

	~Memory();

	Memory(Memory &&) = default;

	Memory(const Memory &) = delete;

	auto operator=(Memory &&) -> Memory & = default;

	auto operator=(const Memory &) -> Memory & = delete;

	[[nodiscard]] auto map(size_t size, size_t offset) -> std::span<byte>;

	void unmap();

private:
	[[nodiscard]] auto get_vk_handle() -> VkDeviceMemory
	{
		return m_memory;
	}

	memory::NullOnMove<VkDevice> m_device {};

	VkDeviceMemory m_memory {};
};

class Messenger
{
public:
	enum SeverityFlagBits : std::underlying_type_t<VkDebugUtilsMessageSeverityFlagBitsEXT>
	{
		verbose = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
		info = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
		warning = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
		error = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
	};

	enum TypeFlagBits : std::underlying_type_t<VkDebugUtilsMessageTypeFlagBitsEXT>
	{
		general = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
		validation = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
		performance = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		binding = VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT,
	};

	struct MessageData
	{
		std::string message;
	};

	using Callback = std::function<void(Flags, Flags, MessageData, void *)>;

	struct CreateInfo
	{
		Callback user_callback;
		void *user_data;
		Flags enabled_types;
		Flags enabled_severities;
	};

	Messenger() = default;

	Messenger(Instance &instance, CreateInfo info);

	~Messenger();

	Messenger(Messenger &&) = default;

	Messenger(const Messenger &) = delete;

	auto operator=(Messenger &&) -> Messenger & = default;

	auto operator=(const Messenger &) -> Messenger & = delete;

private:
	memory::NullOnMove<VkInstance> m_instance {};

	Callback m_user_callback;

	void *m_user_data {};

	VkDebugUtilsMessengerEXT m_messenger {};
};

} // namespace lt::renderer::vk


/** ================================ **/
/** Private Template Implementations **/
/** ================================ **/
namespace lt::renderer::vk {

// This is the only api function that needs to be inside the "header" part of the module,
// since it's used in a template that does std::format magic.
//
// ...And the template implementation needs to be visible by the compiler on the calling site to
// generate the templated code
namespace api {
PFN_vkSetDebugUtilsObjectNameEXT set_debug_object_name {}; // NOLINT
}

constexpr auto to_string(VkResult result) noexcept -> std::string_view
{
	switch (result)
	{
		// clang-format off
	case VK_SUCCESS: return "VK_SUCCESS";
	case VK_NOT_READY: return "VK_NOT_READY";
	case VK_TIMEOUT: return "VK_TIMEOUT";
	case VK_EVENT_SET: return "VK_EVENT_SET";
	case VK_EVENT_RESET: return "VK_EVENT_RESET";
	case VK_INCOMPLETE: return "VK_INCOMPLETE";
	case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
	case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
	case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
	case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
	case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
	case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
	case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
	case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
	case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
	case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
	case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
	case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL";
	case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN";
	case VK_ERROR_VALIDATION_FAILED: return "VK_ERROR_VALIDATION_FAILED";
	case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY";
	case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
	case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
	case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION";
	case VK_PIPELINE_COMPILE_REQUIRED: return "VK_PIPELINE_COMPILE_REQUIRED";
	case VK_ERROR_NOT_PERMITTED: return "VK_ERROR_NOT_PERMITTED";
	case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
	case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
	case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
	case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
	case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR: return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
	case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
	case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
	case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
	case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
	case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
	case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
	case VK_ERROR_PRESENT_TIMING_QUEUE_FULL_EXT: return "VK_ERROR_PRESENT_TIMING_QUEUE_FULL_EXT";
	case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
	case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR";
	case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR";
	case VK_OPERATION_DEFERRED_KHR: return "VK_OPERATION_DEFERRED_KHR";
	case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR";
	case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR: return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
	case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
	case VK_INCOMPATIBLE_SHADER_BINARY_EXT: return "VK_INCOMPATIBLE_SHADER_BINARY_EXT";
	case VK_PIPELINE_BINARY_MISSING_KHR: return "VK_PIPELINE_BINARY_MISSING_KHR";
	case VK_ERROR_NOT_ENOUGH_SPACE_KHR: return "VK_ERROR_NOT_ENOUGH_SPACE_KHR";
    case VK_RESULT_MAX_ENUM: return "VK_RESULT_MAX_ENUM";
    default: return "<unknown>";
		// clang-format on
	}
}

void vkc(VkResult result)
{
	if (result)
	{
		log::error("Checked vulkan call failed with result: {}", to_string(result));
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

	vkc(api::set_debug_object_name(m_device, &info));
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

	vkc(api::set_debug_object_name(m_device, &info));
}

} // namespace lt::renderer::vk


module :private;
namespace lt::renderer::vk {

namespace api {
// global functions
PFN_vkGetInstanceProcAddr get_instance_proc_address {};
PFN_vkCreateInstance create_instance {};
PFN_vkEnumerateInstanceExtensionProperties enumerate_instance_extension_properties {};
PFN_vkEnumerateInstanceLayerProperties enumerate_instance_layer_properties {};

// instance functions
PFN_vkDestroyInstance destroy_instance {};
PFN_vkEnumeratePhysicalDevices enumerate_physical_devices {};

PFN_vkGetPhysicalDeviceProperties get_physical_device_properties {};
PFN_vkGetPhysicalDeviceQueueFamilyProperties get_physical_device_queue_family_properties {};
PFN_vkCreateDevice create_device {};
PFN_vkGetDeviceProcAddr get_device_proc_address {};
PFN_vkDestroyDevice destroy_device {};
PFN_vkGetPhysicalDeviceFeatures2 get_physical_device_features {};
PFN_vkEnumerateDeviceExtensionProperties enumerate_device_extension_properties {};
PFN_vkGetPhysicalDeviceMemoryProperties get_physical_device_memory_properties {};

// extension instance functions
PFN_vkCmdBeginDebugUtilsLabelEXT cmd_begin_debug_label {};
PFN_vkCmdEndDebugUtilsLabelEXT cmd_end_debug_label {};
PFN_vkCmdInsertDebugUtilsLabelEXT cmd_insert_debug_label {};
PFN_vkCreateDebugUtilsMessengerEXT create_debug_messenger {};
PFN_vkDestroyDebugUtilsMessengerEXT destroy_debug_messenger {};
PFN_vkQueueBeginDebugUtilsLabelEXT queue_begin_debug_label {};
PFN_vkQueueEndDebugUtilsLabelEXT queue_end_debug_label {};
PFN_vkQueueInsertDebugUtilsLabelEXT queue_insert_debug_label {};
PFN_vkSetDebugUtilsObjectTagEXT set_debug_object_tag {};
PFN_vkSubmitDebugUtilsMessageEXT submit_debug_message {};

// surface instance functions
PFN_vkGetPhysicalDeviceSurfaceSupportKHR get_physical_device_surface_support {};
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR get_physical_device_surface_capabilities {};
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR get_physical_device_surface_formats {};

// device functions
PFN_vkGetDeviceQueue get_device_queue {};
PFN_vkCreateCommandPool create_command_pool {};
PFN_vkDestroyCommandPool destroy_command_pool {};
PFN_vkAllocateCommandBuffers allocate_command_buffers {};
PFN_vkFreeCommandBuffers free_command_buffers {};
PFN_vkBeginCommandBuffer begin_command_buffer {};
PFN_vkEndCommandBuffer end_command_buffer {};
PFN_vkCmdPipelineBarrier cmd_pipeline_barrier {};
PFN_vkQueueSubmit queue_submit {};
PFN_vkQueueWaitIdle queue_wait_idle {};
PFN_vkDeviceWaitIdle device_wait_idle {};
PFN_vkCreateFence create_fence {};
PFN_vkDestroyFence destroy_fence {};
PFN_vkWaitForFences wait_for_fences {};
PFN_vkResetFences reset_fences {};
PFN_vkCreateSemaphore create_semaphore {};
PFN_vkDestroySemaphore destroy_semaphore {};
PFN_vkCreateSwapchainKHR create_swapchain_khr {};
PFN_vkDestroySwapchainKHR destroy_swapchain_khr {};
PFN_vkGetSwapchainImagesKHR get_swapchain_images_khr {};
PFN_vkAcquireNextImageKHR acquire_next_image_khr {};
PFN_vkQueuePresentKHR queue_present_khr {};
PFN_vkCreateImage create_image {};
PFN_vkDestroyImage destroy_image {};
PFN_vkCreateImageView create_image_view {};
PFN_vkDestroyImageView destroy_image_view {};
PFN_vkCreateRenderPass create_render_pass {};
PFN_vkDestroyRenderPass destroy_render_pass {};
PFN_vkCreateFramebuffer create_frame_buffer {};
PFN_vkDestroyFramebuffer destroy_frame_buffer {};
PFN_vkCreateShaderModule create_shader_module {};
PFN_vkDestroyShaderModule destroy_shader_module {};
PFN_vkCreatePipelineLayout create_pipeline_layout {};
PFN_vkDestroyPipelineLayout destroy_pipeline_layout {};
PFN_vkCreateGraphicsPipelines create_graphics_pipelines {};
PFN_vkDestroyPipeline destroy_pipeline {};
PFN_vkCmdBeginRenderPass cmd_begin_render_pass {};
PFN_vkCmdEndRenderPass cmd_end_render_pass {};
PFN_vkCmdBindPipeline cmd_bind_pipeline {};
PFN_vkCmdBindDescriptorSets cmd_bind_descriptor_sets {};
PFN_vkCmdDraw cmd_draw {};
PFN_vkCmdSetViewport cmd_set_viewport {};
PFN_vkCmdSetScissor cmd_set_scissors {};
PFN_vkCmdPushConstants cmd_push_constants {};
PFN_vkCmdCopyBuffer cmd_copy_buffer {};

PFN_vkCreateDescriptorSetLayout create_descriptor_set_layout {};
PFN_vkDestroyDescriptorSetLayout destroy_descriptor_set_layout {};
PFN_vkCreateDescriptorPool create_descriptor_pool {};
PFN_vkDestroyDescriptorPool destroy_descriptor_pool {};
PFN_vkAllocateDescriptorSets allocate_descriptor_sets {};
PFN_vkFreeDescriptorSets free_descriptor_sets {};

PFN_vkCreateBuffer create_buffer {};
PFN_vkDestroyBuffer destroy_buffer {};
PFN_vkGetBufferMemoryRequirements get_buffer_memory_requirements {};
PFN_vkAllocateMemory allocate_memory {};
PFN_vkBindBufferMemory bind_buffer_memory {};
PFN_vkMapMemory map_memory {};
PFN_vkUnmapMemory unmap_memory {};
PFN_vkFreeMemory free_memory {};

PFN_vkResetCommandBuffer reset_command_buffer {};

PFN_vkCmdBeginRendering cmd_begin_rendering {};
PFN_vkCmdEndRendering cmd_end_rendering {};

#if defined(LIGHT_PLATFORM_LINUX)
PFN_vkCreateWaylandSurfaceKHR create_wayland_surface_khr {};
#elif defined(LIGHT_PLATFORM_WINDOWS)
PFN_vkCreateWin32SurfaceKHR create_win32_surface_khr {};
#else
	#error "Unsupported platform"
#endif

PFN_vkDestroySurfaceKHR destroy_surface_khr {};
} // namespace api

void *library = nullptr; // NOLINT

void load_library()
{
#if defined(LIGHT_PLATFORM_LINUX)
	constexpr auto runtime_loader_flags = RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE;
	library = dlopen("libvulkan.so.1", runtime_loader_flags);
	if (!library)
	{
		library = dlopen("libvulkan.so", runtime_loader_flags);
	}
	lt::debug::ensure(library, "Failed to dlopen the libvulkan.so");

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	api::get_instance_proc_address = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
	    dlsym(library, "vkGetInstanceProcAddr")
	);
	lt::debug::ensure(
	    api::get_instance_proc_address,
	    "Failed to load vulkan function: vkGetInstanceProcAddr"
	);
#elif defined(LIGHT_PLATFORM_WINDOWS)
	library = LoadLibraryA("vulkan-1.dll");
	lt::debug::ensure(library, "Failed to LoadLibraryA the vulkan-1.dll");

	api::get_instance_proc_address = std::bit_cast<PFN_vkGetInstanceProcAddr>(
	    GetProcAddress(std::bit_cast<HMODULE>(library), "vkGetInstanceProcAddr")
	);
	lt::debug::ensure(
	    api::get_instance_proc_address,
	    "Failed to get vkGetInstanceProcAddr function pointer from vulkan-1.dll"
	);

#else
	#error "Unsupported platform"
#endif
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
		pfn = std::bit_cast<T>(api::get_instance_proc_address(nullptr, fn_name));
		lt::debug::ensure(pfn, "Failed to load vulkan global function: {}", fn_name);
	};

	load_fn(api::create_instance, "vkCreateInstance");
	load_fn(api::enumerate_instance_extension_properties, "vkEnumerateInstanceExtensionProperties");
	load_fn(api::enumerate_instance_layer_properties, "vkEnumerateInstanceLayerProperties");
}

void Instance::load_functions()
{
	const auto load_fn = [this]<typename T>(T &pfn, const char *fn_name) {
		pfn = std::bit_cast<T>(api::get_instance_proc_address(m_instance, fn_name));
		lt::debug::ensure(pfn, "Failed to load vulkan instance function: {}", fn_name);
	};

	load_fn(api::destroy_instance, "vkDestroyInstance");
	load_fn(api::enumerate_physical_devices, "vkEnumeratePhysicalDevices");
	load_fn(api::get_physical_device_properties, "vkGetPhysicalDeviceProperties");
	load_fn(
	    api::get_physical_device_queue_family_properties,
	    "vkGetPhysicalDeviceQueueFamilyProperties"
	);
	load_fn(api::create_device, "vkCreateDevice");
	load_fn(api::get_device_proc_address, "vkGetDeviceProcAddr");
	load_fn(api::destroy_device, "vkDestroyDevice");
	load_fn(api::get_physical_device_features, "vkGetPhysicalDeviceFeatures");
	load_fn(api::enumerate_device_extension_properties, "vkEnumerateDeviceExtensionProperties");
	load_fn(api::get_physical_device_memory_properties, "vkGetPhysicalDeviceMemoryProperties");

	load_fn(api::cmd_begin_debug_label, "vkCmdBeginDebugUtilsLabelEXT");
	load_fn(api::cmd_end_debug_label, "vkCmdEndDebugUtilsLabelEXT");
	load_fn(api::cmd_insert_debug_label, "vkCmdInsertDebugUtilsLabelEXT");
	load_fn(api::create_debug_messenger, "vkCreateDebugUtilsMessengerEXT");
	load_fn(api::destroy_debug_messenger, "vkDestroyDebugUtilsMessengerEXT");
	load_fn(api::queue_begin_debug_label, "vkQueueBeginDebugUtilsLabelEXT");
	load_fn(api::queue_end_debug_label, "vkQueueEndDebugUtilsLabelEXT");
	load_fn(api::queue_insert_debug_label, "vkQueueInsertDebugUtilsLabelEXT");
	load_fn(api::set_debug_object_name, "vkSetDebugUtilsObjectNameEXT");
	load_fn(api::set_debug_object_tag, "vkSetDebugUtilsObjectTagEXT");
	load_fn(api::submit_debug_message, "vkSubmitDebugUtilsMessageEXT");

	load_fn(api::get_physical_device_surface_support, "vkGetPhysicalDeviceSurfaceSupportKHR");
	load_fn(
	    api::get_physical_device_surface_capabilities,
	    "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"
	);
	load_fn(api::get_physical_device_surface_formats, "vkGetPhysicalDeviceSurfaceFormatsKHR");

#if defined(LIGHT_PLATFORM_LINUX)
	load_fn(api::create_wayland_surface_khr, "vkCreateWaylandSurfaceKHR");
#elif defined(LIGHT_PLATFORM_WINDOWS)
	load_fn(api::create_win32_surface_khr, "vkCreateWin32SurfaceKHR");
#else
	#error "Unsupported platform"
#endif
	load_fn(api::destroy_surface_khr, "vkDestroySurfaceKHR");
}

void Device::load_functions()
{
	const auto load_fn = [this]<typename T>(T &pfn, const char *fn_name) {
		pfn = std::bit_cast<T>(api::get_device_proc_address(m_device, fn_name));
		lt::debug::ensure(pfn, "Failed to load vulkan device function: {}", fn_name);
	};

	load_fn(api::get_device_queue, "vkGetDeviceQueue");
	load_fn(api::create_command_pool, "vkCreateCommandPool");
	load_fn(api::destroy_command_pool, "vkDestroyCommandPool");
	load_fn(api::allocate_command_buffers, "vkAllocateCommandBuffers");
	load_fn(api::free_command_buffers, "vkFreeCommandBuffers");
	load_fn(api::begin_command_buffer, "vkBeginCommandBuffer");
	load_fn(api::end_command_buffer, "vkEndCommandBuffer");
	load_fn(api::cmd_pipeline_barrier, "vkCmdPipelineBarrier");
	load_fn(api::queue_submit, "vkQueueSubmit");
	load_fn(api::queue_wait_idle, "vkQueueWaitIdle");
	load_fn(api::device_wait_idle, "vkDeviceWaitIdle");
	load_fn(api::create_fence, "vkCreateFence");
	load_fn(api::destroy_fence, "vkDestroyFence");
	load_fn(api::wait_for_fences, "vkWaitForFences");
	load_fn(api::reset_fences, "vkResetFences");
	load_fn(api::create_semaphore, "vkCreateSemaphore");
	load_fn(api::destroy_semaphore, "vkDestroySemaphore");
	load_fn(api::create_swapchain_khr, "vkCreateSwapchainKHR");
	load_fn(api::destroy_swapchain_khr, "vkDestroySwapchainKHR");
	load_fn(api::get_swapchain_images_khr, "vkGetSwapchainImagesKHR");
	load_fn(api::acquire_next_image_khr, "vkAcquireNextImageKHR");
	load_fn(api::queue_present_khr, "vkQueuePresentKHR");
	load_fn(api::create_image, "vkCreateImage");
	load_fn(api::destroy_image, "vkDestroyImage");
	load_fn(api::create_image_view, "vkCreateImageView");
	load_fn(api::destroy_image_view, "vkDestroyImageView");
	load_fn(api::create_render_pass, "vkCreateRenderPass");
	load_fn(api::destroy_render_pass, "vkDestroyRenderPass");
	load_fn(api::create_frame_buffer, "vkCreateFramebuffer");
	load_fn(api::destroy_frame_buffer, "vkDestroyFramebuffer");
	load_fn(api::create_shader_module, "vkCreateShaderModule");
	load_fn(api::destroy_shader_module, "vkDestroyShaderModule");
	load_fn(api::create_pipeline_layout, "vkCreatePipelineLayout");
	load_fn(api::destroy_pipeline_layout, "vkDestroyPipelineLayout");
	load_fn(api::create_graphics_pipelines, "vkCreateGraphicsPipelines");
	load_fn(api::destroy_pipeline, "vkDestroyPipeline");
	load_fn(api::cmd_begin_render_pass, "vkCmdBeginRenderPass");
	load_fn(api::cmd_end_render_pass, "vkCmdEndRenderPass");
	load_fn(api::cmd_bind_pipeline, "vkCmdBindPipeline");
	load_fn(api::cmd_bind_descriptor_sets, "vkCmdBindDescriptorSets");
	load_fn(api::cmd_draw, "vkCmdDraw");
	load_fn(api::cmd_set_viewport, "vkCmdSetViewport");
	load_fn(api::cmd_set_scissors, "vkCmdSetScissor");
	load_fn(api::cmd_push_constants, "vkCmdPushConstants");
	load_fn(api::cmd_copy_buffer, "vkCmdCopyBuffer");
	load_fn(api::create_descriptor_set_layout, "vkCreateDescriptorSetLayout");
	load_fn(api::destroy_descriptor_set_layout, "vkDestroyDescriptorSetLayout");
	load_fn(api::create_descriptor_pool, "vkCreateDescriptorPool");
	load_fn(api::destroy_descriptor_pool, "vkDestroyDescriptorPool");
	load_fn(api::allocate_descriptor_sets, "vkAllocateDescriptorSets");
	load_fn(api::free_descriptor_sets, "vkFreeDescriptorSets");
	load_fn(api::create_buffer, "vkCreateBuffer");
	load_fn(api::destroy_buffer, "vkDestroyBuffer");
	load_fn(api::allocate_memory, "vkAllocateMemory");
	load_fn(api::bind_buffer_memory, "vkBindBufferMemory");
	load_fn(api::map_memory, "vkMapMemory");
	load_fn(api::unmap_memory, "vkUnmapMemory");
	load_fn(api::free_memory, "vkFreeMemory");
	load_fn(api::get_buffer_memory_requirements, "vkGetBufferMemoryRequirements");
	load_fn(api::reset_command_buffer, "vkResetCommandBuffer");

	load_fn(api::cmd_begin_rendering, "vkCmdBeginRendering");
	load_fn(api::cmd_end_rendering, "vkCmdEndRendering");
}

Instance::Instance(CreateInfo info)
{
	const auto layer_setting_type_visitor = overloads {
		[](const std::vector<const char *> &) { return VK_LAYER_SETTING_TYPE_STRING_EXT; },
		[](u32) { return VK_LAYER_SETTING_TYPE_UINT32_EXT; },
		[](bool) { return VK_LAYER_SETTING_TYPE_BOOL32_EXT; },
	};

	const auto layer_setting_value_visitor = overloads {
		[](std::vector<const char *> values) { return std::bit_cast<void *>(values.data()); },
		[](u32 value) { return std::bit_cast<void *>(&value); },
		[](bool value) { return std::bit_cast<void *>(&value); },
	};

	auto layer_settings = std::vector<VkLayerSettingEXT> {};
	auto layer_names = std::vector<const char *> {};
	auto extension_names = std::vector<const char *> {};
	for (auto &extension : info.extensions)
	{
		extension_names.emplace_back(extension.c_str());
	}

	for (const auto &layer : info.layers)
	{
		layer_names.emplace_back(layer.name.c_str());
		for (const auto &setting : layer.settings)
		{
			const auto *values = static_cast<void *>(nullptr);

			if (setting.values.index() == 0)
			{
				values = std::bit_cast<const void *>(std::get<0>(setting.values).data());
			}
			else if (setting.values.index() == 1)
			{
				values = std::bit_cast<const void *>(&std::get<1>(setting.values));
			}
			else if (setting.values.index() == 2)
			{
				values = std::bit_cast<const void *>(&std::get<2>(setting.values));
			}

			debug::ensure(values, "Failed to get variant from setting.values");

			layer_settings.emplace_back(
			    VkLayerSettingEXT {
			        .pLayerName = layer.name.c_str(),
			        .pSettingName = setting.name.c_str(),
			        .type = std::visit(layer_setting_type_visitor, setting.values),
			        .valueCount = 1u,
			        .pValues = values,
			    }
			);
		}
	}

	const auto layer_settings_create_info = VkLayerSettingsCreateInfoEXT {
		.sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
		.settingCount = static_cast<uint32_t>(layer_settings.size()),
		.pSettings = layer_settings.data(),
	};

	auto app_info = VkApplicationInfo {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = constants::engine_name,
		.applicationVersion = constants::application_version,
		.pEngineName = constants::app_name,
		.apiVersion = constants::api_version,
	};

	auto vk_info = VkInstanceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = &layer_settings_create_info,
		.flags = {},
		.pApplicationInfo = &app_info,
		.enabledLayerCount = static_cast<uint32_t>(info.layers.size()),
		.ppEnabledLayerNames = layer_names.data(),
		.enabledExtensionCount = static_cast<uint32_t>(extension_names.size()),
		.ppEnabledExtensionNames = extension_names.data(),
	};

	vkc(api::create_instance(&vk_info, nullptr, &m_instance));
	debug::ensure(m_instance, "Failed to create vulkan instance");
}

Surface::Surface(const Instance &instance, const CreateInfo &info)
    : m_instance(instance.m_instance.get())
{
#if defined(LIGHT_PLATFORM_LINUX)
	const auto vk_info = VkWaylandSurfaceCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
		.pNext = {},
		.flags = {},
		.display = info.display,
		.surface = info.surface,
	};

	vkc(api::create_wayland_surface_khr(instance.get_vk_handle(), &vk_info, nullptr, &m_surface));
#elif defined(LIGHT_PLATFORM_WINDOWS)

	const auto vk_info = VkWin32SurfaceCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		.pNext = {},
		.flags = {},
		.hinstance = GetModuleHandle(nullptr),
		.hwnd = info.window,
	};

	vkc(api::create_win32_surface_khr(instance.get_vk_handle(), &vk_info, nullptr, &m_surface));
#else
	#error "Unsupported platform"

#endif
}

Surface::~Surface()
{
	if (m_instance)
	{
		api::destroy_surface_khr(m_instance, m_surface, nullptr);
	}
}

[[nodiscard]]
/* static */ auto Gpu::enumerate(const Instance &instance) -> std::vector<Gpu>
{
	auto count = 0u;
	vkc(api::enumerate_physical_devices(instance.m_instance, &count, nullptr));
	debug::ensure(count != 0u, "Failed to find any gpus with Vulkan support");

	auto vk_gpus = std::vector<VkPhysicalDevice>(count);
	vkc(api::enumerate_physical_devices(instance.m_instance, &count, vk_gpus.data()));

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
	api::get_physical_device_features(m_physical_device, &features_2);
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

	api::get_physical_device_features(m_physical_device, &features_2);
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

	api::get_physical_device_features(m_physical_device, &features_2);
	return DescriptorIndexingFeatures {
		// clang-format off
		.shader_input_attachment_array_dynamic_indexing = false,
		.shader_uniform_texel_buffer_array_dynamic_indexing = true,
		.shader_storage_texel_buffer_array_dynamic_indexing = true,
		.shader_uniform_buffer_array_non_uniform_indexing = true,
		.shader_sampled_image_array_non_uniform_indexing = true,
		.shader_storage_buffer_array_non_uniform_indexing = true,
		.shader_storage_image_array_non_uniform_indexing = true,
		.shader_input_attachment_array_non_uniform_indexing =false,
		.shader_uniform_texel_buffer_array_non_uniform_indexing = true,
		.shader_storage_texel_buffer_array_non_uniform_indexing = true,
		.descriptor_binding_uniform_buffer_update_after_bind = true,
		.descriptor_binding_sampled_image_update_after_bind = true,
		.descriptor_binding_storage_image_update_after_bind = true,
		.descriptor_binding_storage_buffer_update_after_bind = true,
		.descriptor_binding_uniform_texel_buffer_update_after_bind = true,
		.descriptor_binding_storage_texel_buffer_update_after_bind = true,
		.descriptor_binding_update_unused_while_pending = true,
		.descriptor_binding_partially_bound = true, 
        .descriptor_binding_variable_descriptor_count = true,
        .runtime_descriptor_array = true,
		// clang-format on
	};
}

[[nodiscard]] auto Gpu::get_properties() const -> Properties
{
	auto vk_properties = VkPhysicalDeviceProperties {};
	api::get_physical_device_properties(m_physical_device, &vk_properties);

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
	    static_cast<u8 *>(vk_properties.pipelineCacheUUID),
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
	api::get_physical_device_memory_properties(m_physical_device, &vk_memory_properties);

	auto memory_properties = MemoryProperties {};

	memory_properties.memory_heaps.resize(vk_memory_properties.memoryHeapCount);
	std::memcpy(
	    memory_properties.memory_heaps.data(),
	    static_cast<VkMemoryHeap *>(vk_memory_properties.memoryHeaps),
	    sizeof(VkMemoryHeap) * vk_memory_properties.memoryHeapCount
	);

	memory_properties.memory_types.resize(vk_memory_properties.memoryTypeCount);
	std::memcpy(
	    memory_properties.memory_types.data(),
	    static_cast<VkMemoryType *>(vk_memory_properties.memoryTypes),
	    sizeof(VkMemoryType) * vk_memory_properties.memoryTypeCount
	);

	return memory_properties;
}

[[nodiscard]] auto Gpu::get_queue_family_properties() const -> std::vector<QueueFamilyProperties>
{
	auto count = u32 {};

	api::get_physical_device_queue_family_properties(m_physical_device, &count, {});

	auto vk_properties = std::vector<VkQueueFamilyProperties>(count);
	api::get_physical_device_queue_family_properties(
	    m_physical_device,
	    &count,
	    vk_properties.data()
	);

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
    u32 queue_family_idx
) const -> bool
{
	auto supported = VkBool32 { false };
	vkc(api::get_physical_device_surface_support(
	    m_physical_device,
	    queue_family_idx,
	    surface.m_surface,
	    &supported
	));
	return supported;
}

[[nodiscard]] auto Gpu::get_surface_capabilities(Surface &surface) const -> Surface::Capabilities
{
	auto vk_capabilities = VkSurfaceCapabilitiesKHR {};
	vkc(api::get_physical_device_surface_capabilities(
	    m_physical_device,
	    surface.get_vk_handle(),
	    &vk_capabilities
	));

	return Surface::Capabilities {
        .min_image_count = vk_capabilities.minImageCount,
            .max_image_count = vk_capabilities.maxImageCount,

		.current_extent = { vk_capabilities.currentExtent.width,
		                    vk_capabilities.currentExtent.height, },
        .min_image_extent = {vk_capabilities.minImageExtent.width, vk_capabilities.minImageExtent.height,},
        .max_image_extent = {vk_capabilities.maxImageExtent.width, vk_capabilities.maxImageExtent.height},
		.supported_transforms = vk_capabilities.supportedTransforms,
		.current_transform = static_cast<Surface::Transform>(vk_capabilities.currentTransform),
		.supported_composite_alpha = static_cast<CompositeAlpha::T>(
		    vk_capabilities.supportedCompositeAlpha
		),
        .supported_usage_flags = vk_capabilities.supportedUsageFlags,
	};
}

[[nodiscard]] auto Gpu::get_surface_formats(Surface &surface) const -> std::vector<Surface::Format>
{
	auto count = uint32_t { 0u };
	vkc(api::get_physical_device_surface_formats(
	    m_physical_device,
	    surface.get_vk_handle(),
	    &count,
	    nullptr
	));

	auto vk_formats = std::vector<VkSurfaceFormatKHR>(count);
	vkc(api::get_physical_device_surface_formats(
	    m_physical_device,
	    surface.get_vk_handle(),
	    &count,
	    vk_formats.data()
	));

	auto formats = std::vector<Surface::Format> {};
	for (auto &vk_format : vk_formats)
	{
		formats.emplace_back(
		    Surface::Format {
		        .format = static_cast<Format>(vk_format.format),
		        .color_space = static_cast<ColorSpace>(vk_format.colorSpace),
		    }
		);
	}

	return formats;
}

Semaphore::Semaphore(Device &device): m_device(device.get_vk_handle())
{
	auto vk_info = VkSemaphoreCreateInfo {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};

	vkc(api::create_semaphore(m_device, &vk_info, nullptr, &m_semaphore));
}

Semaphore::~Semaphore()
{
	if (m_device)
	{
		api::destroy_semaphore(m_device, m_semaphore, nullptr);
	}
}

Fence::Fence(Device &device, CreateInfo info): m_device(device.get_vk_handle())
{
	auto vk_info = VkFenceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = info.signaled ? VK_FENCE_CREATE_SIGNALED_BIT : VkFlags {},
	};

	vkc(api::create_fence(m_device, &vk_info, nullptr, &m_fence));
}

Fence::~Fence()
{
	if (m_device)
	{
		api::destroy_fence(m_device, m_fence, nullptr);
	}
}

void Fence::wait()
{
	vkc(api::wait_for_fences(m_device, 1u, &m_fence, true, std::numeric_limits<uint64_t>::max()));
}

void Fence::reset()
{
	vkc(api::reset_fences(m_device, 1u, &m_fence));
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

	auto vk_extension_names = std::vector<const char *> {};
	for (const auto &extension : info.extensions)
	{
		vk_extension_names.emplace_back(extension.c_str());
	}

	const auto vk_physical_device_features = VkPhysicalDeviceFeatures {
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

	auto vk_physical_device_features2 = VkPhysicalDeviceFeatures2 {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
		.pNext = {},
		.features = vk_physical_device_features,
	};

	auto vk_info = VkDeviceCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &vk_physical_device_features2,
		.queueCreateInfoCount = static_cast<uint32_t>(vk_queue_infos.size()),
		.pQueueCreateInfos = vk_queue_infos.data(),
		.enabledExtensionCount = static_cast<uint32_t>(vk_extension_names.size()),
		.ppEnabledExtensionNames = vk_extension_names.data(),
		.pEnabledFeatures = {}, // replaced by vk_physical_device_features2
	};

	void **last_p_next = &vk_physical_device_features2.pNext;
	auto vk_descriptor_indexing_features = VkPhysicalDeviceDescriptorIndexingFeatures {};
	auto vk_dynamic_rendering_features = VkPhysicalDeviceDynamicRenderingFeatures {};

	if (info.dynamic_rendering_features)
	{
		vk_dynamic_rendering_features = VkPhysicalDeviceDynamicRenderingFeatures {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
			.pNext = {},
			.dynamicRendering = true,
		};

		*last_p_next = &vk_dynamic_rendering_features;
		last_p_next = &vk_dynamic_rendering_features.pNext;
	}

	if (info.descriptor_indexing_features)
	{
		const auto &features = *info.descriptor_indexing_features;
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

	vkc(api::create_device(gpu.m_physical_device, &vk_info, nullptr, &m_device));
}

Device::~Device()
{
	if (m_device)
	{
		api::destroy_device(m_device, nullptr);
	}
}

void Device::wait_idle() const
{
	vkc(api::device_wait_idle(m_device));
}

void Device::wait_for_fence(VkFence fence) const
{
	vkc(api::wait_for_fences(m_device, 1u, &fence, true, std::numeric_limits<uint64_t>::max()));
}

void Device::reset_fence(VkFence fence) const
{
	vkc(api::reset_fences(m_device, 1u, &fence));
}

void Device::reset_fences(std::span<VkFence> fences) const
{
	vkc(api::reset_fences(m_device, static_cast<uint32_t>(fences.size()), fences.data()));
}

auto Device::acquire_image(VkSwapchainKHR swapchain, VkSemaphore semaphore, uint64_t timeout)
    -> std::optional<uint32_t>
{
	auto image_idx = uint32_t {};
	const auto result = api::acquire_next_image_khr(
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
	vkc(api::wait_for_fences(
	    m_device,
	    static_cast<uint32_t>(fences.size()),
	    fences.data(),
	    true,
	    std::numeric_limits<uint64_t>::max()
	));
}

[[nodiscard]] auto Device::get_swapchain_images(VkSwapchainKHR swapchain) const
    -> std::vector<VkImage>
{
	auto count = uint32_t { 0u };
	vkc(api::get_swapchain_images_khr(m_device, swapchain, &count, nullptr));
	debug::ensure(count != 0u, "Failed to get swapchain images");

	auto images = std::vector<VkImage>(count);
	vkc(api::get_swapchain_images_khr(m_device, swapchain, &count, images.data()));
	return images;
}

[[nodiscard]] auto Device::get_memory_requirements(VkBuffer buffer) const -> VkMemoryRequirements
{
	auto requirements = VkMemoryRequirements {};
	api::get_buffer_memory_requirements(m_device, buffer, &requirements);
	return requirements;
}

void Device::bind_memory(VkBuffer buffer, VkDeviceMemory memory, size_t offset /* = 0u */) const
{
	vkc(api::bind_buffer_memory(m_device, buffer, memory, offset));
}

[[nodiscard]] auto Device::map_memory(VkDeviceMemory memory, size_t size, size_t offset) const
    -> std::span<byte>
{
	void *data = {};
	vkc(api::map_memory(m_device, memory, offset, size, {}, &data));
	return { std::bit_cast<byte *>(data), size };
}

void Device::unmap_memory(VkDeviceMemory memory)
{
	api::unmap_memory(m_device, memory);
}

[[nodiscard]] auto Device::create_swapchain(VkSwapchainCreateInfoKHR info) const -> VkSwapchainKHR
{
	auto *swapchain = VkSwapchainKHR {};
	vkc(api::create_swapchain_khr(m_device, &info, nullptr, &swapchain));
	return swapchain;
}

[[nodiscard]] auto Device::create_framebuffer(VkFramebufferCreateInfo info) const -> VkFramebuffer
{
	auto *framebuffer = VkFramebuffer {};
	vkc(api::create_frame_buffer(m_device, &info, nullptr, &framebuffer));
	return framebuffer;
}

[[nodiscard]] auto Device::create_image_view(VkImageViewCreateInfo info) const -> VkImageView
{
	auto *view = VkImageView {};
	vkc(api::create_image_view(m_device, &info, nullptr, &view));
	return view;
}

[[nodiscard]] auto Device::create_graphics_pipeline(VkGraphicsPipelineCreateInfo info) const
    -> VkPipeline
{
	auto *graphics_pipeline = VkPipeline {};
	vkc(api::create_graphics_pipelines(
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
	vkc(api::create_render_pass(m_device, &info, nullptr, &pass));
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
	vkc(api::create_pipeline_layout(m_device, &info, nullptr, &pipeline_layout));
	return pipeline_layout;
}

[[nodiscard]] auto Device::create_shader_module(VkShaderModuleCreateInfo info) const
    -> VkShaderModule
{
	auto *module = VkShaderModule {};
	vkc(api::create_shader_module(m_device, &info, nullptr, &module));
	return module;
}

[[nodiscard]] auto Device::create_command_pool(VkCommandPoolCreateInfo info) const -> VkCommandPool
{
	auto *command_pool = VkCommandPool {};
	vkc(api::create_command_pool(m_device, &info, nullptr, &command_pool));
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
		api::create_semaphore(m_device, &info, nullptr, &semaphore);
	}
	return semaphores;
}

[[nodiscard]] auto Device::create_fences(VkFenceCreateInfo info, uint32_t count) const
    -> std::vector<VkFence>
{
	auto fences = std::vector<VkFence>(count);
	for (auto &fence : fences)
	{
		api::create_fence(m_device, &info, nullptr, &fence);
	}
	return fences;
}

[[nodiscard]] auto Device::create_buffer(VkBufferCreateInfo info) const -> VkBuffer
{
	auto *buffer = VkBuffer {};
	vkc(api::create_buffer(m_device, &info, nullptr, &buffer));
	return buffer;
}
[[nodiscard]] auto Device::create_desscriptor_pool(VkDescriptorPoolCreateInfo info) const
    -> VkDescriptorPool
{
	auto *pool = VkDescriptorPool {};
	vkc(api::create_descriptor_pool(m_device, &info, nullptr, &pool));
	return pool;
}

[[nodiscard]] auto Device::create_descriptor_set_layout(VkDescriptorSetLayoutCreateInfo info) const
    -> VkDescriptorSetLayout
{
	auto *layout = VkDescriptorSetLayout {};
	vkc(api::create_descriptor_set_layout(m_device, &info, nullptr, &layout));
	return layout;
}

[[nodiscard]] auto Device::allocate_command_buffers(VkCommandBufferAllocateInfo info) const
    -> std::vector<VkCommandBuffer>
{
	auto command_buffers = std::vector<VkCommandBuffer>(info.commandBufferCount);
	vkc(api::allocate_command_buffers(m_device, &info, command_buffers.data()));
	return command_buffers;
}

[[nodiscard]] auto Device::allocate_memory(VkMemoryAllocateInfo info) const -> VkDeviceMemory
{
	auto *memory = VkDeviceMemory {};
	vkc(api::allocate_memory(m_device, &info, nullptr, &memory));
	return memory;
}

[[nodiscard]] auto Device::allocate_descriptor_set(VkDescriptorSetAllocateInfo info) const
    -> VkDescriptorSet
{
	auto *descriptor_set = VkDescriptorSet {};
	vkc(api::allocate_descriptor_sets(m_device, &info, &descriptor_set));
	return descriptor_set;
}

void Device::free_memory(VkDeviceMemory memory) const
{
	api::free_memory(m_device, memory, nullptr);
}

void Device::free_descriptor_set(
    VkDescriptorPool descriptor_pool,
    VkDescriptorSet descriptor_set
) const
{
	vkc(api::free_descriptor_sets(m_device, descriptor_pool, 1, &descriptor_set));
}

void Device::destroy_swapchain(VkSwapchainKHR swapchain) const
{
	api::destroy_swapchain_khr(m_device, swapchain, nullptr);
}

void Device::destroy_framebuffer(VkFramebuffer framebuffer) const
{
	api::destroy_frame_buffer(m_device, framebuffer, nullptr);
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
	api::destroy_image_view(m_device, image_view, nullptr);
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
	api::destroy_pipeline(m_device, pipeline, nullptr);
}

void Device::destroy_pass(VkRenderPass pass) const
{
	api::destroy_render_pass(m_device, pass, nullptr);
}

void Device::destroy_pipeline_layout(VkPipelineLayout pipeline_layout) const
{
	api::destroy_pipeline_layout(m_device, pipeline_layout, nullptr);
}

void Device::destroy_shader_module(VkShaderModule shader_module) const
{
	api::destroy_shader_module(m_device, shader_module, nullptr);
}

void Device::destroy_command_pool(VkCommandPool command_pool) const
{
	api::destroy_command_pool(m_device, command_pool, nullptr);
}

void Device::destroy_semaphore(VkSemaphore semaphore) const
{
	api::destroy_semaphore(m_device, semaphore, nullptr);
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
	api::destroy_fence(m_device, fence, nullptr);
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
	api::destroy_buffer(m_device, buffer, nullptr);
}

void Device::destroy_descriptor_set_layout(VkDescriptorSetLayout layout) const
{
	api::destroy_descriptor_set_layout(m_device, layout, nullptr);
}

void Device::destroy_descriptor_pool(VkDescriptorPool pool) const
{
	api::destroy_descriptor_pool(m_device, pool, nullptr);
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
	api::get_device_queue(m_device, queue_family_idx, queue_idx, &m_queue);
}

Queue::~Queue()
{
}

void Queue::submit(SubmitInfo info) const
{
	const auto vk_info = VkSubmitInfo {

		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1u,
		.pWaitSemaphores = info.wait_semaphore->get_addressof_vk_handle(),
		.pWaitDstStageMask = addressof_underlying(info.wait_stages),

		.commandBufferCount = 1u,
		.pCommandBuffers = info.command_buffer->get_addressof_vk_handle(),
		.signalSemaphoreCount = 1u,
		.pSignalSemaphores = info.signal_semaphore->get_addressof_vk_handle(),
	};

	vkc(api::queue_submit(m_queue, 1u, &vk_info, info.signal_fence->get_vk_handle()));
}

void Queue::present(PresentInfo info) const
{
	auto result = VkResult {};

	const auto vk_info = VkPresentInfoKHR {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1u,
		.pWaitSemaphores = info.wait_semaphore->get_addressof_vk_handle(),
		.swapchainCount = 1u,
		.pSwapchains = info.swapchain->get_addressof_vk_handle(),
		.pImageIndices = &info.image_idx,
		.pResults = &result,
	};

	vkc(api::queue_present_khr(m_queue, &vk_info));
	vkc(result);
}

Image::Image(Device &device, CreateInfo info): m_device(device.get_vk_handle()), m_image()
{
	// WIP(Light): use image create info's info

	ignore = info;
	auto vk_info = VkImageCreateInfo {};
	vkc(api::create_image(m_device, &vk_info, nullptr, &m_image));
}

Image::Image(VkImage image) noexcept: m_device(), m_image(image)
{
}

Image::~Image()
{
	if (m_device)
	{
		api::destroy_image(m_device, m_image, nullptr);
	}
}

ImageView::ImageView(Device &device, Image &image, CreateInfo info)
    : m_device(device.get_vk_handle())
    , m_image_view()
{
	auto vk_info = VkImageViewCreateInfo {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = {},
		.image = image.get_vk_handle(),
		.viewType = static_cast<VkImageViewType>(info.type),
		.format = static_cast<VkFormat>(info.format),
		.components = VkComponentMapping{
            .r = static_cast<VkComponentSwizzle>(info.components[0]),
            .g = static_cast<VkComponentSwizzle>(info.components[1]),
            .b = static_cast<VkComponentSwizzle>(info.components[2]),
            .a = static_cast<VkComponentSwizzle>(info.components[3]),
        },
		.subresourceRange = {
            .aspectMask = static_cast<VkImageAspectFlags>(info.range.aspect_flags),
            .baseMipLevel = info.range.base_mip_level,
            .levelCount = info.range.level_count,
            .baseArrayLayer = info.range.base_array_layer,
            .layerCount = info.range.layer_count,
        },
	};
	vkc(api::create_image_view(m_device, &vk_info, nullptr, &m_image_view));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

ImageView::~ImageView()
{
	if (m_device)
	{
		api::destroy_image_view(m_device, m_image_view, nullptr);
	}
}

CommandBuffer::CommandBuffer(VkCommandBuffer buffer): m_buffer(buffer)
{
}

void CommandBuffer::begin(BeginInfo info /* = {} */)
{
	// WIP(Light): Use info
	ignore = info;

	auto vk_info = VkCommandBufferBeginInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = {},
		.flags = {},
		.pInheritanceInfo = {},
	};

	vkc(api::begin_command_buffer(m_buffer, &vk_info));
}

void CommandBuffer::end()
{
	vkc(api::end_command_buffer(m_buffer));
}

void CommandBuffer::copy(BufferCopyInfo info)
{
	auto vk_copy_region = VkBufferCopy {
		.srcOffset = info.src_offset,
		.dstOffset = info.dst_offset,
		.size = info.size,
	};

	api::cmd_copy_buffer(
	    m_buffer,
	    info.src_buffer->get_vk_handle(),
	    info.dst_buffer->get_vk_handle(),
	    1u,
	    &vk_copy_region
	);
}

void CommandBuffer::push_constants(PushConstantsInfo info)
{
	api::cmd_push_constants(
	    m_buffer,
	    info.layout->get_vk_handle(),
	    info.shader_stages,
	    info.offset,
	    info.size,
	    info.data
	);
}

void CommandBuffer::image_barrier(ImageBarrierInfo info)
{
	auto vk_barrier = VkImageMemoryBarrier {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.pNext = {},
		.srcAccessMask = info.src_accesses,
		.dstAccessMask = info.dst_accesses,
		.oldLayout = static_cast<VkImageLayout>(info.src_layout),
		.newLayout = static_cast<VkImageLayout>(info.dst_layout),
		.srcQueueFamilyIndex = {},
		.dstQueueFamilyIndex = {},
		.image = info.image->get_vk_handle(),
		.subresourceRange = {
            .aspectMask = info.range.aspect_flags,
            .baseMipLevel = info.range.base_mip_level,
            .levelCount = info.range.level_count,
            .baseArrayLayer = info.range.base_array_layer,
            .layerCount = info.range.layer_count,
        },
	};

	api::cmd_pipeline_barrier(
	    m_buffer,
	    info.src_stages,
	    info.dst_stages,
	    {},
	    {},
	    {},
	    {},
	    {},
	    1u,
	    &vk_barrier
	);
}

void CommandBuffer::begin_rendering(RenderingInfo info)
{
	auto vk_color_attachments = std::vector<VkRenderingAttachmentInfo> {};
	for (auto attachment : info.color_attachments)
	{
		vk_color_attachments.emplace_back(
		    VkRenderingAttachmentInfo {
		        .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		        .pNext = {},
		        .imageView = attachment.view->get_vk_handle(),
		        .imageLayout = static_cast<VkImageLayout>(attachment.layout),
		        .resolveMode = static_cast<VkResolveModeFlagBits>(attachment.resolve_mode_flags),
		        .loadOp = static_cast<VkAttachmentLoadOp>(attachment.load_operation),
		        .storeOp = static_cast<VkAttachmentStoreOp>(attachment.store_operation),
		        .clearValue = { .color { .float32 = { attachment.color_clear_values[0], attachment.color_clear_values[1], attachment.color_clear_values[2], attachment.color_clear_values[3], } } },
		    }
		);
	}

	auto vk_info = VkRenderingInfo
	{
		.sType = VK_STRUCTURE_TYPE_RENDERING_INFO, .pNext = {}, .flags = {},
		.renderArea = {
			.offset = {info.area_offset.x, info.area_offset.y},
			.extent = {info.area_extent.x, info.area_extent.y},
		},
        .layerCount = 1u,
        .colorAttachmentCount = static_cast<u32>(vk_color_attachments.size()),
        .pColorAttachments= vk_color_attachments.data(),
    };

	api::cmd_begin_rendering(m_buffer, &vk_info);
}

void CommandBuffer::end_rendering()
{
	api::cmd_end_rendering(m_buffer);
}

void CommandBuffer::bind_pipeline(Pipeline &pipeline, Pipeline::BindPoint bind_point)
{
	api::cmd_bind_pipeline(
	    m_buffer,
	    static_cast<VkPipelineBindPoint>(bind_point),
	    pipeline.get_vk_handle()
	);
}

void CommandBuffer::bind_descriptor_set(
    DescriptorSet &set,
    Pipeline::BindPoint bind_point,
    PipelineLayout &layout,
    uint32_t idx
)
{
	api::cmd_bind_descriptor_sets(
	    m_buffer,
	    static_cast<VkPipelineBindPoint>(bind_point),
	    layout.get_vk_handle(),
	    idx,
	    1u,
	    set.get_vk_handle_addr(),
	    0u,
	    {}
	);
}

void CommandBuffer::draw(DrawInfo info)
{
	api::cmd_draw(
	    m_buffer,
	    info.vertex_count,
	    info.instance_count,
	    info.first_vertex,
	    info.first_instance
	);
}

void CommandBuffer::set_viewport(Viewport viewport)
{
	auto vk_viewport = VkViewport {
		.x = viewport.origin.x,
		.y = viewport.origin.y,
		.width = viewport.extent.x,
		.height = viewport.extent.y,
		.minDepth = viewport.min_depth,
		.maxDepth = viewport.max_depth,
	};
	api::cmd_set_viewport(m_buffer, 0u, 1u, &vk_viewport);
}

void CommandBuffer::set_scissor(Rect2d scissor)
{
	auto vk_scissor = VkRect2D {
		.offset = { .x = scissor.offset.x, .y = scissor.offset.y },
		.extent = { .width = scissor.extent.x, .height = scissor.extent.y },
	};
	api::cmd_set_scissors(m_buffer, 0u, 1u, &vk_scissor);
}

CommandPool::CommandPool(Device &device, CreateInfo info): m_device(device.get_vk_handle())
{
	auto vk_info = VkCommandPoolCreateInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = {},
		.flags = info.flags,
		.queueFamilyIndex = {},
	};

	vkc(api::create_command_pool(m_device, &vk_info, nullptr, &m_pool));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

CommandPool::~CommandPool()
{
	if (m_device)
	{
		api::destroy_command_pool(m_device, m_pool, nullptr);
	}
}

[[nodiscard]] auto CommandPool::allocate(uint32_t count, BufferLevel level)
    -> std::vector<CommandBuffer>
{
	auto vk_buffers = std::vector<VkCommandBuffer>(count);

	auto vk_info = VkCommandBufferAllocateInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = {},
		.commandPool = m_pool,
		.level = static_cast<VkCommandBufferLevel>(level),
		.commandBufferCount = count,
	};

	vkc(api::allocate_command_buffers(m_device, &vk_info, vk_buffers.data()));

	auto buffers = std::vector<CommandBuffer>();
	buffers.reserve(vk_buffers.size());
	for (auto &vk_buffer : vk_buffers)
	{
		buffers.emplace_back(CommandBuffer { vk_buffer });
	}

	return buffers;
}

Swapchain::Swapchain(Device &device, Surface &surface, CreateInfo info)
    : m_device(device.m_device.get())
    , m_swapchain()
{
	auto vk_info = VkSwapchainCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface.m_surface,
		.minImageCount = info.min_image_count,
		.imageFormat = static_cast<VkFormat>(info.format),
		.imageColorSpace = static_cast<VkColorSpaceKHR>(info.color_space),
		.imageExtent = VkExtent2D { .width = info.extent.x, .height = info.extent.y },
		.imageArrayLayers = 1u,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = static_cast<u32>(info.queue_family_indices.size()),
		.pQueueFamilyIndices = info.queue_family_indices.data(),
		.preTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(info.pre_transform),
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = static_cast<VkPresentModeKHR>(info.present_mode),
		.clipped = VK_TRUE,
		.oldSwapchain = nullptr,
	};
	vkc(api::create_swapchain_khr(m_device, &vk_info, nullptr, &m_swapchain));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

Swapchain::~Swapchain()
{
	if (m_device)
	{
		api::destroy_swapchain_khr(m_device, m_swapchain, nullptr);
	}
}

[[nodiscard]] auto Swapchain::get_images() -> std::vector<Image>
{
	auto count = 0u;
	api::get_swapchain_images_khr(m_device, m_swapchain, &count, nullptr);

	auto vk_images = std::vector<VkImage>(count);
	api::get_swapchain_images_khr(m_device, m_swapchain, &count, vk_images.data());

	auto images = std::vector<Image>();
	for (auto vk_image : vk_images)
	{
		images.emplace_back(Image { vk_image });
	}

	return images;
}

[[nodiscard]] auto Swapchain::acquire_image(Semaphore &semaphore, u64 timeout) -> u32
{
	auto idx = u32 {};
	vkc(api::acquire_next_image_khr(
	    m_device,
	    m_swapchain,
	    timeout,
	    semaphore.get_vk_handle(),
	    VK_NULL_HANDLE,
	    &idx
	));

	return idx;
}

Buffer::Buffer(Device &device, CreateInfo info): m_device(device.m_device.get())
{
	auto vk_info = VkBufferCreateInfo {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = info.size,
		.usage = info.usage,
		.sharingMode = static_cast<VkSharingMode>(info.sharing_mode),
	};

	vkc(api::create_buffer(m_device, &vk_info, nullptr, &m_buffer));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
};

Buffer::~Buffer()
{
	if (m_device)
	{
		api::destroy_buffer(m_device, m_buffer, nullptr);
	}
}

[[nodiscard]] auto Buffer::get_memory_requirements() const -> MemoryRequirements
{
	auto vk_requirements = VkMemoryRequirements {};
	api::get_buffer_memory_requirements(m_device, m_buffer, &vk_requirements);
	return {
		.size = vk_requirements.size,
		.alignment = vk_requirements.alignment,
		.memory_type_bits = vk_requirements.memoryTypeBits,
	};
}

Memory::Memory(Device &device, Buffer &buffer, AllocateInfo info): m_device(device.m_device.get())
{
	auto vk_info = VkMemoryAllocateInfo {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.pNext = {},
		.allocationSize = info.size,
		.memoryTypeIndex = info.memory_type_idx,
	};
	api::allocate_memory(m_device, &vk_info, nullptr, &m_memory);

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);

	vkc(api::bind_buffer_memory(m_device, buffer.get_vk_handle(), m_memory, 0u));
}

Memory::~Memory()
{
	api::free_memory(m_device, m_memory, nullptr);
}

[[nodiscard]] auto Memory::map(size_t size, size_t offset) -> std::span<byte>
{
	void *data = {};
	vkc(api::map_memory(m_device, m_memory, offset, size, {}, &data));
	return { std::bit_cast<byte *>(data), size };
}

void Memory::unmap()
{
	api::unmap_memory(m_device, m_memory);
}

ShaderModule::ShaderModule(Device &device, CreateInfo info): m_device(device.get_vk_handle())
{
	auto vk_info = VkShaderModuleCreateInfo {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pNext = {},
		.flags = {},
		.codeSize = info.code.size(),
		.pCode = std::bit_cast<u32 *>(info.code.data()),
	};
	vkc(api::create_shader_module(m_device, &vk_info, nullptr, &m_shader_module));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

ShaderModule::~ShaderModule()
{
	if (m_device)
	{
		api::destroy_shader_module(m_device, m_shader_module, nullptr);
	}
}

DescriptorSetLayout::DescriptorSetLayout(Device &device, CreateInfo info)
    : m_device(device.get_vk_handle())
{
	auto vk_bindings = std::vector<VkDescriptorSetLayoutBinding> {};
	auto vk_binding_flag_values = std::vector<Flags> {};

	vk_bindings.reserve(info.bindings.size());
	vk_binding_flag_values.reserve(info.bindings.size());
	for (auto &binding_info : info.bindings)
	{
		vk_bindings.emplace_back(
		    VkDescriptorSetLayoutBinding {
		        .binding = binding_info.idx,
		        .descriptorType = static_cast<VkDescriptorType>(binding_info.type),
		        .descriptorCount = binding_info.count,
		        .stageFlags = binding_info.shader_stages,
		        .pImmutableSamplers = {},
		    }
		);

		vk_binding_flag_values.emplace_back(binding_info.flags);
	}

	auto vk_binding_flags_info = VkDescriptorSetLayoutBindingFlagsCreateInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
		.pNext = {},
		.bindingCount = static_cast<u32>(vk_binding_flag_values.size()),
		.pBindingFlags = vk_binding_flag_values.data(),
	};

	auto vk_info = VkDescriptorSetLayoutCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.pNext = &vk_binding_flags_info,
		.flags = info.flags,
		.bindingCount = static_cast<u32>(vk_bindings.size()),
		.pBindings = vk_bindings.data(),
	};
	vkc(api::create_descriptor_set_layout(m_device, &vk_info, nullptr, &m_descriptor_set_layout));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

DescriptorSetLayout::~DescriptorSetLayout()
{
	if (m_device)
	{
		api::destroy_descriptor_set_layout(m_device, m_descriptor_set_layout, nullptr);
	}
}

DescriptorPool::DescriptorPool(Device &device, CreateInfo info): m_device(device.get_vk_handle())
{
	auto vk_sizes = std::vector<VkDescriptorPoolSize> {};
	vk_sizes.reserve(info.sizes.size());
	for (auto &size : info.sizes)
	{
		vk_sizes.emplace_back(
		    VkDescriptorPoolSize {
		        .type = static_cast<VkDescriptorType>(size.type),
		        .descriptorCount = size.count,
		    }
		);
	}

	auto vk_info = VkDescriptorPoolCreateInfo {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.pNext = {},
		.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT,
		.maxSets = info.max_sets,
		.poolSizeCount = static_cast<u32>(vk_sizes.size()),
		.pPoolSizes = vk_sizes.data(),
	};

	vkc(api::create_descriptor_pool(m_device, &vk_info, nullptr, &m_descriptor_pool));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

DescriptorPool::~DescriptorPool()
{
	if (m_device)
	{
		api::destroy_descriptor_pool(m_device, m_descriptor_pool, nullptr);
	}
}

[[nodiscard]] auto DescriptorPool::allocate(DescriptorSetLayout &layout) -> DescriptorSet
{
	auto *vk_set = VkDescriptorSet {};
	auto vk_info = VkDescriptorSetAllocateInfo {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.descriptorPool = m_descriptor_pool,
		.descriptorSetCount = 1,
		.pSetLayouts = layout.get_vk_handle_addr(),
	};
	vkc(api::allocate_descriptor_sets(m_device, &vk_info, &vk_set));

	return DescriptorSet { vk_set };
}

DescriptorSet::DescriptorSet(VkDescriptorSet descriptor_set): m_descriptor_set(descriptor_set)
{
}

Pipeline::Pipeline(Device &device, PipelineLayout &layout, CreateInfo info)
    : m_device(device.m_device.get())

{
	auto shader_stages = std::vector<VkPipelineShaderStageCreateInfo> {};
	for (auto &[shader, stage] : info.shaders)
	{
		shader_stages.emplace_back(
		    VkPipelineShaderStageCreateInfo {
		        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		        .stage = static_cast<VkShaderStageFlagBits>(stage),
		        .module = shader.get_vk_handle(),
		        .pName = "main",
		    }
		);
	}

	auto dynamic_states = std::array<VkDynamicState, 2> {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
	};

	auto dynamic_state = VkPipelineDynamicStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size()),
		.pDynamicStates = dynamic_states.data(),
	};

	auto vertex_input = VkPipelineVertexInputStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
	};

	auto input_assembly = VkPipelineInputAssemblyStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = static_cast<VkPrimitiveTopology>(info.input_assembly_state.topology),
		.primitiveRestartEnable = info.input_assembly_state.primitive_restart_enabled,
	};

	auto viewport_state = VkPipelineViewportStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = info.viewport_state.viewport_count,
		.scissorCount = info.viewport_state.scissor_count,
	};

	auto rasterization = VkPipelineRasterizationStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_NONE,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.lineWidth = 1.0,
	};

	auto multisampling = VkPipelineMultisampleStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.sampleShadingEnable = VK_FALSE,
		.minSampleShading = 1.0,
		.pSampleMask = nullptr,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
	};

	auto color_blend_attachment = VkPipelineColorBlendAttachmentState {
		.blendEnable = VK_FALSE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
		.alphaBlendOp = VK_BLEND_OP_ADD,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
		                  | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
	};

	auto color_blend = VkPipelineColorBlendStateCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = 1,
		.pAttachments = &color_blend_attachment,
		.blendConstants = { 0.0f, 0.0, 0.0, 0.0 },
	};

	auto color_attachment_formats = std::vector<vk::Format> {};

	// WIP(Light): use color attachments
	for (auto &color_attachment : info.attachment_state.color_attachments)
	{
		ignore = color_attachment;
	}

	auto rendering_info = VkPipelineRenderingCreateInfoKHR {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.colorAttachmentCount = static_cast<uint32_t>(color_attachment_formats.size()),
		.pColorAttachmentFormats = std::bit_cast<VkFormat *>(color_attachment_formats.data()),
		.depthAttachmentFormat = info.attachment_state.depth_attachment ?
		                             static_cast<VkFormat>(
		                                 *info.attachment_state.depth_attachment
		                             ) :
		                             VK_FORMAT_UNDEFINED,

		.stencilAttachmentFormat = info.attachment_state.stencil_attachment ?
		                               static_cast<VkFormat>(
		                                   *info.attachment_state.stencil_attachment
		                               ) :
		                               VK_FORMAT_UNDEFINED,
	};

	auto vk_info = VkGraphicsPipelineCreateInfo {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = &rendering_info,
		.stageCount = static_cast<uint32_t>(shader_stages.size()),
		.pStages = shader_stages.data(),
		.pVertexInputState = &vertex_input,
		.pInputAssemblyState = &input_assembly,
		.pViewportState = &viewport_state,
		.pRasterizationState = &rasterization,
		.pMultisampleState = &multisampling,
		.pDepthStencilState = nullptr,
		.pColorBlendState = &color_blend,
		.pDynamicState = &dynamic_state,
		.layout = layout.get_vk_handle(),
		.renderPass = nullptr,
		.subpass = {},
		.basePipelineHandle = nullptr,
		.basePipelineIndex = -1,
	};

	vkc(api::create_graphics_pipelines(m_device, nullptr, 1u, &vk_info, nullptr, &m_pipeline));
}

Pipeline::~Pipeline()
{
	if (m_device)
	{
		api::destroy_pipeline(m_device, m_pipeline, nullptr);
	}
}

PipelineLayout::PipelineLayout(Device &device, CreateInfo info): m_device(device.get_vk_handle())
{
	auto vk_set_layouts = std::vector<VkDescriptorSetLayout> {};
	vk_set_layouts.reserve(info.descriptor_set_layouts.size());

	auto vk_push_constant_ranges = std::vector<VkPushConstantRange> {};
	vk_push_constant_ranges.reserve(info.push_constant_ranges.size());

	for (const auto &range : info.push_constant_ranges)
	{
		vk_push_constant_ranges.emplace_back(
		    VkPushConstantRange {
		        .stageFlags = range.shader_stages,
		        .offset = range.offset,
		        .size = range.size,
		    }
		);
	}

	for (const auto &layout : info.descriptor_set_layouts)
	{
		vk_set_layouts.emplace_back(layout->get_vk_handle());
	}

	auto vk_info = VkPipelineLayoutCreateInfo {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = {},
		.flags = {},
		.setLayoutCount = static_cast<u32>(vk_set_layouts.size()),
		.pSetLayouts = vk_set_layouts.data(),
		.pushConstantRangeCount = static_cast<u32>(vk_push_constant_ranges.size()),
		.pPushConstantRanges = vk_push_constant_ranges.data()
	};
	vkc(api::create_pipeline_layout(m_device, &vk_info, nullptr, &m_pipeline_layout));

	if (info.name.empty())
	{
		info.name = "<unnamed>";
	}
	device.name(*this, "{}", info.name);
}

PipelineLayout::~PipelineLayout()
{
	api::destroy_pipeline_layout(m_device, m_pipeline_layout, nullptr);
}

Messenger::Messenger(Instance &instance, CreateInfo info): m_instance(instance.get_vk_handle())
{
	constexpr auto native_callback = [](VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	                                    VkDebugUtilsMessageTypeFlagsEXT types,
	                                    const VkDebugUtilsMessengerCallbackDataEXT *data,
	                                    void *user_data) {
		auto *messenger = std::bit_cast<Messenger *>(user_data);
		messenger->m_user_callback(
		    severity,
		    types,
		    { .message = data->pMessage },
		    messenger->m_user_data
		);

		return VK_FALSE;
	};

	m_user_callback = std::move(info.user_callback);
	m_user_data = info.user_data;
	auto vk_info = VkDebugUtilsMessengerCreateInfoEXT {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.messageSeverity = info.enabled_severities,
		.messageType = info.enabled_types,
		.pfnUserCallback = native_callback,
		.pUserData = this,

	};

	vkc(api::create_debug_messenger(m_instance, &vk_info, nullptr, &m_messenger));
}

Messenger::~Messenger()
{
	if (m_instance)
	{
		api::destroy_debug_messenger(m_instance, m_messenger, nullptr);
	}
}

[[nodiscard]]
auto enumerate_instance_extension_properties() -> std::vector<VkExtensionProperties>
{
	auto count = 0u;
	vkc(api::enumerate_instance_extension_properties(nullptr, &count, nullptr));

	auto extensions = std::vector<VkExtensionProperties>(count);
	std::memset(extensions.data(), 0, extensions.size() * sizeof(VkExtensionProperties));
	vkc(api::enumerate_instance_extension_properties(nullptr, &count, extensions.data()));

	return extensions;
}

// auto binding = VkDescriptorSetLayoutBinding {
// 	.binding = 0,
// 	.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
// 	.descriptorCount = 1'000,
// 	.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
// };
//
// const auto descriptor_binding_flags = VkDescriptorBindingFlagsEXT {
// 	VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT
// 	    | VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT
// 	    | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT
// 	    | VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT_EXT,
// };
//
// constexpr auto descriptor_count = uint32_t { 1'000 };
//
// auto descriptor_binding_flags_info = VkDescriptorSetLayoutBindingFlagsCreateInfoEXT {
// 	.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT,
// 	.bindingCount = 1,
// 	.pBindingFlags = &descriptor_binding_flags,
// };
// m_vertices_descriptor_set_layout = m_device->create_descriptor_set_layout(
//     {
//         .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
//         .pNext = &descriptor_binding_flags_info,
//         .flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT,
//         .bindingCount = 1u,
//         .pBindings = &binding,
//
//     }
// );

} // namespace lt::renderer::vk

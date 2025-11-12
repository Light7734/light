export module renderer.components;
import assets.shader;
import math.vec3;
import memory.reference;
import std;

export namespace lt::renderer::components {

enum class VertexFormat : std::uint8_t
{
	r32_g32_b32_sfloat,

	r32_g32_sfloat,
};

enum class VertexInputRate : std::uint8_t
{
	per_vertex,

	per_instance,
};

struct VertexInputAttributeDescriptipn
{
	std::uint32_t location;

	std::uint32_t binding;

	std::uint32_t offset;

	VertexFormat format;
};

struct VertexInputBindingDescription
{
	std::uint32_t binding;

	std::uint32_t stride;
};

/** Requires a math::components::Transform component on the same entity to be functional. */
struct Sprite
{
	struct Vertex
	{
		math::vec3 position;

		math::vec3 color;

		[[nodiscard]] constexpr static auto get_attributes()
		    -> std::array<VertexInputAttributeDescriptipn, 2>
		{
			return {
				VertexInputAttributeDescriptipn {
				    .location = 0u,
				    .binding = 0u,
				    .offset = 0u,
				    .format = VertexFormat::r32_g32_b32_sfloat,

				},

				VertexInputAttributeDescriptipn {
				    .location = 1u,
				    .binding = 0u,
				    .offset = sizeof(math::vec3),
				    .format = VertexFormat::r32_g32_b32_sfloat,
				},
			};
		}
	};

	math::vec3 color;
};

} // namespace lt::renderer::components

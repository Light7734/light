export module renderer.components;
import assets.shader;
import math.vec3;
import memory.reference;
import std;

namespace lt::renderer::components {

export enum class VertexFormat: std::uint8_t {
	r32_g32_b32_sfloat,

	r32_g32_sfloat,
};

export enum class VertexInputRate: std::uint8_t {
	per_vertex,

	per_instance,
};

export struct VertexInputAttributeDescriptipn
{
	std::uint32_t location;

	std::uint32_t binding;

	std::uint32_t offset;

	VertexFormat format;
};

export struct VertexInputBindingDescription
{
	std::uint32_t binding;

	std::uint32_t stride;
};

/** Requires a math::components::Transform component on the same entity to be functional. */
export struct Sprite
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
				    .offset = offsetof(Sprite::Vertex, position),
				    .format = VertexFormat::r32_g32_b32_sfloat,

				},

				VertexInputAttributeDescriptipn {
				    .location = 1u,
				    .binding = 0u,
				    .offset = offsetof(Sprite::Vertex, color),
				    .format = VertexFormat::r32_g32_b32_sfloat,
				},
			};
		}
	};

	math::vec3 color;
};

} // namespace lt::renderer::components

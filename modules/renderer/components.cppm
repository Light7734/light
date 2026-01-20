export module renderer.components;

import preliminary;
import assets.shader;
import math.vec3;
import memory.reference;

export namespace lt::renderer::components {

enum class VertexFormat : u8
{
	r32_g32_b32_sfloat,

	r32_g32_sfloat,
};

enum class VertexInputRate : u8
{
	per_vertex,

	per_instance,
};

struct VertexInputAttributeDescriptipn
{
	u32 location;

	u32 binding;

	u32 offset;

	VertexFormat format;
};

struct VertexInputBindingDescription
{
	u32 binding;

	u32 stride;
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

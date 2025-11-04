#pragma once

#include <assets/shader.hpp>
#include <math/vec3.hpp>
#include <memory/reference.hpp>

namespace lt::renderer::components {

enum class VertexFormat : uint8_t
{
	r32_g32_b32_sfloat,

	r32_g32_sfloat,
};

enum class VertexInputRate : uint8_t
{
	per_vertex,

	per_instance,
};

struct VertexInputAttributeDescriptipn
{
	uint32_t location;

	uint32_t binding;

	uint32_t offset;

	VertexFormat format;
};

struct VertexInputBindingDescription
{
	uint32_t binding;

	uint32_t stride;
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

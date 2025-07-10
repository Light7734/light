#pragma once

#include <renderer/texture.hpp>

namespace lt {

class glTexture: public Texture
{
public:
	glTexture(const Ref<Assets::TextureAsset> &asset);

	~glTexture() override;

	void bind(unsigned int slot = 0u) override;

	auto get_texture() -> void * override;

private:
	[[nodiscard]] auto map_num_components_to_format(uint32_t num_components) const -> int;

	[[nodiscard]] auto map_num_components_to_internal_format(uint32_t num_components) const -> int;

	uint32_t m_texture_id {};
};

} // namespace lt

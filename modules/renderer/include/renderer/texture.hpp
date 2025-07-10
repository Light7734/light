#pragma once

namespace Assets {

class TextureAsset;

}

namespace Light {

class SharedContext;

class Texture
{
public:
	static Ref<Texture> create(
	    Ref<Assets::TextureAsset> asset,
	    const Ref<SharedContext> &shared_context
	);

	virtual ~Texture() = default;

	Texture(Texture &&) = default;

	auto operator=(Texture &&) -> Texture & = default;

	Texture(const Texture &) = delete;

	auto operator=(const Texture &) -> Texture & = delete;

	virtual void bind(unsigned int slot = 0) = 0;

	virtual auto get_texture() -> void * = 0;

protected:
	Texture() = default;
};

} // namespace Light

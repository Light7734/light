#pragma once

#include <engine/base/base.hpp>

namespace Light {

class SharedContext;

// #todo: improve textures
class Texture
{
public:
	static Ref<Texture> Create(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, Ref<SharedContext> sharedContext, const std::string& filePath);

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	virtual ~Texture() = default;

	virtual void Bind(unsigned int slot = 0) = 0;

	virtual void* GetTexture() = 0;

	inline const std::string& GetFilePath() const { return m_FilePath; }

protected:
	Texture(const std::string& filePath);

protected:
	std::string m_FilePath;
};

} // namespace Light

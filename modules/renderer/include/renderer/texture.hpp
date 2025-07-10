#pragma once



namespace Light {

class SharedContext;

class Texture
{
public:
	static Ref<Texture> create(
	    unsigned int width,
	    unsigned int height,
	    unsigned int components,
	    unsigned char *pixels,
	    const Ref<SharedContext>& sharedContext,
	    const std::string &filePath
	);

	Texture(const Texture &) = delete;

	auto operator=(const Texture &) -> Texture & = delete;

	virtual ~Texture() = default;

	virtual void bind(unsigned int slot = 0) = 0;

	virtual auto get_texture() -> void * = 0;

	[[nodiscard]] auto GetFilePath() const -> const std::string &
	{
		return m_file_path;
	}

protected:
	std::string m_file_path;

	Texture(std::string filePath);
};

} // namespace Light

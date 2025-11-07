#pragma once

#include <memory/scope.hpp>
#include <renderer/api.hpp>

namespace lt::renderer {

class IBuffer
{
public:
	enum class Usage : uint8_t
	{
		vertex,

		index,

		storage,

		staging,
	};

	struct CreateInfo
	{
		Usage usage;

		size_t size;

		std::string debug_name;
	};

	struct CopyInfo
	{
		size_t offset;

		size_t size;
	};

	[[nodiscard]] static auto create(
	    Api target_api,
	    class IDevice *device,
	    class IGpu *gpu,
	    const CreateInfo &info
	) -> memory::Scope<IBuffer>;

	IBuffer() = default;

	virtual ~IBuffer() = default;

	IBuffer(IBuffer &&) = default;

	IBuffer(const IBuffer &) = delete;

	auto operator=(IBuffer &&) -> IBuffer & = default;

	auto operator=(const IBuffer &) -> IBuffer & = delete;

	[[nodiscard]] virtual auto map() -> std::span<std::byte> = 0;

	virtual void unmap() = 0;

	[[nodiscard]] virtual auto get_size() const -> size_t = 0;

private:
};

} // namespace lt::renderer

#pragma once

namespace lt::renderer {

class IDevice
{
public:
	IDevice() = default;

	virtual ~IDevice() = default;

	IDevice(IDevice &&) = default;

	IDevice(const IDevice &) = delete;

	auto operator=(IDevice &&) -> IDevice & = default;

	auto operator=(const IDevice &) -> IDevice & = delete;
};

} // namespace lt::renderer

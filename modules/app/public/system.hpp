#pragma once

namespace lt::app {

class ISystem
{
public:
	ISystem() = default;

	virtual ~ISystem() = default;

	ISystem(ISystem &&) = default;

	ISystem(const ISystem &) = delete;

	auto operator=(ISystem &&) -> ISystem & = default;

	auto operator=(const ISystem &) -> ISystem & = delete;

	virtual void init() = 0;

	virtual auto tick() -> bool = 0;
};

} // namespace lt::app

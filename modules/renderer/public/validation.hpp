#pragma once

namespace lt::renderer {

enum class Severity : uint8_t
{
	off,

	very_verbose,
	verbose,
	info,
	warning,
	error,
	critical,
};

class Validation
{
public:
	void push_diagnosis();

private:
};

} // namespace lt::renderer

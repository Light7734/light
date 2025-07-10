#pragma once

#include <ecs/entity.hpp>

namespace lt {

class NativeScript
{
public:
	friend class Scene;

	NativeScript() = default;

	virtual ~NativeScript() = default;

	[[nodiscard]] auto get_uid() const -> unsigned int
	{
		return m_unique_identifier;
	}

	template<typename t>
	auto GetComponent() -> t &
	{
		return m_entity.get_component<t>();
	}

protected:
	virtual void on_create()
	{
	}

	virtual void on_destroy()
	{
	}

	virtual void on_update(float ts)
	{
	}

private:
	Entity m_entity;

	unsigned int m_unique_identifier = 0; // :#todo
};

} // namespace lt

#pragma once

#include <engine/base/base.hpp>
#include <engine/scene/entity.hpp>

namespace Light {

class NativeScript
{
public:
	friend class Scene;

	NativeScript() = default;

	virtual ~NativeScript() = default;

	inline unsigned int get_uid() const
	{
		return m_unique_identifier;
	}

	template<typename t>
	t &GetComponent()
	{
		return m_entity.GetComponent<t>();
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

} // namespace Light
